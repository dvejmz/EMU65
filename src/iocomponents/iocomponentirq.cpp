#include "../../include/iocomponents/iocomponentirq.h"

IOComponentIRQ::IOComponentIRQ() : m_channel(nullptr)
{
}

IOComponentIRQ::IOComponentIRQ(const byte *registers, const word minAddress, const word maxAddress)
    : IOComponent(registers, minAddress, maxAddress), m_channel(nullptr)
{
}

IOComponentIRQ::IOComponentIRQ(const word minAddress, const word maxAddress)
    : IOComponent(minAddress, maxAddress), m_channel(nullptr)
{
}

IOComponentIRQ::~IOComponentIRQ()
{
}

void IOComponentIRQ::SignalIRQ() const
{
  this->m_channel->SendIRQ();
}

void IOComponentIRQ::BindChannel(IOChannel *channel)
{
  this->m_channel = std::shared_ptr<IOChannel>(channel);
}
