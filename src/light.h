#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>

struct Light
{
    using Vec3 = glm::vec3;

    Light(Vec3 ambient, Vec3 diffuse, Vec3 specular, bool enabled = true) :
        ambient(ambient),
        diffuse(diffuse),
        specular(specular),
        enabled(enabled)
    {}

    Vec3 ambient;
    Vec3 diffuse;
    Vec3 specular;
    bool enabled;
};

struct DirectionalPhongLight : public Light
{
    DirectionalPhongLight(Vec3 orientation, Vec3 ambient, Vec3 diffuse, Vec3 specular, bool enabled = true) :
        Light(ambient, diffuse, specular, enabled),
        orientation(orientation)
    {}

    Vec3 orientation;
};


#endif // LIGHT_H
