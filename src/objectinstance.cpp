#include "objectinstance.h"

ObjectInstance::ObjectInstance(MeshID index, PrimitiveInfo primitiveInfo) :
    m_meshID(index),
    m_primitiveInfo(primitiveInfo),
    m_modelMatrix(1.0f),
    m_scaling(1.0f),
    m_translation(0.0f),
    m_rotation(0.0f)
{}

ObjectInstance::~ObjectInstance()
{}

void ObjectInstance::rebaseTransform(glm::mat4 transform)
{
    updateTransform();
    m_modelMatrix = transform*m_modelMatrix;
}

void ObjectInstance::setScaling(const glm::vec3 &scaling)
{
    m_scaling = scaling;
    updateTransform();
}

void ObjectInstance::setTranslation(const glm::vec3 &translation)
{
    m_translation = translation;
    updateTransform();
}

void ObjectInstance::setRotation(const glm::vec3 &rotation)
{
    m_rotation = rotation;
    updateTransform();
}

ObjectInstance::MeshID ObjectInstance::meshID() const
{
    return m_meshID;
}

const glm::mat4 &ObjectInstance::modelMatrix() const
{
    return m_modelMatrix;
}

const glm::vec3 &ObjectInstance::scaling() const
{
    return m_scaling;
}

const glm::vec3 &ObjectInstance::translation() const
{
    return m_translation;
}

const glm::vec3 &ObjectInstance::rotation() const
{
    return m_rotation;
}

void ObjectInstance::updateTransform()
{
    glm::mat4 id = glm::mat4(1.0f);
    glm::mat4 rotateX = glm::rotate(id, m_rotation.x, glm::vec3(1, 0, 0));
    glm::mat4 rotateY = glm::rotate(id, m_rotation.y, glm::vec3(0, 1, 0));
    glm::mat4 rotateZ = glm::rotate(id, m_rotation.z, glm::vec3(0, 0, 1));
    glm::mat4 scale = glm::scale(id, m_scaling);
    glm::mat4 translate = glm::translate(id, m_translation);

    //Not the same transform as the TP, but it's the most common.
    m_modelMatrix = translate*rotateX*rotateY*rotateZ*scale;
}
