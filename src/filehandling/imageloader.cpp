#include "../../include/filehandling/imageloader.h"

ImageLoader::ImageLoader()
{
}

ImageLoader::ImageLoader(const std::string &filePath)
{
    this->m_filePath = filePath;
    this->ReadImageContents(this->GetImageFile(this->m_filePath));
    //filePath.copy(this->m_filePath, filePath.size());
}

ImageLoader::~ImageLoader()
{
    delete[] this->m_imageContents;
}

std::ifstream ImageLoader::GetImageFile(const std::string &filePath) const
{
    std::ifstream fin(filePath, std::ios_base::in | std::ios_base::binary);
    return fin;
}

unsigned long ImageLoader::GetImageSize(std::ifstream &fin) const
{
    fin.seekg(0, std::ios_base::end);
    unsigned long fileSizeBytes = static_cast<unsigned long>(fin.tellg());
    fin.seekg(0, std::ios_base::beg);
    return fileSizeBytes;
}

byte* ImageLoader::ImageContents()
{
    return this->m_imageContents;
}

void ImageLoader::ReadImageContents(std::ifstream &fin)
{
    // TODO -- Should return 'false' if reading failed.

    if (fin.is_open())
    {
        unsigned long imageSize = this->GetImageSize(fin);
        char *buffer = new char[imageSize];
        this->m_imageContents = new byte[imageSize];

        if(fin.good())
        {
            fin.read(buffer, imageSize);
            for(int i = 0; i < imageSize; ++i)
            {
                this->m_imageContents[i] = static_cast<byte>(buffer[i]);
            }
        }

        delete[] buffer;

        fin.close();
    }
}
