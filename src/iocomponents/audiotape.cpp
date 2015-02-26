#include "../../include/iocomponents/audiotape.h"

/** User VIA R6522 - Audio Tape Module Address Space ********************/
/**                                                                    **/
/** 0xA000 - UDRB: Data Register B (PB0-PB7).                          **/
/**     4: PB4 -> J1-W TAPE IA, J1-F TAPE IB, J1-E TAPE IB RETURN      **/
/**     5: PB5 -> J1-V TAPE 2A, J1-J TAPE 2B, J1-H TAPE 2B RETURN      **/
/**     7: PB7 -> J1-L AUDIO IN, J1-P AUDIO OUT HI, J1-M AUDIO OUT LO  **/
/** 0xA001 - UDRAH: Data Register A (PA0-PA7)(Handshake)               **/
/** 0xA002 - UDDRB: Data Direction Register B.                         **/
/** 0xA003 - UDDRA: Data Direction Register A.                         **/
/** 0xA004 -                                                           **/
/** 0xA005 -                                                           **/
/** 0xA006 -                                                           **/
/** 0xA007 -                                                           **/
/** 0xA008 -                                                           **/
/** 0xA009 -                                                           **/
/** 0xA00A - USR: Shift Register (SR)                                  **/
/** 0xA00B - UACR: Auxiliary Control Register (ACR)                    **/
/** 0xA00C - UPCR: Peripheral Control Register (PCR)                   **/
/**     0: CA1 | 1-3: CA2 | 4: CB1 | 5-6: CB2                          **/
/** 0xA00D - UIFR: Interrupt Flag Register (IFR)                       **/
/** 0xA00E - UIER: Interrupt Enable Register (IER)                     **/
/** 0xA00F - UDRA: Data Register A (No Handshake)                      **/
/************************************************************************/

const std::string AudioTape::DEFAULT_TAPEFILES_FOLDER_PATH = "../../res/";
// 'aat' stands for Aim Audio Tape.
const std::string AudioTape::AIM65_AUDIOTAPE_FILE_EXTENSION = "aat";

AudioTape::AudioTape() : IOComponentIRQ()
{
}

AudioTape::AudioTape(const byte *registers, const word minAddress, const word maxAddress)
    : IOComponentIRQ(registers, minAddress, maxAddress)
{
}

AudioTape::AudioTape(const word minAddress, const word maxAddress)
    : IOComponentIRQ(minAddress, maxAddress)
{
}

AudioTape::~AudioTape()
{
}
