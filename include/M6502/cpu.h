/** EMU65 ***********************************************************/
/**                                                                **/
/**                             cpu.h                              **/
/**                                                                **/
/** Header file of the Cpu class, which encapsulates the 6502 libra**/
/** ries, providing a simple interface to the rest of the system.  **/
/**                                                                **/
/** David J Sequero                                                **/
/**                                                                **/
/**    Copyright (C) David J Sequero. This file is distributed unde**/
/**    r GPLv3 licensing terms, except those components conveyed b **/
/**    y Marat Fayzullin.                                          **/
/**                                                                **/
/********************************************************************/
#ifndef CPU_H
#define CPU_H

#include <memory>
#include "../globals.h"
#include "../iocomponents/cpuchannel.h"
#include "M6502.h"

#ifdef DEBUG
#include "../debug/aiminspector.h"
#endif

class Cpu
{
 public:
  /**
   * @brief GetInstance
   * {Gets a pointer to the Cpu singleton. If Cpu hasn't been instantiated yet
   * it constructs it and then returns a pointer to it.}
   */
  static Cpu* GetInstance();

  /**
   * @brief Run
   * {Starts CPU execution by relaying the 'Run' command to the
   * encapsulated 6502 CPU.}
   */
  void Run();

  void Halt();

  /**
   * @brief Read
   * {Retrieve a byte from the specified memory address.}
   * @param address {Address of the word to be read from memory.}
   * @return {The value stored in the specified address.}
   */
  byte Read(word address);

  /**
   * @brief Write
   * {Write a byte to the specified memory address.}
   * @param address {Address of the word to be written to memory.}
   * @param value {Value to be stored at the specified address.}
   */
  void Write(word address, byte value) const;

  /**
   * @brief Reset
   * {Resets CPU registers by relaying the 'Reset' command to the
   * encapsulated 6502 CPU. Coupled with Reset6502() in M6502.}
   */
  void Reset();

  /**
   * @brief CheckInterrupts
   * {Coupled with Loop6502() in M6502.}
   * @return
   */
  byte CheckInterrupts();

  /**
   * @brief ProcessUnknownCode
   * {Coupled with Patch6502() in M6502.}
   * @return
   */
  byte ProcessUnknownCode();

  /**
   * @brief ServiceInterrupt
   * {Coupled with Int6502() in M6502.}
   * @param type
   */
  void ServiceInterrupt(byte type);

  /**
   * @brief ServiceIRQ
   */
  void ServiceIRQ();

  /**
   * @brief ServiceNMI
   */
  void ServiceNMI();

  /**
   * @brief ExecuteOpcode
   * {Coupled with Exec6502() in M6502.}
   * @param runCycles
   * @return
   */
  int ExecuteOpcode(int runCycles);

  #ifdef DEBUG

  /**
   * @brief GetInspector
   * @return
   */
  AimInspector* GetInspector();

  /**
   * @brief GetDebugData
   * @return
   */
  std::string GetCpuDebugData();
  std::string DumpMemory(word Addr);

  /**
   * @brief UpdateDbgStatus
   * @return
   */
  byte UpdateDbgStatus();

  #endif

  /**
   * @brief BindChannel
   * @param channel
   */
  void BindChannel(CpuChannel *channel);

 private:
  /**
   * @brief pInstance
   */
  static Cpu* pInstance;

  /**
   * @brief m_cpu
   */
  M6502 m_cpu;

  /**
   * @brief m_channel
   */
  std::unique_ptr<CpuChannel> m_channel;
  
  DISALLOW_COPY_AND_ASSIGN(Cpu);

  /** Cpu()
   ** Sets up any system-wide variables which affect CPU execution
   ** and then issues the 'Init' command to the encapsulated 6502 CPU. 
   ** Kept private to ensure singleton implementation of the class. 
   ** It can only be called from Initialise(). **/
  /**
   * @brief Cpu
   */
  Cpu();

  /**
   * @brief ~Cpu
   */
  ~Cpu();

  bool m_halt;
};

#endif /* CPU_H */
