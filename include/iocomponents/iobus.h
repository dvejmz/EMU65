/** EMU65 ***********************************************************/
/**                                                                **/
/**                            iobus.h                             **/
/**                                                                **/
/** Header file of the IOBus class, which relays messages between C**/
/** pu and IOComponent children.                                   **/
/**                                                                **/
/** David J Sequero                                                **/
/**                                                                **/
/**    Copyright (C) David J Sequero. This file is distributed unde**/
/**    r GPLv3 licensing terms, except those components conveyed b **/
/**    y Marat Fayzullin.                                          **/
/**                                                                **/
/********************************************************************/
#ifndef IOBUS_H
#define IOBUS_H

#include <vector>
#include <memory>
#include "../globals.h"

class IOChannel;
class CpuChannel;

/**
 * @brief The IOBus class
 * {Redirects read and write requests from the attached channels, redirecting messages from every component.}
 */
class IOBus
{
 public:
    /**
     * @brief GetInstance
     * {Gets a pointer to the IOBus singleton. If IOBus hasn't been instantiated yet
     * it constructs it and then returns a pointer to it.}
     * @return {Pointer to IOBus singleton instance.}
     */
    static IOBus* GetInstance();
    // TODO -- Might probably need a copy constructor, since this class is
    // going to be managed chiefly by value.
    /**
     * @brief AttachIOChannel
     * {Inserts an IOChannel to the list of attached IOChannels to the singleton.}
     * @param pChannel {IOChannel to be inserted.}
     */
    void AttachIOChannel(IOChannel *pChannel);
    /**
     * @brief DetachIOChannel
     * {Removes an IOChannel from the list of attached IOChannels to the singleton.}
     * @param pChannel {IOChannel to be removed.}
     */
    void DetachIOChannel(IOChannel *pChannel);
    /**
     * @brief GetIOChannel
     * {Gets the IOChannel from the attached set whose address range corresponds to the address provided.}
     * @param address {Specifies an address which identifies the address space of an attached IOChannel.}
     * @return {The corresponding IOChannel to the address.}
     */
    IOChannel* GetIOChannel(word address) const;
    /**
     * @brief SetIRQLine
     * {Sets the IRQ line high, signalling there is a new pending IRQ.}
     */
    void SetIRQLine();
    /**
     * @brief ClearIRQLine
     * {Sets the IRQ line low, signalling there are no new pending IRQs. This is usually done when
     * Cpu acknowledges an IRQ.}
     */
    void ClearIRQLine();
    /**
     * @brief IRQLine
     * {Obtains the current state of the IRQLine.}
     * @return  {True if the IRQ line is high, false if it is low.}
     * \sa CpuChannel::ReadIRQLineState
     */
    bool IRQLine() const;
    /**
     * @brief Write
     * {Writes data to an IOComponent register based on a given address.}
     * @param address {Address of the IOComponent register.}
     * @param value {Value to be written in the IOComponent register.}
     */
    void Write(word address, byte value);
    /**
     * @brief Read
     * {Reads data from an IOComponent register based on a given address.}
     * @param address {Address of the IOComponent register.}
     * @return {Value of the IOComponent register.}
     */
    byte Read(word address);
private:
    // Both ends of the channel have a reference to it.
    /**
     * @brief m_attachedIOChannels
     * {List of IOChannels attached to the singleton.}
     */
    std::vector<std::shared_ptr<IOChannel>> m_attachedIOChannels;
    /**
     * @brief pInstance
     * Pointer to the singleton instance.
     */
    static IOBus* pInstance;
    /**
     * @brief m_irqLine
     * {IRQ line variable.}
     * \sa IOBus::SetIRQLine
     * \sa IOBus::ClearIRQLine
     * \sa IOBus::IRQLine
     */
    bool m_irqLine;
    // bool m_nmiLine;
    DISALLOW_COPY_AND_ASSIGN(IOBus);
    IOBus();
    ~IOBus();
};

#endif /* IOBUS_H */
