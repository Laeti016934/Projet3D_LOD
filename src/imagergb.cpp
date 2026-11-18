#include "imagergb.h"

#include <algorithm>
#include <fstream>

ImageRGB::ImageRGB() :
    m_width(0),
    m_height(0)
{
}

ImageRGB::ImageRGB(unsigned int width,
                   unsigned int height)
{
    resize(width, height);
}

void ImageRGB::resize(unsigned int width,
                      unsigned int height)
{
    m_width = width;
    m_height = height;

    m_pixels.assign(width * height, glm::vec3(0.0f));
}

glm::vec3& ImageRGB::pixel(unsigned int x,
                           unsigned int y)
{
    return m_pixels[y * m_width + x];
}

const glm::vec3& ImageRGB::pixel(unsigned int x,
                                 unsigned int y) const
{
    return m_pixels[y * m_width + x];
}

bool ImageRGB::save(const std::string& filename) const
{
    std::ofstream file(filename, std::ios::binary);

    if(!file)
        return false;

    file << "P6\n";
    file << m_width << " "
         << m_height << "\n";
    file << "255\n";

    for(const glm::vec3& c : m_pixels)
    {
        unsigned char rgb[3];

        rgb[0] = static_cast<unsigned char>(255.0f * std::clamp(c.r, 0.0f, 1.0f));
        rgb[1] = static_cast<unsigned char>(255.0f * std::clamp(c.g, 0.0f, 1.0f));
        rgb[2] = static_cast<unsigned char>(255.0f * std::clamp(c.b, 0.0f, 1.0f));

        file.write(reinterpret_cast<char*>(rgb), 3);
    }

    return true;
}

bool ImageRGB::load(const std::string& filename)
{
    std::ifstream file(filename, std::ios::binary);

    if(!file)
        return false;

    std::string magic;

    file >> magic;

    if(magic != "P6")
        return false;

    unsigned int width;
    unsigned int height;
    unsigned int maxValue;

    file >> width
        >> height
        >> maxValue;

    file.get();

    if(maxValue != 255)
        return false;

    resize(width, height);

    for(glm::vec3& c : m_pixels)
    {
        unsigned char rgb[3];

        file.read(reinterpret_cast<char*>(rgb), 3);

        c.r = rgb[0] / 255.0f;
        c.g = rgb[1] / 255.0f;
        c.b = rgb[2] / 255.0f;
    }

    return true;
}