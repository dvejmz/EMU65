#include <QThread>
#include "cpu.h"

// TODO -- Is there a better way to implement the basic multithreading?
/**
 * This class is necessary to implement a basic multithreaded execution model for the
 * execution of the emulator. Keeps the UI thread separate from the code execution thread
 * so the UI can be updated successfully.
 */
class CpuQtThread : public QThread
{
  Q_OBJECT

protected:
  void run();
};
