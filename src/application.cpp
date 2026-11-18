#include "application.h"
#include "imagergb.h"

Application *g_application = nullptr;

Application::Application(int argc, char **argv) :
    m_scene(nullptr),
    m_openGLRenderer(),
    m_isFullScreen(false),
    m_screenWidth(1600),
    m_screenHeight(900),
    m_windowID(0),
    m_mouseMovePressed(false),
    m_mouseRotatePressed(false),
    m_mouseZoomPressed(false),
    m_lastX(0),
    m_lastY(0),
    m_lastZoom(0)
{
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize (m_screenWidth, m_screenHeight);
    m_windowID = glutCreateWindow ("TP HAI719I");

    g_application = this;
    glutIdleFunc(glutCallbackIdle);
    glutDisplayFunc(glutCallbackDisplay);
    glutKeyboardFunc(glutCallbackKeyboard);
    glutMouseFunc(glutCallbackMouse);
    glutMotionFunc(glutCallbackMotion);
    glutReshapeFunc(glutCallbackReshape);

    keyboard ('?', 0, 0);

    m_openGLRenderer.initialize(); //Must be initialized after glut
}

void Application::setScene(Scene *scene)
{
    m_scene = scene;
    m_openGLRenderer.uploadScene(*m_scene);
}

//GLUT override functions

void Application::idle()
{
    // glutPostRedisplay orders a display of the scene : https://www.opengl.org/resources/libraries/glut/spec3/node20.html
    // In theory we don't always need to redraw the scene every frame.
    glutPostRedisplay ();
}

void Application::display()
{
    m_openGLRenderer.displayScene(*m_scene);
    glutSwapBuffers();
}

void Application::keyboard(unsigned char keyPressed, int x, int y)
{
    switch (keyPressed)
    {
    case 'f':
        if (m_isFullScreen == true) {
            glutReshapeWindow (m_screenWidth, m_screenHeight);
            m_isFullScreen = false;
        } else {
            glutFullScreen ();
            m_isFullScreen = true;
        }
        break;

    case 'w':
        GLint polygonMode[2];
        glGetIntegerv(GL_POLYGON_MODE, polygonMode);
        if(polygonMode[0] != GL_FILL)
            glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
        else
            glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);
        break;

    case 'n': //Press n key to display normals
        m_openGLRenderer.toggleDisplayNormals();
        break;

    default:
        break;
    }
    idle ();
}

void Application::mouse(int button, int state, int x, int y)
{
    if(m_scene != nullptr)
    {
        TrackballCamera &camera = m_scene->camera();
        if (state == GLUT_UP)
        {
            m_mouseMovePressed = false;
            m_mouseRotatePressed = false;
            m_mouseZoomPressed = false;
        }
        else
        {
            if (button == GLUT_LEFT_BUTTON)
            {
                camera.beginRotate(x, y);
                m_mouseMovePressed = false;
                m_mouseRotatePressed = true;
                m_mouseZoomPressed = false;
            }
            else if (button == GLUT_RIGHT_BUTTON)
            {
                m_lastX = x;
                m_lastY = y;
                m_mouseMovePressed = true;
                m_mouseRotatePressed = false;
                m_mouseZoomPressed = false;
            }
            else if (button == GLUT_MIDDLE_BUTTON)
            {
                if (m_mouseZoomPressed == false)
                {
                    m_lastZoom = y;
                    m_mouseMovePressed = false;
                    m_mouseRotatePressed = false;
                    m_mouseZoomPressed = true;
                }
            }
        }
    }
    idle ();
}

void Application::motion(int x, int y)
{
    if(m_scene != nullptr)
    {
        TrackballCamera &camera = m_scene->camera();
        if (m_mouseRotatePressed == true)
        {
            camera.rotate(x, y);
        }
        else if (m_mouseMovePressed == true)
        {
            camera.move(
                (x-m_lastX)/static_cast<float>(m_screenWidth),
                (m_lastY-y)/static_cast<float>(m_screenHeight)
            );
            m_lastX = x;
            m_lastY = y;
        }
        else if (m_mouseZoomPressed == true) {
            camera.zoom (float (y-m_lastZoom)/m_screenHeight);
            m_lastZoom = y;
        }
    }
}

void Application::reshape(int w, int h)
{
    if(m_scene != nullptr)
    {
        TrackballCamera &camera = m_scene->camera();
        camera.resize (w, h);
    }
}

//GLUT doesn't accept member functions as function pointers so I do this

void glutCallbackIdle()
{
    g_application->idle();
}

void glutCallbackDisplay()
{
    g_application->display();
}

void glutCallbackKeyboard(unsigned char keyPressed, int x, int y)
{
    g_application->keyboard(keyPressed, x, y);
}

void glutCallbackMouse(int button, int state, int x, int y)
{
    g_application->mouse(button, state, x, y);
}

void glutCallbackMotion(int x, int y)
{
    g_application->motion(x, y);
}

void glutCallbackReshape(int width, int height)
{
    g_application->reshape(width, height);
}

