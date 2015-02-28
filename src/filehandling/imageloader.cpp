#include "../../include/filehandling/imageloader.h"

ImageLoader::ImageLoader()
{
}

ImageLoader::ImageLoader(const std::string &filePath)
{
    this->m_filePath = filePath;
    m_imagestream.open(m_filePath, std::ios_base::in | std::ios_base::binary);
    this->ReadImageContents();
}

ImageLoader::~ImageLoader()
{
    m_imagestream.close();
}

unsigned long ImageLoader::GetImageSize()
{
    m_imagestream.seekg(0, std::ios_base::end);
    unsigned long fileSizeBytes = static_cast<unsigned long>(m_imagestream.tellg());
    m_imagestream.seekg(0, std::ios_base::beg);
    return fileSizeBytes;
}

byte* ImageLoader::ImageContents()
{
    return this->m_imageContents.get();
}

void ImageLoader::ReadImageContents()
{
    // TODO -- Should return 'false' if reading failed.
    if (m_imagestream.is_open())
    {
        auto imageSize = this->GetImageSize();
        auto buffer = std::unique_ptr<char[]>(new char[imageSize]);
        m_imageContents = std::unique_ptr<byte[]>(new byte[imageSize]);

        if(m_imagestream.good())
        {
            m_imagestream.read(buffer.get(), imageSize);
            for(int i = 0; i < imageSize; ++i)
            {
                this->m_imageContents.get()[i] = static_cast<byte>(buffer.get()[i]);
            }
        }
    }
}
