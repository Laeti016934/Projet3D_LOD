#include "mesh.h"

Mesh::Mesh() :
    m_positions(),
    m_normals(),
    m_triangles()
{}

void Mesh::load(std::string const &filename, bool load_normals)
{
    openOFF(filename, m_positions, m_normals, m_triangles, load_normals);
}

void Mesh::initTriangleMesh()
{
    std::vector<glm::vec3> positionData
    {
        glm::vec3(-1.0f, -1.0f, 0.0f),
        glm::vec3(1.0f, -1.0f, 0.0f),
        glm::vec3(1.0f,  1.0f, 0.0f),
    };

    std::vector<glm::vec3> colorData
    {
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 1.0f),
    };

    m_positions = positionData;
    m_normals = colorData;
    m_triangles.push_back( Triangle(0,1,2) );
}

const std::vector<glm::vec3> &Mesh::positions() const
{
    return m_positions;
}

const std::vector<glm::vec3> &Mesh::normals() const
{
    return m_normals;
}

const std::vector<Triangle> &Mesh::triangles() const
{
    return m_triangles;
}



