#include "../../include/iocomponents/printer.h"

/** Printer Address Space *****************************************/
/**                                                              **/
/** 0xA800 - DRB: Data Register B.                               **/
/**     0: TE9/PB0 | 1: TE10/PB1                                 **/
/** 0xA801 - DRAH: Data Register A (Handshake) PA0-PA7/TE1-TE8.  **/
/** 0xA802 - DDRB: Data Direction Register B.                    **/
/** 0xA803 - DDRA: Data Direction Register A.                    **/
/******************************************************************/

// DRB_ADDR's 3rd bit (PB3 - KB/TTY) must always be 1 (KB) so TTY bit rate measurement routine can
// be bypassed.

Printer::Printer() : IOComponentIRQ()
{
}

Printer::Printer(const byte *registers, const word minAddress, const word maxAddress) : IOComponentIRQ(registers, minAddress, maxAddress)
{
}

Printer::Printer(const word minAddress, const word maxAddress) : IOComponentIRQ(minAddress, maxAddress)
{
    // Override the default address vector with this extra address (no value attached to it)
    // so the class can claim recognising it and intercept the print subroutine.
    this->m_addressRange.push_back(PRDOT0_ADDR);
    this->m_registers.insert(std::make_pair(PRDOT0_ADDR, 0));
}

byte Printer::GetRegisterValue(const word address)
{
    if (address == PRDOT0_ADDR)
    {
        // Intercept print subroutine call.
        this->PrintBuffer();
        // Return something to make the CPU think it's already done everything it needed to.
    }
    else
    {
        return IOComponentIRQ::GetRegisterValue(address);
    }
}

void Printer::UpdateDebugStatus(word address)
{

}

void Printer::PrintBuffer() const
{
    const int bufferSize = 20;
    int numSetCharacters = 0;
    byte bufferContents[bufferSize];
    for (word i = 0; i < bufferSize; ++i)
    {
        if (bufferContents[i] > 0)
        {
            bufferContents[i] = IOBus::GetInstance()->Read(IBUFM_ADDR+i);
            ++numSetCharacters;
        }
    }

    // Print buffer contents to file.
    FilePrinter fPrinter(bufferContents, numSetCharacters);
    // Print path argument initialised to default path if no other path provided.
    fPrinter.Print();
}
