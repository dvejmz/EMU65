#include "../include/iocomponents/leddisplay.h"
#include <fstream>

/** LED Display Address Mappings *************************/
/**                                                     **/
/** NOTE: There are address gaps amongst DISP 2-5.      **/
/** KEY: A0-A1: Digit Select Lines. DS1-DS5: Displays.  **/
/**      CE: Chip Enable (Select). W: Write.            **/
/**      D0-D7: Data Lines. CU: Cursor.                 **/
/**                                                     **/
/** 0xAC00 - RA: Data Register A.                       **/
/**     0: A0 | 1: A1 | 2: DS1 CE | 3: DS2 CE           **/
/**     4: DS3 CE | 5: DS4 CE | 6: DS5 CE | 7: W        **/
/** 0xAC01 - CRA: Control Register A. (Data Direction)  **/
/** 0xAC02 - RB: Register B.                            **/
/**     0: D0 | 1: D1 | 2: D2 | 3: D3                   **/
/**     4: D4 | 5: D5 | 6: D6 | 7: CU                   **/
/** 0xAC03 - CRB: Control Register B. (Data Direction)  **/
/** 0xAC04 - DISP 1 DIG 0 CH 4                          **/
/** 0xAC05 - DISP 1 DIG 1 CH 3                          **/
/** 0xAC06 - DISP 1 DIG 2 CH 2                          **/
/** 0xAC07 - DISP 1 DIG 3 CH 1                          **/
/** 0xAC08 - DISP 2 DIG 0 CH 8                          **/
/** 0xAC09 - DISP 2 DIG 1 CH 7                          **/
/** 0xAC0A - DISP 2 DIG 2 CH 6                          **/
/** 0xAC0B - DISP 2 DIG 3 CH 5                          **/
/** 0xAC10 - DISP 3 DIG 0 CH 12                         **/
/** 0xAC11 - DISP 3 DIG 1 CH 11                         **/
/** 0xAC12 - DISP 3 DIG 2 CH 10                         **/
/** 0xAC13 - DISP 3 DIG 3 CH 9                          **/
/** 0xAC20 - DISP 4 DIG 0 CH 16                         **/
/** 0xAC21 - DISP 4 DIG 1 CH 15                         **/
/** 0xAC22 - DISP 4 DIG 2 CH 14                         **/
/** 0xAC23 - DISP 4 DIG 3 CH 13                         **/
/** 0xAC40 - DISP 5 DIG 0 CH 20                         **/
/** 0xAC41 - DISP 5 DIG 1 CH 19                         **/
/** 0xAC42 - DISP 5 DIG 2 CH 18                         **/
/** 0xAC43 - DISP 5 DIG 3 CH 17                         **/
/*********************************************************/

const word LedDisplay::MIN_ADDR = 0xAC00;
const word LedDisplay::MAX_ADDR = 0xAC43;

const word LedDisplay::RA_ADDR = 0xAC00;
const word LedDisplay::RB_ADDR = 0xAC02;

const word LedDisplay::RA_W = 0x80;
const word LedDisplay::RA_DS5 = 0x40;
const word LedDisplay::RA_DS4 = 0x20;
const word LedDisplay::RA_DS3 = 0x10;
const word LedDisplay::RA_DS2 = 0x08;
const word LedDisplay::RA_DS1 = 0x04;
const word LedDisplay::RA_A1 = 0x02;
const word LedDisplay::RA_A0 = 0x01;

const word LedDisplay::RB_CU = 0x80;

const word LedDisplay::DS1_ADDR = 0xAC04;
const word LedDisplay::DS2_ADDR = 0xAC08;
const word LedDisplay::DS3_ADDR = 0xAC10;
const word LedDisplay::DS4_ADDR = 0xAC20;
const word LedDisplay::DS5_ADDR = 0xAC40;
const byte LedDisplay::DISPLAY_MASK = LedDisplay::RA_DS1 | LedDisplay::RA_DS2 | LedDisplay::RA_DS3 | LedDisplay::RA_DS4 | LedDisplay::RA_DS5; // 0x3E

LedDisplay::LedDisplay(LedDisplayProxy *proxy)
{
    for (int i = 0xAC00; i <= 0xAC43; ++i)
    {
        this->m_registers.insert(std::make_pair(i,0));
    }

    this->SetAddressRange();

    this->m_proxy = std::shared_ptr<LedDisplayProxy>(proxy);
}

LedDisplay::LedDisplay(const byte *registers, const word minAddress, const word maxAddress)
    : IOComponent(registers, minAddress, maxAddress)
{
}

LedDisplay::LedDisplay(const word minAddress, const word maxAddress)
    : IOComponent(minAddress, maxAddress)
{
}

/*void LedDisplay::SetRegister(word address, byte value)
{
    std::ofstream fout("led.txt", std::ios_base::out | std::ios_base::app);
    fout << "ADDRESS: " << address << " VALUE: " << (int)value;
    fout << std::endl;
    fout.close();

    if (this->CursorEnabled(this->m_registers[RA_ADDR], this->m_registers[RB_ADDR]))
    {
            std::vector<word> targetedAddresses = this->GetTargetDisplaysFromAddrRegister();
            for (auto effectiveRegAddr : targetedAddresses)
            {
                // For each display addressed.
                // Update the register corresponding to the address in RA.
                this->m_registers[effectiveRegAddr] = this->m_registers[RB_ADDR];

                this->m_proxy->triggerDisplayDigitChanged(this->GetDisplayDigitPair(effectiveRegAddr), '*');
            }
    }
    else if (address == RA_ADDR)
    {
        // Mask out W.
        byte w = value & RA_W;
        // Mask out CE.
        byte ce = value & DISPLAY_MASK;
        // If W=1 and there is a CE line held low (open).
        if (w > 0)
        {
            IOComponent::SetRegister(address, value);
            // The value contains the chip and digit position.
            std::vector<word> targetedAddresses = this->GetTargetDisplaysFromAddrRegister();
            for (auto effectiveRegAddr : targetedAddresses)
            {
                // For each display addressed.
                // Update the register corresponding to the address in RA.
                this->m_registers[effectiveRegAddr] = this->m_registers[RB_ADDR];
            }
        }
        else if(w == 0)
        {
            // Display the contents of RB.
            std::vector<word> targetedAddresses = this->GetTargetDisplaysFromAddrRegister();
            for (auto effectiveRegAddr : targetedAddresses)
            {
                // For each display addressed.
                // It's fine to store the entire byte as read from the CPU
                // with the trailing W bit zero in an internal register
                // but it is necesary to turn it into a cast-friendly
                // variable so it can be readily displayed in ASCII.
                // Thus, the trailing W zero is removed, effectively
                // obtaining a 7-bit construct that can be casted
                // into ASCII chars.
                byte cleanChar = this->m_registers[effectiveRegAddr] >> 1;
                this->m_proxy->triggerDisplayDigitChanged(this->GetDisplayDigitPair(effectiveRegAddr), cleanChar);
            }
        }
    }
    else if (address == RB_ADDR)
    {
        IOComponent::SetRegister(address, value);
    }
}*/

void LedDisplay::UpdateDebugStatus(word address)
{
    AimInspector::GetInstance()->UpdateLedDisplayStatus(IOComponent::DumpMemory());
}

void LedDisplay::SetRegister(word address, byte value)
{
    /*std::ofstream fout("leddbglog.txt", std::ios_base::out | std::ios_base::app);
    char S[64];
    sprintf(S, "ADDRESS: %04X  VALUE: %02X", address, value);
    fout << "[" << AimInspector::CurrentDateTime() << "] " << S;
    fout << std::endl;
    fout.close();*/

    IOComponent::SetRegister(address, value);

    if (this->CursorEnabled())
    {
        this->OutputCursor();
    }
    else if (address == RA_ADDR)
    {
        // Mask out W.
        byte w = value & RA_W;
        // If W=1 and there is a CE line held low (logical 1).
        if (w > 0 && this->GetTargetDisplayFromAddrRegister() != 5)
        {
            // The value contains the chip and digit position.
            word effectiveRegAddr = this->GetTargetDisplayFromAddrRegister();
            // For each display addressed.
            // Update the register corresponding to the address in RA.
            this->m_registers[effectiveRegAddr] = this->m_registers[RB_ADDR];

            // Display the contents of RB.
            // It's fine to store the entire byte as read from the CPU
            // with the trailing W bit zero in an internal register
            // but it is necesary to turn it into a cast-friendly
            // variable so it can be readily displayed in ASCII.
            // Thus, the trailing W zero is removed, effectively
            // obtaining a 7-bit construct that can be casted
            // into ASCII chars.
            byte cleanChar = this->m_registers[effectiveRegAddr] >> 1;

            std::ofstream fout("leddbglog.txt", std::ios_base::out | std::ios_base::app);
            char S[64];
            sprintf(S, "EFF ADDRESS: %04X  VALUE: %02X CLEAN CHAR: %d", effectiveRegAddr, value, cleanChar);
            fout << "[" << AimInspector::CurrentDateTime() << "] " << S;
            fout << std::endl;
            fout.close();

            this->m_proxy->triggerDisplayDigitChanged(this->GetDisplayDigitPair(effectiveRegAddr), cleanChar);
        }
    }
}

bool LedDisplay::CursorEnabled()
{
    byte regA = this->m_registers[RA_ADDR];
    byte regB = this->m_registers[RB_ADDR];
    byte displaySelection = regA & DISPLAY_MASK;

    regA &= RA_W;
    regB &= RB_CU;

    return regA > 0 && regB > 0 && displaySelection > 0;
}

void LedDisplay::OutputCursor()
{
    for(word addr : this->GetCursorTargetDisplaysFromAddrRegister())
    {
        std::ofstream fout("leddbglog.txt", std::ios_base::out | std::ios_base::app);
        char S[64];
        sprintf(S, "ADDRESS: %04X", addr);
        fout << std::endl;
        fout.close();
        this->m_proxy->triggerDisplayDigitChanged(this->GetDisplayDigitPair(addr), '*');
    }
}

std::vector<word> LedDisplay::GetCursorTargetDisplaysFromAddrRegister()
{
    std::vector<word> targetedDisplaysAddrs;
    // Decode the display digit position to change.
    int digitBitsOffset = 6;
    int digitOffset = this->m_registers[RA_ADDR] >> digitBitsOffset;

    // Decode the display in which the digit is located.
    byte displaySelection = this->m_registers[RA_ADDR] & DISPLAY_MASK;

    if ((displaySelection & RA_DS1) > 0)
    {
        targetedDisplaysAddrs.push_back(DS1_ADDR+digitOffset);
    }
    if ((displaySelection & RA_DS2) > 0)
    {
        targetedDisplaysAddrs.push_back(DS2_ADDR+digitOffset);
    }
    if ((displaySelection & RA_DS3) > 0)
    {
        targetedDisplaysAddrs.push_back(DS3_ADDR+digitOffset);
    }
    if ((displaySelection & RA_DS4) > 0)
    {
        targetedDisplaysAddrs.push_back(DS4_ADDR+digitOffset);
    }
    if ((displaySelection & RA_DS5) > 0)
    {
        targetedDisplaysAddrs.push_back(DS5_ADDR+digitOffset);
    }

    return targetedDisplaysAddrs;
}

word LedDisplay::GetTargetDisplayFromAddrRegister()
{
    word displayAddress = 0x0000;
    // Decode the display digit position to change.
    int digitBitsOffset = 6;
    int digitOffset = this->m_registers[RA_ADDR] << digitBitsOffset;

    // Decode the display in which the digit is located.
    byte displaySelection = this->m_registers[RA_ADDR] & DISPLAY_MASK;
    int displayPosition = -1;
    switch (displaySelection)
    {
    case RA_DS1:
        displayPosition = 0;
        displayAddress = DS1_ADDR;
        break;
    case RA_DS2:
        displayPosition = 1;
        displayAddress = DS2_ADDR;
        break;
    case RA_DS3:
        displayPosition = 2;
        displayAddress = DS3_ADDR;
        break;
    case RA_DS4:
        displayPosition = 3;
        displayAddress = DS4_ADDR;
        break;
    case RA_DS5:
        displayPosition = 4;
        displayAddress = DS5_ADDR;
        break;
    default:
        // Invalid value like multiple displays selected at the same time.
        return 5;
    }

    return displayAddress+digitOffset;
}

std::pair<int, int> LedDisplay::GetDisplayDigitPair(word address) const
{
    std::pair<int, int> pair;

    if (address >= DS1_ADDR && address < (DS1_ADDR + 4))
    {
        pair = std::make_pair(0, address - DS1_ADDR);
    }
    else if (address >= DS2_ADDR && address < (DS2_ADDR + 4))
    {
        pair = std::make_pair(1, address - DS2_ADDR);
    }
    else if (address >= DS3_ADDR && address < (DS3_ADDR + 4))
    {
        pair = std::make_pair(2, address - DS3_ADDR);
    }
    else if (address >= DS4_ADDR && address < (DS4_ADDR + 4))
    {
        pair = std::make_pair(3, address - DS4_ADDR);
    }
    else if (address >= DS5_ADDR && address < (DS5_ADDR + 4))
    {
        pair = std::make_pair(4, address - DS5_ADDR);
    }
    else
    {
        // Address is invalid, either out of range or in an inaccessible gap.
        return std::make_pair(-1, -1);
    }

    return pair;
}
