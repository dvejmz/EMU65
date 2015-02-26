#include "../../include/M6502/cpu.h"
#include <fstream>
#include "../../Include/M6502/cpuqthread.h"

Cpu* Cpu::pInstance = nullptr;

Cpu::Cpu()
{
    this->m_halt = true;
}

Cpu::~Cpu()
{
}

Cpu* Cpu::GetInstance()
{
    if (Cpu::pInstance == nullptr)
    {
        Cpu::pInstance = new Cpu();
    }

    return Cpu::pInstance;
}

void Cpu::Run()
{
    this->m_halt = false;
    Run6502(&this->m_cpu);
}

byte Cpu::Read(word address)
{
    return this->m_channel->Read(address);
}

void Cpu::Write(word address, byte value) const
{
    this->m_channel->Write(address, value);
}

void Cpu::Reset()
{
    Reset6502(&this->m_cpu);
}

#ifdef DEBUG

byte Cpu::UpdateDbgStatus()
{
    AimInspector::GetInstance()->UpdateCpuStatus(this->GetCpuDebugData());

    const std::string timestamp = "[" + AimInspector::CurrentDateTime() + "] ";
    std::string str = timestamp + this->GetCpuDebugData();
    std::ofstream fout("dbgoutput.txt", std::ios_base::out | std::ios_base::app);

    for (int i = 0; i < str.size(); ++i)
    {
        if (str[i])
        fout.put(str[i]);
    }

    fout << std::endl;
    fout.close();
    return 1;
}

// TODO -- Expose:
// * Cpu cycles: ICount, IPeriod
// Produces a formatted string of data to send to AimInspector
// Chances are AimInspector won't need to work with
// any data at all, just display things that the emulator components
// feed it. Debugging metrics will be processed by their corresponding class.
std::string Cpu::GetCpuDebugData()
{
    const int stringBufferSize = 128;
    char FA[9]="NVRBDIZC";
    char S[stringBufferSize];
    byte F;
    int J;
    std::string dbgOutput = "";

    sprintf(S, "A:%02X  P:%02X  X:%02X  Y:%02X  S:%04X  PC:%04X  Flags:[",
            m_cpu.A,m_cpu.P,m_cpu.X,m_cpu.Y,m_cpu.S+0x0100,m_cpu.PC.W);
    dbgOutput += S;

    for(J=0,F=m_cpu.P;J<8;J++,F<<=1)
    {
        S[stringBufferSize];
        sprintf(S, "%c",F&0x80? FA[J]:'.');
        dbgOutput += S;
    }

    S[stringBufferSize];
    sprintf(S, "]\n");
    dbgOutput += S;

    sprintf
            (
                S,
                "AT PC: [%02X]   AT SP: [%02X %02X %02X]\n",
                Read(m_cpu.PC.W),
                Read(0x0100+(byte)(m_cpu.S+1)),
                Read(0x0100+(byte)(m_cpu.S+2)),
                Read(0x0100+(byte)(m_cpu.S+3))
                );
    dbgOutput += S;
    S[stringBufferSize];

    return dbgOutput;
}

#endif /* DEBUG */

void Cpu::ServiceInterrupt(byte type)
{
    Int6502(&this->m_cpu, type);
}

void Cpu::ServiceIRQ()
{
    this->ServiceInterrupt(INT_IRQ);
}

void Cpu::ServiceNMI()
{
    this->ServiceInterrupt(INT_NMI);
}

byte Cpu::CheckInterrupts()
{
    if (this->m_halt)
    {
        return INT_QUIT;
    }
    else if (m_channel->ReadIRQLineState())
    {
        return INT_IRQ;
    }
    else
    {
        return INT_NONE;
    }
}

// Returns 1 if the exception was handled,
// 0 if the opcode was truly illegal.
byte Cpu::ProcessUnknownCode()
{
    // TODO -- Implement.
    return 1;
}

void Cpu::BindChannel(CpuChannel *channel)
{
    this->m_channel = std::unique_ptr<CpuChannel>(channel);
}

void Cpu::Halt()
{
    this->m_halt = true;
}
