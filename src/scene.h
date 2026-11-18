#pragma once

#include "objectinstance.h"
#include "trackballcamera.h"

class Scene
{
public:
    Scene();

    using MeshID = uint32_t;
    using ObjectInstanceID = uint32_t;

    MeshID addMesh(const Mesh &mesh);
    ObjectInstanceID uploadObjectInstance(const ObjectInstance &objectInstance);

    TrackballCamera &camera() { return m_camera; }
    const TrackballCamera &camera() const { return m_camera; }

    const std::vector<Mesh> &meshes() const { return m_meshes; }
    const std::vector<ObjectInstance> &objectInstances() const { return m_objectInstances; }

    Mesh &mesh(MeshID meshID) { return m_meshes[meshID]; }
    const Mesh &mesh(MeshID meshID) const { return m_meshes[meshID]; }

    ObjectInstance &objectInstance(ObjectInstanceID objectInstanceID) { return m_objectInstances[objectInstanceID]; }
    const ObjectInstance &objectInstance(ObjectInstanceID objectInstanceID) const { return m_objectInstances[objectInstanceID]; }

private:

    //TODO: add whatever you need in the scene (lights for instance).

    TrackballCamera m_camera;
    std::vector<Mesh> m_meshes;
    std::vector<ObjectInstance> m_objectInstances;
};
