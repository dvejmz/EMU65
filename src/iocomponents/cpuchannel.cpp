#include "../../include/iocomponents/cpuchannel.h"

CpuChannel::CpuChannel(IOBus *bus) : Channel(bus)
{
}

CpuChannel::~CpuChannel()
{
}

void CpuChannel::Write(word address, byte value) const
{
  this->m_bus->Write(address, value);
}

byte CpuChannel::Read(word address)
{
  return this->m_bus->Read(address);
}

bool CpuChannel::ReadIRQLineState() const
{
  return this->m_bus->IRQLine();
}
