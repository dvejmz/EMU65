#ifndef CHANNEL_H
#define CHANNEL_H

#include <memory>
#include "../globals.h"

class IOBus;

/**
 * @brief The Channel class
 * {ABC which defines the interface of any channel.}
 */
class Channel
{
 public:
    /**
     * @brief Channel
     * {Default constructor.}
     * @param bus {Pointer to the IOBus singleton with which
     * the channel will communicate.}
     */
    Channel(IOBus *bus);
    /**
     * @brief ~Channel
     * {Default destructor.}
     */
    virtual ~Channel();
    /**
     * @brief Write
     * {Stores a byte in memory.}
     * @param address {Address where \a value will be stored.}
     * @param value {Value to store in \a address.}
     */
    virtual void Write(word address, byte value) const = 0;
    /**
     * @brief Read
     * {Reads a byte from memory.}
     * @param address {Address from which the byte is to be retrieved.}
     * @return {The read byte from memory.}
     */
    virtual byte Read(word address) = 0;
  
 protected:
    /**
     * @brief m_bus
     * {Pointer to the IOBus instance with which the channel communicates.}
     */
    IOBus *m_bus;
};

#endif /* CHANNEL_H */
