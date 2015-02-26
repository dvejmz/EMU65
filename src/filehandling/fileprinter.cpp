#include "../../include/filehandling/fileprinter.h"

const std::string FilePrinter::DEFAULT_PRINTING_PATH = "../../res/printer.txt";

FilePrinter::FilePrinter(byte *buffer, int numChars) : m_buffer(buffer), m_numChars(numChars)
{
}

FilePrinter::~FilePrinter()
{
}

void FilePrinter::Print(const std::string filePath) const
{
    std::ofstream fout(filePath, std::ios_base::out | std::ios_base::app);
    if (fout.is_open())
    {
        for (int i = 0; i < this->m_numChars; ++i)
        {
            if (this->m_buffer[i])
            fout.put(this->m_buffer[i]);
        }

        fout << std::endl;
        fout.close();
    }
}
