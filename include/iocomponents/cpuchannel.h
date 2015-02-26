#ifndef CPUCHANNEL_H
#define CPUCHANNEL_H

#include "channel.h"
#include "iobus.h"

/**
 * @brief The CpuChannel class
 * {Unique channel used to relay data to and from the Cpu instance it is bound to.}
 */
class CpuChannel : public Channel
{
 public:
    /**
     * @brief CpuChannel
     * \sa Channel
     */
    CpuChannel(IOBus *bus);
    /**
     * @brief ~CpuChannel
     * \sa ~Channel
     */
    virtual ~CpuChannel();
    /**
     * @brief ReadIRQLineState
     * {Reads the state of the IRQ line in IOBus.}
     * @return {True if it is high (pending IRQ) and false if it is low (no IRQ).}
     */
    bool ReadIRQLineState() const;
    /**
     * @brief Write
     * \sa {Channel::Write(word,byte)}
     */
    virtual void Write(word address, byte value) const;
    /**
     * @brief Read
     * \sa {Channel::Read(word)}
     */
    virtual byte Read(word address);
 private:
    DISALLOW_COPY_AND_ASSIGN(CpuChannel);
};

#endif /* CPUCHANNEL_H */
