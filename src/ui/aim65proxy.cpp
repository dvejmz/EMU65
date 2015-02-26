#include "../../include/ui/aim65proxy.h"

Aim65Proxy::Aim65Proxy(Aim65 *aim65, QObject *parent) : QObject(parent), UiProxy()
{
    this->m_aim65 = std::shared_ptr<Aim65>(aim65);
    CpuQtThread *cpuThread = new CpuQtThread();
    this->m_cpuThread = std::unique_ptr<CpuQtThread>(cpuThread);
    this->RegisterProxy();
}

Aim65Proxy::~Aim65Proxy()
{
}

void Aim65Proxy::RegisterProxy()
{
    UiProxyCollection::GetInstance()->InsertAim65Proxy(this);
}

void Aim65Proxy::SetResetButton(bool newState)
{
    if (newState == true)
    {
        if (this->m_cpuThread != nullptr)
        {
            if(this->m_cpuThread->isRunning())
            {
                this->m_cpuThread->exit(0);
            }
        }

        Cpu::GetInstance()->Reset();
        this->m_cpuThread->start();
        //Cpu::GetInstance()->Run();
    }
    else
    {
        Cpu::GetInstance()->Halt();
    }

    this->m_aim65->SetPowerSwitch(newState);
}

bool Aim65Proxy::GetResetButton() const
{
    return true;
}
