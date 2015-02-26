#include <QThread>
#include "cpu.h"

class CpuQtThread : public QThread
{
  Q_OBJECT

protected:
  void run();
};
