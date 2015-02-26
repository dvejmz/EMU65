#ifndef AUDIOTAPE_H
#define AUDIOTAPE_H

#include "iocomponentirq.h"

class AudioTape : public IOComponentIRQ
{
public:
  AudioTape();
  AudioTape(const byte *registers, const word minAddress, const word maxAddress);
  AudioTape(const word minAddress, const word maxAddress);
  ~AudioTape();
private:
  const static std::string DEFAULT_TAPEFILES_FOLDER_PATH;
  const static std::string AIM65_AUDIOTAPE_FILE_EXTENSION;

  const static word UDRB_ADDR = 0xA000;
  const static word URBA_ADDR = 0xA00F;
};

#endif /* AUDIOTAPE_H */
