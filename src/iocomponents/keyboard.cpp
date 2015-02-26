#include "../../include/iocomponents/keyboard.h"

/** Keyboard Adrress Mappings **********************************************/
/**                                                                       **/
/** NOTE: There is a gap between 0xA488-0xA493 incl.                      **/
/** KEY:                                                                  **/
/**  KI : Keyboard Input.                                                 **/
/**  KO : Keyboard Output.                                                **/
/**                                                                       **/
/** 0xA480 - DRA2: Data Register A (KI1-KI8). Pressed: 0, Unpressed: 1.   **/
/** 0xA481 - DDRA2: Data Direction Register A.                            **/
/** 0xA482 - DRB2: Data Register B (KO1-KO8). Pressed: 0, Unpressed: 1.   **/
/** 0xA483 - DDRB2: Data Direction Register B.                            **/
/** 0xA484 - DNPA7: Write Disable PA7 Interrupt Negative Edge Detect.     **/
/** 0xA485 - DPPA7: Write Disable PA7 Interrupt Positive Edge Detect.     **/
/** 0xA486 - RINT: Read Bit 7 = Timer Flag, Bit 6 = PA7 Flag, Clear Int.  **/
/** 0xA486 - ENPA7: Write Enable PA7 Interrupt, Negative Edge Detect.     **/
/** 0xA487 - EPPA7: Write Enable PA7 Interrupt, Positive Edge Detect.     **/
/** 0xA494 - DIV1: Div. by 0001 (Disable), Add 8 to Enable.               **/
/** 0xA495 - DIV8: Div. by 0008 (Disable), Add 8 to Enable.               **/
/** 0xA496 - DIV64: Div. by 0064 (Disable), Add 8 to Enable.              **/
/** 0xA497 - DIV1024: Div. by 1024 (Disable), Add 8 to Enable.            **/
/***************************************************************************/

Keyboard::Keyboard() : IOComponentIRQ()
{
    this->m_registers.insert(std::make_pair(DRA2_ADDR, 0));
    this->m_registers.insert(std::make_pair(DRB2_ADDR, 0));
    this->m_registers.insert(std::make_pair(DNPA7_ADDR, 0));
    this->m_registers.insert(std::make_pair(DPPA7_ADDR, 0));
    this->m_registers.insert(std::make_pair(RINT_ADDR, 0));
    this->m_registers.insert(std::make_pair(ENPA7_ADDR, 0));
    this->m_registers.insert(std::make_pair(EPPA7_ADDR, 0));
    this->SetAddressRange();
}

Keyboard::Keyboard(const byte *registers, const word minAddress, const word maxAddress)
    : IOComponentIRQ(registers, minAddress, maxAddress)
{
}

Keyboard::Keyboard(const word minAddress, const word maxAddress)
    : IOComponentIRQ(minAddress, maxAddress)
{
}

bool Keyboard::IsValidChar(char ch) const
{
  // Accepted ASCII characters: 32-94.
  // '[', ']' and '^' are interpreted as F1, F2 and F3  respectively.
  return ch >= 32 && ch <= 94;
}

void Keyboard::UpdateDebugStatus(word address)
{

}

// TOTHINK -- Where should I hook up F1, F2 and F3?
void Keyboard::onKeyPressed(char ch)
{
  if (this->IsValidChar(ch))
    {
      this->SetRegister(DRB2_ADDR, static_cast<word>(ch));
      // TODO -- Check whether the state of PA7 is related to the IRQ line (6502 docs).
      this->SignalIRQ();
    }
}
