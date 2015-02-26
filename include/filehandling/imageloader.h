#ifndef ROMLOADER_H
#define ROMLOADER_H

#include <fstream>
#include <utility>
#include "../globals.h"

typedef std::pair<word, byte> data_pair;

class ImageLoader
{
 public:
    ImageLoader();
    ImageLoader(const std::string &filePath);
    ~ImageLoader();
    byte* ImageContents();
 private:
    std::string m_filePath;
    //byte *m_imageContents; // Array of sequential bytes containing the entire image.
    byte *m_imageContents;

    DISALLOW_COPY_AND_ASSIGN(ImageLoader);
    std::ifstream GetImageFile(const std::string &filePath) const;
    unsigned long GetImageSize(std::ifstream &fin) const;
    void ReadImageContents(std::ifstream &fin);
};

#endif /* ROMLOADER_H */
