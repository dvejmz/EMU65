#include "../../include/iocomponents/iobus.h"
#include "../../include/iocomponents/iochannel.h"
#include "../../include/iocomponents/cpuchannel.h"
#include "../../include/iocomponents/unmappedmemoryexception.h"

IOBus* IOBus::pInstance = nullptr;

IOBus* IOBus::GetInstance()
{
    if (IOBus::pInstance == nullptr)
    {
        IOBus::pInstance = new IOBus();
    }

    return IOBus::pInstance;
}

IOBus::IOBus()
{
    this->ClearIRQLine();
}

IOBus::~IOBus()
{
}

void IOBus::AttachIOChannel(IOChannel *pChannel)
{
    this->m_attachedIOChannels.push_back(std::shared_ptr<IOChannel>(pChannel));
}

void IOBus::DetachIOChannel(IOChannel *pChannel)
{
    for (int i = 0; i < this->m_attachedIOChannels.size(); ++i)
    {
        if (this->m_attachedIOChannels.at(i).get() == pChannel)
        {
            this->m_attachedIOChannels.erase(this->m_attachedIOChannels.begin() + i);
        }
    }
}

void IOBus::Write(word address, byte value)
{
    IOChannel* channel = this->GetIOChannel(address);
    if (channel != nullptr)
    {
        channel->Write(address, value);
    }
}

byte IOBus::Read(word address)
{
    IOChannel* channel = this->GetIOChannel(address);
    if (channel != nullptr)
    {
        return channel->Read(address);
    }
}

IOChannel* IOBus::GetIOChannel(word address) const
{
    IOChannel *targetChannel = nullptr;

    // 0xF08C - PRDOT0: Beginning of printer buffer printing subroutine. (Called from 0xFF4B)
    const word PRDOT0_ADDR = 0xF08C;

    if(address == 0xFF74)
    {
        int x = 5;
    }

    // Trap calls to print subroutine stored in Monitor ROM.
    if (address == PRDOT0_ADDR)
    {
        // Get the printer channel.
        for (auto channel : this->m_attachedIOChannels)
        {
            // If the channel recognises the printer subroutine address, which is also recognised by the
            // Monitor ROM channel, and it recognises the address of one of the printer registers,
            // then it is the printer channel.
            if(channel->IsValidAddress(address) && channel->IsValidAddress(0xA800))
            {
                targetChannel = channel.get();
                break;
            }
        }
    }
    else
    {
        for (auto channel : this->m_attachedIOChannels)
        {
            if(channel->IsValidAddress(address))
            {
                targetChannel = channel.get();
                break;
            }
        }
    }

    if (targetChannel == nullptr)
    {
        throw UnmappedMemoryException();
    }

    return targetChannel;
}

void IOBus::SetIRQLine()
{
    m_irqLine = true;
}

void IOBus::ClearIRQLine()
{
    m_irqLine = false;
}

bool IOBus::IRQLine() const
{
    return m_irqLine;
}
