#ifndef LEDDISPLAY_H
#define LEDDISPLAY_H

#include <map>
#include "iocomponent.h"
#include "../ui/leddisplayqtproxy.h"

class LedDisplay : public IOComponent
{
public:
    LedDisplay(LedDisplayProxy *proxy);
    LedDisplay(const byte *registers, const word minAddress, const word maxAddress);
    LedDisplay(const word minAddress, const word maxAddress);
    void SetRegister(word address, byte value);
    void UpdateDebugStatus(word address);

private:
    // LED display address bounds: 0xAC00-0xAC43.
    static const word MIN_ADDR = 0xAC00;
    static const word MAX_ADDR = 0xAC43;

    static const word RA_ADDR = 0xAC00;
    static const word RB_ADDR = 0xAC02;

    static const word RA_W = 0x80;
    static const word RA_DS5 = 0x40;
    static const word RA_DS4 = 0x20;
    static const word RA_DS3 = 0x10;
    static const word RA_DS2 = 0x08;
    static const word RA_DS1 = 0x04;
    static const word RA_A1 = 0x02;
    static const word RA_A0 = 0x01;

    static const word RB_CU = 0x80;

    static const word DS1_ADDR = 0xAC04;
    static const word DS2_ADDR = 0xAC08;
    static const word DS3_ADDR = 0xAC10;
    static const word DS4_ADDR = 0xAC20;
    static const word DS5_ADDR = 0xAC40;
    static const byte DISPLAY_MASK = RA_DS1 | RA_DS2 | RA_DS3 | RA_DS4 | RA_DS5; // 0x3E

    std::shared_ptr<LedDisplayProxy> m_proxy;

    DISALLOW_COPY_AND_ASSIGN(LedDisplay);
    /**
     * Decodes the address byte and returns the actual mapped register.
     * @return
     */
    std::vector<word> GetCursorTargetDisplaysFromAddrRegister();
    void OutputCursor();
    word GetTargetDisplayFromAddrRegister();
    /**
     * Returns the display and digit position corresponding to the address provided.
     * @return First element of the pair is the display position, the second one is the digit offset.
     */
    std::pair<int, int> GetDisplayDigitPair(word address) const;

    /**
     * Checks whether the address register indicates that the LED display cursor is enabled.
     * @return True if the cursor is enabled, false if it's not.
     */
    bool CursorEnabled();
};

#endif /* LEDDISPLAY_H */
