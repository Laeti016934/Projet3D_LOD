#include "trackballcamera.h"

#include <algorithm>
#include <cmath>

TrackballCamera::TrackballCamera() :
    m_theta(0.0f),
    m_phi(0.3f),
    m_radius(2.0f),
    m_fov(45.0f),
    m_aspectRatio(16.0f / 9.0f),
    m_nearPlane(0.01f),
    m_farPlane(20.0f),
    m_target(0.0f),
    m_lastMouseX(0),
    m_lastMouseY(0)
{}

void TrackballCamera::resize(unsigned int width, unsigned int height)
{
    m_aspectRatio = static_cast<float>(width) / static_cast<float>(height);
}

void TrackballCamera::beginRotate(int x, int y)
{
    m_lastMouseX = x;
    m_lastMouseY = y;
}

void TrackballCamera::rotate(int x, int y)
{
    constexpr float sensitivity = 0.01f;

    const float dx = static_cast<float>(x - m_lastMouseX);
    const float dy = static_cast<float>(y - m_lastMouseY);

    m_theta -= dx*sensitivity;
    m_phi   += dy*sensitivity;

    const float limit = glm::half_pi<float>() - 0.01f;

    m_phi = glm::clamp(m_phi, -limit, limit);

    m_lastMouseX = x;
    m_lastMouseY = y;
}

void TrackballCamera::move(float dx, float dy)
{
    glm::vec3 forward = glm::normalize(m_target - position());
    glm::vec3 right = glm::normalize(glm::cross(forward, glm::vec3(0.f, 1.f, 0.f)));
    glm::vec3 up = glm::normalize(glm::cross(right, forward));

    constexpr float speed = 2.0f;

    m_target += (-dx * right - dy * up) * speed * m_radius;
}

void TrackballCamera::zoom(float delta)
{
    constexpr float speed = 5.0f;
    m_radius += delta * speed;
    m_radius = std::max(m_radius, 0.1f);
}

glm::vec3 TrackballCamera::position() const
{
    return m_target + glm::vec3(
        m_radius * std::cos(m_phi) * std::sin(m_theta),
        m_radius * std::sin(m_phi),
        m_radius * std::cos(m_phi) * std::cos(m_theta)
    );
}

glm::mat4 TrackballCamera::view() const
{
    return glm::lookAt(
        position(),
        m_target,
        glm::vec3(0.f, 1.f, 0.f)
    );
}

glm::mat4 TrackballCamera::perspective() const
{
    return glm::perspective(
        glm::radians(m_fov),
        m_aspectRatio,
        m_nearPlane,
        m_farPlane
    );
}
