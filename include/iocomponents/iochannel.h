#ifndef IOCHANNEL_H
#define IOCHANNEL_H

#include "channel.h"
#include "iobus.h"
#include "iocomponent.h"
#include "leddisplay.h"

/**
 * @brief The IOChannel class
 * {Connects an IOComponent module to IOBus.}
 */
class IOChannel : public Channel
{
 public:
    /**
     * @brief IOChannel
     * \sa Channel::Channel
     */
    IOChannel(IOBus *bus);
    /**
     * @brief ~IOChannel
     *\sa Channel::~Channel
     */
    virtual ~IOChannel();
    // PASSIVE METHODS.
    // IOComponent does not perform IO autonomously.
    // Rather, it does whatever Cpu instructs it to do,
    // and when its buffer changes, issues an interrupt
    // so Cpu reads its contents or updates its buffers.
    // Updates IOComponent buffer.
    /**
     * @brief Write
     * \sa Channel::Write
     */
    virtual void Write(word address, byte value) const;
    /**
     * @brief Read
     * \sa Channel::Read
     */
    virtual byte Read(word address);
    // When overriden by an IOChannel class, this acts as a
    // passive method, solely called by IOBus.
    // Reads IOComponent buffer.
    /**
     * @brief SendIRQ
     * {Sets the IRQ line in IOBus high.}
     */
    void SendIRQ() const;
    /**
     * @brief IsValidAddress
     * {Confirms that the address is indeed mapped to a register in the attached IOComponent.}
     * @param address {Address to check.}
     * @return {True if the address is valid, false if it is not.}
     */
    bool IsValidAddress(word address) const;
    /**
     * @brief BindComponent
     * {Attaches an IOComponent to this instance so the component is able to exchange messages
     * with the rest of the system through IOBus.}
     * @param component {IOComponent to bind.}
     */
    void BindComponent(IOComponent *component);
    /**
     * @brief GetAddressRange
     * {Obtains an AddressRange struct conaining the minimum and maximum address on which the
     * attached IOComponents operates.}
     * @return {An AddressRange struct identifying the address space bounds of the attached IOComponent.}
     * \sa IOComponent::GetAddressRange
     */
    std::vector<word> GetAddressRange();

    void SetAddressRange();

private:
    /**
     * @brief m_component
     * {Connected IOComponent.}
     */
    std::unique_ptr<IOComponent> m_component;
    /**
     * @brief m_addressRange
     * {Address range within which the attached IOComponent responds.}
     */
    std::vector<word> m_addressRange;

    DISALLOW_COPY_AND_ASSIGN(IOChannel);
};

#endif /* IOCHANNEL_H */
