#ifndef IOCOMPONENT_H
#define IOCOMPONENT_H

#include <map>
#include <vector>
#include <memory>
#include <utility>
#include "../globals.h"
#include "../debug/aiminspector.h"

typedef std::pair<word, byte> data_pair;

// For the moment I cannot think of a reason why IOComponent should be
// an ABC. Why do that when you can just do 'IOComponent ram' for example?
// You can easily subclass IOComponent to provide specialise behaviour
// for Printer and Cassette but use it as-is for RAM.
/**
 * Input/Output component with no IRQ capabilities.
 */
class IOComponent
{
 public:
    IOComponent();

    /**
     * Default constructor.
     */
    IOComponent(const byte *registers, const word minAddress, const word maxAddress);
    /**
     * This constructor accepts an allocated address range for the IOComponent as parameters
     * and constructs a dictionary of registers initialised to a passive state.
     */
    IOComponent(const word minAddress, const word maxAddress);
    virtual ~IOComponent();
    /**
     * Obtains an AddressRange struct conaining the minimum and maximum address on which the
     * IOComponent instance operates.
     * @return An AddressRange struct identifying the address space bounds of the IOComponent instance.
     * @see IOChannel::GetAddressRange
     **/
    std::vector<word> GetAddressRange() const;

    void SetAddressRange();

    /**
     * Gets the value of the register identified at the specified address.
     * @param address Address of the register to retrieve.
     * @return Value of the register specified by \a address.
     */
    virtual byte GetRegisterValue(word address);
    /**
     * Sets the value of the register specified in \a address with \a value.
     * @param address Address of the register to modify.
     * @param value New value of the register.
     */
    virtual void SetRegister(word address, byte value);
    /**
     * Clears the contents of the instance registers completely.
     */
    void Clear();

    void RemoveRegister(word address);

    virtual void UpdateDebugStatus(word address);

    std::string DumpMemory();
    std::string DumpMemory(word address);

protected:
    /**
     * Contains all addresses allocated to the IOComponent.
     */
    std::vector<word> m_addressRange;
    /**
     * Contains the registers for the IOComponent, indexed by address.
     */
    std::map<word, byte> m_registers;

private:
    DISALLOW_COPY_AND_ASSIGN(IOComponent);
};

#endif /* IOCOMPONENT_H */
