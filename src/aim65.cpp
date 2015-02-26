#include "../include/aim65.h"

/** AIM-65 Full Address Space ********************************************/
/**                                                                     **/
/** 0x0000-0x03FF (RAM)                                                 **/
/** X - 0x0400-0x9FFF (ONBOARD AND OFFBOARD OPTIONAL MEMORY EXPANSION)  **/
/** 0xA000-0xA00F (TAPE)                                                **/
/** 0xA480-0xA497 (KB W/ GAPS)                                          **/
/** 0xAC00-0xAC43 (LED W/ GAPS)                                         **/
/** 0xA400-0xA47F (RIOT MONITOR RAM)                                    **/
/** 0xA800-0xA80F (PRINTER)                                             **/
/** X - 0xB000-0XCFFF (BASIC ROM)                                       **/
/** X - 0xD000-0xDFFF (ASSEMBLER ROM)                                   **/
/** 0xE000-0xFFFF (MONITOR ROM)                                         **/
/**                                                                     **/
/** X : Not implemented.                                                **/
/*************************************************************************/

Aim65* Aim65::pInstance = nullptr;

Aim65::Aim65()
{
    // Power Off. RUN/STEP switch set to RUN.
    this->m_panel.powerSwitch = false;
    this->m_panel.runStepSwitch = true;
}

Aim65::~Aim65()
{
}

Aim65* Aim65::GetInstance()
{
    if (Aim65::pInstance == nullptr)
    {
        Aim65::pInstance = new Aim65();
    }

    return Aim65::pInstance;
}

void Aim65::Initialise()
{
    this->RunSystemBootstrap();
}

void Aim65::RunSystemBootstrap()
{
    // Cold Reset Bootstrap Sequence
    // Vector to RSET -> RSET 0xE0BF -> Clear Dec Mode, Dis IRQ
    // Initialise: Stack Pointer, R6522 (Z32), R6532 (Z33)
    // Initialise: NMIV2, IRQV2, DILINK, TSPEED, GAP, NPUL, TIMG, REGF, DISFLG, BKFLG, PRIFLG
    // Initialise Monitor Variables -> Initialise R6520 (U1)
    // KB or TTY? (It will always be KB)
    // (If TTY: Measure TTY to AIM65 Bit Transmission Rate)
    // Display "ROCKWELL AIM 65"
    // START
    this->InitialiseIOComponents();
    this->InitialiseCpu();
}

void Aim65::InitialiseCpu()
{
    CpuChannel *pChannel = new CpuChannel(IOBus::GetInstance());
    Cpu *cpu = Cpu::GetInstance();
    cpu->BindChannel(pChannel);
}

void Aim65::InitialiseIOComponents()
{
    this->InitialiseRamMemory();
    this->InitialiseRom();
    this->InitialiseKeyboard();
    this->InitialiseMonitorRiotRam();
    this->InitialisePrinter();
    this->InitialiseAudioTape();
    this->InitialiseLedDisplay();
}

void Aim65::InitialiseRamMemory()
{
    // RAM addresses are initialised entirely by monitor. The code has no awareness whatsoever of any mapping here.
    // Harcoded mappings are reserved for IO components with actual registers and buffers.
    // There are two different RAM address spaces: the actual RAM address space (0x0000-0x0FFF)
    // initialised here, which belongs to RamMemory, and the RAM portion in the Z33 R6532 RIOT module,
    // which provides memory and an interface to the keyboard.
    // User and System RAM Address Space: 0x0000-0x01FF (Pages 1 & 2)
    const word ramStartAddr = 0x0000;
    const word ramEndAddr = 0x03FF;
    IOComponent *ramMemory = new IOComponent(ramStartAddr, ramEndAddr);
    IOChannel *ramChannel = new IOChannel(IOBus::GetInstance());
    ramChannel->BindComponent(ramMemory);
}

void Aim65::InitialiseRom()
{
    this->InitialiseMonitorRom();
    // Initialise optional ROM modules (assembler, BASIC, PASCAL, FORTH, PL65, etc.).
}

void Aim65::InitialiseMonitorRom()
{
    // Monitor ROM (Z32 and Z22 respectively): 0xE000-0xFFFF (0x1FFF in size).
    // Start Vector: 0xFFFA-0xFFFB, which points to 0xE0BF.
    const word monitorStartAddr = 0xE000;
    const word monitorEndAddr = 0xFFFF;
    ImageLoader monitorImgLoader(MONITOR_IMAGE_PATH);
    IOComponent *monitorRom = new IOComponent(monitorImgLoader.ImageContents(), monitorStartAddr, monitorEndAddr);
    // Remove the printer buffer register so the Printer class can respond.
    //monitorRom->RemoveRegister(0xF08C);
    IOChannel *monitorRomChannel = new IOChannel(IOBus::GetInstance());
    monitorRomChannel->BindComponent(monitorRom);
}

void Aim65::InitialiseMonitorRiotRam()
{
    // Monitor RAM Address Space: 0xA400-0xA47F
    // 0xA460: Printer Buffer.
    // 0xA438: Display Buffer.
    const word monitorRamStartAddr = 0xA400;
    const word monitorRamEndAddr = 0xA47F;
    IOComponent *monitorRam = new IOComponent(monitorRamStartAddr, monitorRamEndAddr);
    IOChannel *monitorRamChannel = new IOChannel(IOBus::GetInstance());
    monitorRamChannel->BindComponent(monitorRam);
}

void Aim65::InitialisePrinter()
{
    // Printer Address Space: 0xA800-0xA80F.
    const word minPrinterAddr = 0xA800;
    const word maxPrinterAddr = 0xA80F;
    Printer *printer = new Printer(minPrinterAddr, maxPrinterAddr);
    IOChannel *printerChannel = new IOChannel(IOBus::GetInstance());
    printerChannel->BindComponent(printer);
    printer->BindChannel(printerChannel);
}

void Aim65::InitialiseAudioTape()
{
    // Z1 R6522 User VIA (Audio Tape) address space: 0xA000-0xA00F.
    const word minAudioTapeAddr = 0xA000;
    const word maxAudioTapeAddr = 0xA00F;

    AudioTape *audioTape = new AudioTape(minAudioTapeAddr, maxAudioTapeAddr);
    IOChannel *audioTapeChannel = new IOChannel(IOBus::GetInstance());
    audioTapeChannel->BindComponent(audioTape);
    audioTape->BindChannel(audioTapeChannel);
}

void Aim65::InitialiseKeyboard()
{
    const word MIN_KEYBOARD_ADDR = 0xA480;
    const word MAX_KEYBOARD_ADDR = 0xA497;

    Keyboard *keyboard = new Keyboard(MIN_KEYBOARD_ADDR, MAX_KEYBOARD_ADDR);
    IOChannel *keyboardChannel = new IOChannel(IOBus::GetInstance());
    keyboardChannel->BindComponent(keyboard);
    keyboard->BindChannel(keyboardChannel);
    KeyboardProxy *keyboardProxy = new KeyboardProxy(keyboard);
}

void Aim65::InitialiseLedDisplay()
{
    LedDisplayProxy *proxy = new LedDisplayProxy(5, 4);
    LedDisplay *ledDisplay = new LedDisplay(proxy);
    IOChannel *ledChannel = new IOChannel(IOBus::GetInstance());
    ledChannel->BindComponent(ledDisplay);
}

void Aim65::SetPowerSwitch(bool newState)
{
    this->m_panel.powerSwitch = newState;
}

void Aim65::SetRunStepSwitch(bool newState)
{
    this->m_panel.runStepSwitch = newState;
}
