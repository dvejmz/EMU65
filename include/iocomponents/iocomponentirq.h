#ifndef IOCOMPONENTIRQ_H
#define IOCOMPONENTIRQ_H

#include "iocomponent.h"
#include "iochannel.h"

/**
 * Input/Output component capable of issuing IRQs to the processor.
 */
class IOComponentIRQ : public IOComponent
{
public:
    IOComponentIRQ();

    IOComponentIRQ(const byte *registers, const word minAddress, const word maxAddress);

    IOComponentIRQ(const word minAddress, const word maxAddress);

    virtual ~IOComponentIRQ();
    /**
     * Creates an IRQ signal to be issued through its attached IOChannel.
     */
    void SignalIRQ() const;
    /**
     * Attach an IOChannel instance to allow for communication with IOBus.
     * @param channel Channel to attach to the IOCompnentIRQ instance.
     */
    void BindChannel(IOChannel *channel);
protected:

    std::shared_ptr<IOChannel> m_channel;
private:
    DISALLOW_COPY_AND_ASSIGN(IOComponentIRQ);
};

#endif /* IOCOMPONENTIRQ_H */
