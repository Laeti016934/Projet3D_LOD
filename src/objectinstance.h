#pragma once

#include "openglmesh.h"
#include <memory>

class ObjectInstance
{
public:

    enum PrimitiveInfo
    {
        Mesh = 0,
        Sphere = 1,
        Square = 2
    };

    using MeshID = uint32_t;

    ObjectInstance(MeshID index, PrimitiveInfo primitiveInfo = Mesh);
    ~ObjectInstance();

    void rebaseTransform(glm::mat4 transform = glm::mat4(1.0f));

    void setScaling(const glm::vec3 &scaling);
    void setTranslation(const glm::vec3 &translation);
    void setRotation(const glm::vec3 &rotation);

    MeshID meshID() const;
    const glm::mat4& modelMatrix() const;

    const glm::vec3 &scaling() const;
    const glm::vec3 &translation() const;
    const glm::vec3 &rotation() const;

private:

    void updateTransform();

    MeshID m_meshID; //References the ID of a mesh representing the object.
    PrimitiveInfo m_primitiveInfo;
    glm::mat4 m_modelMatrix;
    glm::vec3 m_scaling;
    glm::vec3 m_translation;
    glm::vec3 m_rotation;
};
