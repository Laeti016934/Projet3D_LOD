#include <iostream>
#include <string>

#include "openglmesh.h"

GLenum glCheckError_(const char *file, int line)
{
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR)
    {
        std::string error;
        switch (errorCode)
        {
            case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
            case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
            case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
            case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
            case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
            case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
        }
        std::cout << error << " | " << file << " (" << line << ")" << std::endl;
    }
    return errorCode;
}

OpenGLMesh::OpenGLMesh() :
    m_positionBuffer(0),
    m_normalBuffer(0),
    m_elementbuffer(0),
    m_vao(0),
    m_vertexCount(0)
{}

OpenGLMesh::OpenGLMesh(const Mesh &mesh) :
    m_positionBuffer(0),
    m_normalBuffer(0),
    m_elementbuffer(0),
    m_vao(0),
    m_vertexCount(0)
{
    loadMesh(mesh);
}

void OpenGLMesh::loadMesh(const Mesh &mesh)
{
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    //TODO : initialize the buffers like in section 3.2.
    //pass positions and normals as array buffers and triangles as an element buffer.
    //Remember to check glBufferData https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBufferData.xhtml
    glGenBuffers(1, &m_positionBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_positionBuffer);
    glBufferData(GL_ARRAY_BUFFER, mesh.positions().size()*sizeof(glm::vec3), &mesh.positions()[0], GL_STATIC_DRAW);

    glGenBuffers(1, &m_normalBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_normalBuffer);
    glBufferData(GL_ARRAY_BUFFER, mesh.normals().size()*sizeof(glm::vec3), &mesh.normals()[0], GL_STATIC_DRAW);

    glGenBuffers(1, &m_elementbuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementbuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.triangles().size() * sizeof(Triangle), &mesh.triangles()[0] , GL_STATIC_DRAW);

    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, m_positionBuffer);
    glVertexAttribPointer(
                0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                3,                  // size
                GL_FLOAT,           // type
                GL_FALSE,           // normalized?
                0,                  // stride
                (void*)0            // array buffer offset
                );

    // 2nd attribute buffer : colors
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, m_normalBuffer);
    glVertexAttribPointer(
                1,                  // attribute 1.
                3,                  // size
                GL_FLOAT,           // type
                GL_FALSE,           // normalized?
                0,                  // stride
                (void*)0            // array buffer offset
                );
    glBindVertexArray(0);

    m_vertexCount = mesh.triangles().size()*3;
    glCheckError();
}

void OpenGLMesh::clearBuffers()
{
    glDeleteBuffers(1, &m_positionBuffer);
    glDeleteBuffers(1, &m_normalBuffer);
    glDeleteBuffers(1, &m_elementbuffer);

    // glDisableVertexAttribArray(0);
    // glDisableVertexAttribArray(1);

    glDeleteVertexArrays(1, &m_vao);
}

void OpenGLMesh::draw () const
{
    glBindVertexArray(m_vao);
    glDrawElements(
                GL_TRIANGLES,      // mode
                m_vertexCount,    // count
                GL_UNSIGNED_INT,   // type
                (void*)0           // element array buffer offset
                );
}

void OpenGLMesh::debugDrawNormals(const Mesh &mesh, float normalScale) const
{
    glLineWidth(1.);
    for(unsigned int pIt = 0 ; pIt < mesh.normals().size() ; ++pIt)
    {
        glm::vec3 to = mesh.positions()[pIt] + mesh.normals()[pIt]*normalScale;
        debugDrawVector(mesh.positions()[pIt], to);
    }
}

void OpenGLMesh::debugDrawVector(const glm::vec3 &i_from, const glm::vec3 &i_to ) const
{
    glBegin(GL_LINES);
    glVertex3f(i_from[0], i_from[1], i_from[2] );
    glVertex3f(i_to[0], i_to[1], i_to[2] );
    glEnd();
}

