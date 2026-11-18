#include "scene.h"


Scene::Scene() :
    m_camera(),
    m_meshes(),
    m_objectInstances()
{
    m_camera.resize (1600, 900);
}

Scene::MeshID Scene::addMesh(const Mesh &mesh)
{
    m_meshes.push_back(mesh);
    return static_cast<MeshID>(m_meshes.size() - 1);
}

Scene::ObjectInstanceID Scene::uploadObjectInstance(const ObjectInstance &objectInstance)
{
    //emplace_back() constructs an object directly in a std::vector with the parameters expected by its constructor.
    //avoids an intermediate copy.

    //Get rotation, scaling, translations from modelMatrix
    m_objectInstances.push_back(objectInstance);
    return static_cast<ObjectInstanceID>(m_objectInstances.size() - 1);
}