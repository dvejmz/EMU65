#ifndef IOCHANNEL_H
#define IOCHANNEL_H

#include "channel.h"
#include "iobus.h"
#include "iocomponent.h"
#include "leddisplay.h"

/**
 * Connects an IOComponent module to IOBus.
 */
class IOChannel : public Channel
{
 public:
    /**
     * @see Channel::Channel
     */
    IOChannel(IOBus *bus);
    /**
     * @see Channel::~Channel
     */
    virtual ~IOChannel();
    // PASSIVE METHODS.
    // IOComponent does not perform IO autonomously.
    // Rather, it does whatever Cpu instructs it to do,
    // and when its buffer changes, issues an interrupt
    // so Cpu reads its contents or updates its buffers.
    // Updates IOComponent buffer.
    /**
     * @see Channel::Write
     */
    virtual void Write(word address, byte value) const;
    /**
     * @see Channel::Read
     */
    virtual byte Read(word address);
    // When overriden by an IOChannel class, this acts as a
    // passive method, solely called by IOBus.
    // Reads IOComponent buffer.
    /**
     * Sets the IRQ line in IOBus high.
     */
    void SendIRQ() const;
    /**
     * Confirms that the address is indeed mapped to a register in the attached IOComponent.
     * @param address Address to check.
     * @return True if the address is valid, false if it is not.
     */
    bool IsValidAddress(word address) const;
    /**
     * Attaches an IOComponent to this instance so the component is able to exchange messages
     * with the rest of the system through IOBus.
     * @param component IOComponent to bind.
     */
    void BindComponent(IOComponent *component);
    /**
     * Obtains an AddressRange struct conaining the minimum and maximum address on which the
     * attached IOComponents operates.
     * @return An AddressRange struct identifying the address space bounds of the attached IOComponent.
     * @see IOComponent::GetAddressRange
     */
    std::vector<word> GetAddressRange();

    void SetAddressRange();

private:
    /**
     * Connected IOComponent.
     */
    std::unique_ptr<IOComponent> m_component;
    /**
     * Address range within which the attached IOComponent responds.
     */
    std::vector<word> m_addressRange;

    DISALLOW_COPY_AND_ASSIGN(IOChannel);
};

#endif /* IOCHANNEL_H */
