#include "../../include/iocomponents/iochannel.h"

IOChannel::IOChannel(IOBus *bus) : Channel(bus), m_addressRange(0)
{
    m_bus->AttachIOChannel(this);
}

IOChannel::~IOChannel()
{
    m_bus->DetachIOChannel(this);
}

void IOChannel::Write(word address, byte value) const
{
    this->m_component->SetRegister(address, value);
}

byte IOChannel::Read(word address)
{
    return this->m_component->GetRegisterValue(address);
}

std::vector<word> IOChannel::GetAddressRange()
{
    if (this->m_addressRange.empty())
    {
        this->SetAddressRange();
    }

    return this->m_addressRange;
}

void IOChannel::SetAddressRange()
{
    this->m_addressRange = this->m_component->GetAddressRange();
}

bool IOChannel::IsValidAddress(word address) const
{
    bool isValidAddress = false;
    for (auto addr : this->m_addressRange)
    {
        if (address == addr)
        {
            isValidAddress = true;
            break;
        }
    }

    return isValidAddress;
}

void IOChannel::SendIRQ() const
{
    this->m_bus->SetIRQLine();
}

void IOChannel::BindComponent(IOComponent *component)
{
    this->m_component = std::unique_ptr<IOComponent>(component);
    this->SetAddressRange();
}
