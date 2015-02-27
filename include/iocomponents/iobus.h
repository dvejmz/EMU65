/** EMU65 ***********************************************************/
/**                                                                **/
/**                            iobus.h                             **/
/**                                                                **/
/** Header file of the IOBus class, which relays messages between C**/
/** pu and IOComponent children.                                   **/
/********************************************************************/
#ifndef IOBUS_H
#define IOBUS_H

#include <vector>
#include <memory>
#include "../globals.h"

// These forward declarations must exist to avoid circular dependencies amongst the components involved.
class IOChannel;
class CpuChannel;

/**
 * Redirects read and write requests from the attached channels, redirecting messages from every component.
 */
class IOBus
{
 public:
    /**
     * Gets a pointer to the IOBus singleton. If IOBus hasn't been instantiated yet
     * it constructs it and then returns a pointer to it.
     * @return Pointer to IOBus singleton instance.
     */
    static IOBus* GetInstance();

    // TODO -- Might probably need a copy constructor, since this class is
    // going to be managed chiefly by value.
    /**
     * Inserts an IOChannel to the list of attached IOChannels to the singleton.
     * @param pChannel IOChannel to be inserted.
     */
    void AttachIOChannel(IOChannel *pChannel);

    /**
     * Removes an IOChannel from the list of attached IOChannels to the singleton.
     * @param pChannel IOChannel to be removed.
     */
    void DetachIOChannel(IOChannel *pChannel);

    /**
     * Gets the IOChannel from the attached set whose address range corresponds to the address provided.
     * @param address Specifies an address which identifies the address space of an attached IOChannel.
     * @return The corresponding IOChannel to the address.
     */
    IOChannel* GetIOChannel(word address) const;

    /**
     * Sets the IRQ line high, signalling there is a new pending IRQ.
     */
    void SetIRQLine();

    /**
     * Sets the IRQ line low, signalling there are no new pending IRQs. This is usually done when
     * Cpu acknowledges an IRQ.
     */
    void ClearIRQLine();

    /**
     * Obtains the current state of the IRQLine.
     * @return  True if the IRQ line is high, false if it is low.
     * @see CpuChannel::ReadIRQLineState
     */
    bool IRQLine() const;

    /**
     * Writes data to an IOComponent register based on a given address.
     * @param address Address of the IOComponent register.
     * @param value Value to be written in the IOComponent register.
     */
    void Write(word address, byte value);

    /**
     * Reads data from an IOComponent register based on a given address.
     * @param address Address of the IOComponent register.
     * @return Value of the IOComponent register.
     */
    byte Read(word address);
private:

    // Both ends of the channel have a reference to it.
    /**
     * List of IOChannels attached to the singleton.
     */
    std::vector<std::shared_ptr<IOChannel>> m_attachedIOChannels;

    /**
     * Pointer to the singleton instance.
     */
    static IOBus* pInstance;

    /**
     * IRQ line variable.
     * @see IOBus::SetIRQLine
     * @see IOBus::ClearIRQLine
     * @see IOBus::IRQLine
     */
    bool m_irqLine;
    // bool m_nmiLine;
    DISALLOW_COPY_AND_ASSIGN(IOBus);
    IOBus();
    ~IOBus();
};

#endif /* IOBUS_H */
