#pragma once

#include <GL/glew.h>
#include <GL/glut.h>

#include "openglmesh.h"
#include "scene.h"

class OpenGLRenderer
{
public:
    OpenGLRenderer();
    ~OpenGLRenderer();

    void initialize();

    void uploadScene(const Scene &scene);
    void unloadScene();

    void updateLightUniforms() const;
    void updateCameraUniforms(const Scene &scene) const;
    void displayScene(const Scene &scene);

    void toggleDisplayNormals();

    std::vector<OpenGLMesh> m_openGLMeshes;

    GLuint m_programID;
    GLuint m_modelMatrixUniformLocation, m_viewMatrixUniformLocation, m_projectionMatrixUniformLocation;

    //Global uniform locations for lights
    GLuint m_light1OrientationUniformLocation;
    GLuint m_light1AmbientUniformLocation;
    GLuint m_light1DiffuseUniformLocation;
    GLuint m_light1SpecularUniformLocation;
    GLuint m_light1EnabledUniformLocation;

    //Global buffer IDs for the triangle to draw
    GLuint m_positionBuffer, m_normalBuffer; //For 3.1 and 3.2
    GLuint m_elementBuffer; //For 3.2

    bool m_display_normals;

    unsigned int m_screenWidth;
    unsigned int m_screenHeight;

private:

    void fetchUniformLocations();
};
