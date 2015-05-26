#ifndef AIM65_H
#define AIM65_H

#include <memory>
#include "globals.h"
#include "M6502/cpu.h"
#include "iocomponents/iobus.h"
#include "iocomponents/iocomponent.h"
#include "iocomponents/iocomponentirq.h"
#include "filehandling/imageloader.h"
#include "iocomponents/leddisplay.h"
#include "iocomponents/printer.h"
#include "iocomponents/audiotape.h"

// Implementation dependent headers
// These include the files necessary to interface EMU65 to a Qt Quick 2.0 QML frontend.
// They may be replaced by other frontend proxies to interface with other GUI libraries
// such as GTK+
#include "ui/leddisplayqtproxy.h"
#include "ui/keyboardqtproxy.h"

struct Aim65Panel
{
    // ON = true; OFF = false.
    bool powerSwitch;
    // RUN = true; STEP = false.
    bool runStepSwitch;
};

typedef std::pair<word, byte> data_pair;

const std::string MONITOR_IMAGE_PATH = "res/rom/AIMMON11.BIN";

class Aim65
{
public:
    Aim65();
    ~Aim65();
    static Aim65* GetInstance();
    void RunSystemBootstrap();
    void Initialise();
    void InitialiseCpu();
    void InitialiseIOComponents();
    void InitialiseRamMemory();
    void InitialiseRom();
    void InitialiseMonitorRom();
    void InitialiseMonitorRiotRam();
    void InitialisePrinter();
    void InitialiseAudioTape();
    void InitialiseKeyboard();
    void InitialiseLedDisplay();
    bool GetPowerSwitch();
    void SetPowerSwitch(bool newState);
    void SetRunStepSwitch(bool newState);

private:
    static Aim65* pInstance;
    Aim65Panel m_panel;
    DISALLOW_COPY_AND_ASSIGN(Aim65);
};

#endif /* AIM65_H */
