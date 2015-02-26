#include "../../include/iocomponents/iocomponent.h"
#include <fstream>

IOComponent::IOComponent()
{
}

// Owing to the fact that every address range and location is well known,
// the register data structure can be constructed at compile time.
// A different approach would be to test that the address of the
// write is within correct range but inexistent at the moment.
// In such case, the map entry could be created on the spot.
IOComponent::IOComponent(const byte *registers,
                         const word minAddress,
                         const word maxAddress)
{
    // Has to be int instead of word, because otherwise it wraps around into 0x0 right after 0xFFFF
    // and hence the for loop condition succeeds but 'j' keeps incrementing thus reching the end
    // of the ROM image and causing an exception.
    int i;
    int j;
    try
    {
        for (i = minAddress, j = 0; i <= maxAddress; ++i, ++j)
        {
            this->m_addressRange.push_back(i);
            this->m_registers.insert(std::make_pair(i, registers[j]));
        }
    }
    catch(std::exception &e)
    {
        std::string details = e.what();
    }
}

// Initialise all the component contents to a passive state.
IOComponent::IOComponent(const word minAddress, const word maxAddress)
 {
    for(int i = minAddress; i <= maxAddress; ++i)
    {
        this->m_addressRange.push_back(i);
        this->m_registers.insert(std::make_pair(i, 0));
    }
}

IOComponent::~IOComponent()
{
}

std::vector<word> IOComponent::GetAddressRange() const
{
    return this->m_addressRange;
}

void IOComponent::SetAddressRange()
{
    for (auto kvp : this->m_registers)
    {
        this->m_addressRange.push_back(std::get<0>(kvp));
    }
}

byte IOComponent::GetRegisterValue(word address)
{
    // HACK -- Since not presetting these values
    // would cause bad behaviour in the emulator
    // it is best if some registers contained
    // specific, predictable values. However, this is really hard to accomplish.
    // since these values get changed on a cold/warm reset by the monitor
    // so there's no guarantee whatsoever they will remain as desired throughout
    // the emulator execution (other than maybe making the value at that address 'const').
    // Hence, the only (at least for now) way to
    // ensure good behaviour is by hacking them with stable values.
    if (address == 0xA800)
    {
        // This flips the KB bit always ON, and the TTY bit OFF, leaving the rest
        // unchanged (in relation to what the monitor expects).
        // This is so because the emulator doesn't have any emulated TeleType Controller.
        this->SetRegister(0xA800, 0x3C);
    }
    else if (address == 0xA411)
    {
        // This sets the PRIFLG register to 0, meaning that the printer is off.
        this->SetRegister(0xA411, 0x1);
    }
    return this->m_registers[address];
}

void IOComponent::SetRegister(word address, byte value)
{
    // TODO -- Input verification.
    // if (this->IsGoodValue(value))
    this->m_registers[address] = value;
    this->UpdateDebugStatus(address);
}

void IOComponent::UpdateDebugStatus(word address)
{
    AimInspector::GetInstance()->UpdateComponentStatus(this->DumpMemory(address));
}

std::string IOComponent::DumpMemory()
{
    std::string memoryDump = "";
    char S[128];

    sprintf(S, "\n");
    memoryDump += S;
    for(auto kvp : this->m_registers)
    {
        sprintf(S, "%04X: %02X | %c\n",std::get<0>(kvp), std::get<1>(kvp), isprint(static_cast<int>(std::get<1>(kvp)))? static_cast<int>(std::get<1>(kvp)):'.');
      memoryDump += S;
    }

    return memoryDump;
}

std::string IOComponent::DumpMemory(word address)
{
    std::string memoryDump = "";
    const int range = 16;
    char S[128];

    sprintf(S, "\n");
    memoryDump += S;
    for(int i = (address - range >= this->GetAddressRange()[0] ? address - range : address);
        i <= (address + range) && i <= this->GetAddressRange()[this->GetAddressRange().size() - 1];
        ++i)
    {
        sprintf(S, "%04X: %02X | %c\n",i, this->m_registers[i], isprint(static_cast<int>(this->m_registers[i]))? static_cast<int>(this->m_registers[i]):'.');
      memoryDump += S;
    }

    return memoryDump;
}

void IOComponent::Clear()
{
    if (!this->m_registers.empty())
    {
        this->m_registers.clear();
    }
}

void IOComponent::RemoveRegister(word address)
{
    /*this->m_addressRange.erase(address);
    this->m_registers.erase(address);*/
}
