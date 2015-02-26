#include "../../include/M6502/cpuqthread.h"

void CpuQtThread::run()
{
  Cpu::GetInstance()->Run();
}
