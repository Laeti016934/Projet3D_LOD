#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "triangle.h"
#include "objectfileformathandler.h"

class Mesh
{

public:

    Mesh();

    void load(std::string const &filename, bool load_normals = true);
    void initTriangleMesh();

    const std::vector<glm::vec3> &positions() const;
    const std::vector<glm::vec3> &normals() const;
    const std::vector<Triangle> &triangles() const;

private:

    std::vector<glm::vec3> m_positions;
    std::vector<glm::vec3> m_normals;
    std::vector<Triangle> m_triangles;
};
