#include "openglrenderer.h"
#include "light.h"
#include "shader.h"

OpenGLRenderer::OpenGLRenderer() :
    m_programID(0),
    m_modelMatrixUniformLocation(0),
    m_viewMatrixUniformLocation(0),
    m_projectionMatrixUniformLocation(0),
    m_light1OrientationUniformLocation(0),
    m_light1AmbientUniformLocation(0),
    m_light1DiffuseUniformLocation(0),
    m_light1SpecularUniformLocation(0),
    m_light1EnabledUniformLocation(0),
    m_positionBuffer(0),
    m_normalBuffer(0),
    m_elementBuffer(0),
    m_display_normals(false),
    m_screenWidth(1600),
    m_screenHeight(900)
{}

OpenGLRenderer::~OpenGLRenderer()
{
    glDeleteProgram(m_programID);
}

void OpenGLRenderer::initialize()
{
    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    glCullFace (GL_BACK);
    glEnable (GL_CULL_FACE);
    glDepthFunc (GL_LESS);
    glEnable (GL_DEPTH_TEST);
    glClearColor (0.2f, 0.2f, 0.3f, 1.0f);

    m_display_normals = false;

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return;
    }
    m_programID = load_shaders("vertex_shader.glsl", "fragment_shader.glsl");
    fetchUniformLocations();
}

void OpenGLRenderer::fetchUniformLocations()
{
    m_light1OrientationUniformLocation = glGetUniformLocation(m_programID, "u_light1Orientation");

    m_light1AmbientUniformLocation = glGetUniformLocation(m_programID, "u_light1Ambient");
    m_light1DiffuseUniformLocation = glGetUniformLocation(m_programID, "u_light1Diffuse");
    m_light1SpecularUniformLocation = glGetUniformLocation(m_programID, "u_light1Specular");
    m_light1EnabledUniformLocation = glGetUniformLocation(m_programID, "u_light1Enabled");

    m_modelMatrixUniformLocation = glGetUniformLocation(m_programID, "u_modelMatrix");
    m_viewMatrixUniformLocation = glGetUniformLocation(m_programID, "u_viewMatrix");
    m_projectionMatrixUniformLocation = glGetUniformLocation(m_programID, "u_projectionMatrix");
    glCheckError();
}

void OpenGLRenderer::uploadScene(const Scene &scene)
{
    unloadScene();
    for(const Mesh &mesh : scene.meshes())
    {
        m_openGLMeshes.emplace_back(mesh);
    }
    glCheckError();
}

void OpenGLRenderer::unloadScene()
{
    for(OpenGLMesh &mesh : m_openGLMeshes)
    {
        mesh.clearBuffers();
    }
    m_openGLMeshes.clear();
    glCheckError();
}


void OpenGLRenderer::updateLightUniforms() const
{
    static DirectionalPhongLight light1(glm::vec3(1.0f,-0.0f,1.0f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f));
    glUniform3fv(m_light1OrientationUniformLocation, 1, glm::value_ptr(light1.orientation)); //With glm, access vector members like this...
    glUniform3fv(m_light1AmbientUniformLocation, 1, glm::value_ptr(light1.ambient));
    glUniform3fv(m_light1DiffuseUniformLocation, 1, glm::value_ptr(light1.diffuse));
    glUniform3fv(m_light1SpecularUniformLocation, 1, glm::value_ptr(light1.specular));
    glUniform1i(m_light1EnabledUniformLocation, light1.enabled); //Check the Khronos documentation on GlUniform https://registry.khronos.org/OpenGL-Refpages/gl4/html/glUniform.xhtml
}

void OpenGLRenderer::updateCameraUniforms(const Scene &scene) const
{
    glUniformMatrix4fv(m_viewMatrixUniformLocation, 1, false, glm::value_ptr(scene.camera().view()));
    glUniformMatrix4fv(m_projectionMatrixUniformLocation, 1, false, glm::value_ptr(scene.camera().perspective()));
}

void OpenGLRenderer::displayScene(const Scene &scene)
{
    //Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Use our shaders
    glUseProgram(m_programID);

    // Update all uniforms from the last frame
    updateLightUniforms();

    glCheckError();
    updateCameraUniforms(scene);

    //Lien à faire entre le VAO du maillage et l'objet
    for(const ObjectInstance &objectInstance : scene.objectInstances())
    {
        const Mesh &mesh = scene.meshes()[objectInstance.meshID()];

        glUniformMatrix4fv(m_modelMatrixUniformLocation, 1, false, glm::value_ptr(objectInstance.modelMatrix()));
        m_openGLMeshes[objectInstance.meshID()].draw();

        if(m_display_normals)
        {
            glColor3f(1.,0.,0.);
            m_openGLMeshes[objectInstance.meshID()].debugDrawNormals(mesh);
        }
    }
}

void OpenGLRenderer::toggleDisplayNormals()
{
    m_display_normals = !m_display_normals;
}


