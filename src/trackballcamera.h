#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class TrackballCamera
{
public:

    TrackballCamera();

    void resize(unsigned int width, unsigned int height);
    void beginRotate(int x, int y);
    void rotate(int x, int y);
    void move(float dx, float dy);
    void zoom(float delta);

    glm::mat4 view() const;
    glm::mat4 perspective() const;
    glm::vec3 position() const;

private:

    float m_theta;
    float m_phi;
    float m_radius;

    float m_fov;
    float m_aspectRatio;
    float m_nearPlane;
    float m_farPlane;

    glm::vec3 m_target;

    int m_lastMouseX;
    int m_lastMouseY;
};
