#pragma once

#include "mesh.h"
#include <GL/glew.h>
#include <GL/glut.h>

GLenum glCheckError_(const char *file, int line);
//Use macro glCheckError() when something in OpenGL does not work to pinpoint a potential error.
#define glCheckError() glCheckError_(__FILE__, __LINE__)

class OpenGLMesh
{
public:

    OpenGLMesh();
    OpenGLMesh(const Mesh &mesh);

    void loadMesh(const Mesh &mesh);
    void clearBuffers();

    void draw() const;

    void debugDrawNormals(const Mesh &mesh, float normalScale = 0.02f) const;


private:

    void debugDrawVector(glm::vec3 const & i_from, glm::vec3 const & i_to) const;

    GLuint m_positionBuffer, m_normalBuffer, m_elementbuffer;
    GLuint m_vao;
    unsigned int m_vertexCount;
};
