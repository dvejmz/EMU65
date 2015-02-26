#ifndef IOCOMPONENTIRQ_H
#define IOCOMPONENTIRQ_H

#include "iocomponent.h"
#include "iochannel.h"

/**
 * @brief The IOComponentIRQ class
 * {Input/Output component capable of issuing IRQs to the processor.}
 */
class IOComponentIRQ : public IOComponent
{
public:
    IOComponentIRQ();

    IOComponentIRQ(const byte *registers, const word minAddress, const word maxAddress);

    IOComponentIRQ(const word minAddress, const word maxAddress);

    virtual ~IOComponentIRQ();
    /**
   * @brief SignalIRQ
   * {Creates an IRQ signal to be issued through its attached IOChannel.}
   */
    void SignalIRQ() const;
    /**
   * @brief BindChannel
   * {Attach an IOChannel instance to allow for communication with IOBus.}
   * @param channel {Channel to attach to the IOCompnentIRQ instance.}
   */
    void BindChannel(IOChannel *channel);
protected:

    /**
     * @brief m_channel
     */
    std::shared_ptr<IOChannel> m_channel;
private:
    DISALLOW_COPY_AND_ASSIGN(IOComponentIRQ);
};

#endif /* IOCOMPONENTIRQ_H */
