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
 * @brief The IOComponent class
 * {Input/Output component with no IRQ capabilities.}
 */
class IOComponent
{
 public:
    IOComponent();

    /**
     * @brief IOComponent
     * {Default constructor.}
     * @param registers {Dictionary of potentially initialised values indexed by address.}
     */
    IOComponent(const byte *registers, const word minAddress, const word maxAddress);
    /**
     * @brief IOComponent
     * {This constructor accepts an address range as parameters and constructs an empty dictionary.}
     * @param minAddress {Lowest address.}
     * @param maxAddress {Highest address.}
     */
    IOComponent(const word minAddress, const word maxAddress);
    virtual ~IOComponent();
    /**
     * @brief GetAddressRange
     * {Obtains an AddressRange struct conaining the minimum and maximum address on which the
     * IOComponent instance operates.}
     * @return {An AddressRange struct identifying the address space bounds of the IOComponent instance.}
     * \sa IOChannel::GetAddressRange
     **/
    std::vector<word> GetAddressRange() const;

    void SetAddressRange();

    /**
     * @brief GetRegisterValue
     * {Gets the value of the register identified at the specified address.}
     * @param address {Address of the register to retrieve.}
     * @return {Value of the register specified by \a address.}
     */
    virtual byte GetRegisterValue(word address);
    /**
     * @brief SetRegister
     * {Sets the value of the register specified in \a address with \a value.}
     * @param address {Address of the register to modify.}
     * @param value {New value of the register.}
     */
    virtual void SetRegister(word address, byte value);
    /**
     * @brief Clear
     * {Clears the contents of the instance registers completely.}
     */
    void Clear();

    void RemoveRegister(word address);

    virtual void UpdateDebugStatus(word address);

    std::string DumpMemory();
    std::string DumpMemory(word address);

protected:
    /**
     * @brief m_addressRange
     */
    std::vector<word> m_addressRange;

    /**
     * @brief m_registers
     */
    std::map<word, byte> m_registers;

private:
    DISALLOW_COPY_AND_ASSIGN(IOComponent);
};

#endif /* IOCOMPONENT_H */
