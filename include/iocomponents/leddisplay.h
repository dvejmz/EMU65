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
    static const word MIN_ADDR;
    static  const word MAX_ADDR;

    static const word RA_ADDR;
    static const word RB_ADDR;

    static const word RA_W;
    static const word RA_DS5;
    static const word RA_DS4;
    static const word RA_DS3;
    static const word RA_DS2;
    static const word RA_DS1;
    static const word RA_A1;
    static const word RA_A0;

    static const word RB_CU;

    static const word DS1_ADDR;
    static const word DS2_ADDR;
    static const word DS3_ADDR;
    static const word DS4_ADDR;
    static const word DS5_ADDR;
    static const byte DISPLAY_MASK;

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
