#ifndef FILEPRINTER_H
#define FILEPRINTER_H

#include <fstream>
#include "../globals.h"

class FilePrinter
{
public:
    FilePrinter(byte *buffer, int numChars);
    ~FilePrinter();
    void Print(const std::string filePath = DEFAULT_PRINTING_PATH) const;
private:
    static const std::string DEFAULT_PRINTING_PATH;
    std::string m_filePath;
    byte *m_buffer;
    int m_numChars;

    DISALLOW_COPY_AND_ASSIGN(FilePrinter);
};

#endif /* FILEPRINTER_H */
