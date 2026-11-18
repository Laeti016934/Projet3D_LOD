#pragma once

#include <string>
#include <vector>

#include <glm/glm.hpp>

class ImageRGB
{
public:

    ImageRGB();
    ImageRGB(unsigned int width, unsigned int height);

    bool load(const std::string& filename);
    bool save(const std::string& filename) const;

    void resize(unsigned int width, unsigned int height);

    unsigned int width() const { return m_width; }
    unsigned int height() const { return m_height; }

    glm::vec3& pixel(unsigned int x, unsigned int y);
    const glm::vec3& pixel(unsigned int x, unsigned int y) const;

private:

    unsigned int m_width;
    unsigned int m_height;

    std::vector<glm::vec3> m_pixels;
};