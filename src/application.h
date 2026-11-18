#ifndef APPLICATION_H
#define APPLICATION_H

#include "openglrenderer.h"
#include "scene.h"

class Application
{
public:
    Application(int argc, char **argv);

    void setScene(Scene *scene);
    void idle();
    void display();
    void keyboard(unsigned char keyPressed, int x, int y);
    void mouse(int button, int state, int x, int y);
    void motion(int x, int y);
    void reshape(int width, int height);

private:
    Scene *m_scene;
    OpenGLRenderer m_openGLRenderer;

    bool m_isFullScreen;
    unsigned int m_screenWidth;
    unsigned int m_screenHeight;
    int m_windowID;

    //Camera
    bool m_mouseMovePressed;
    bool m_mouseRotatePressed;
    bool m_mouseZoomPressed;
    int m_lastX;
    int m_lastY;
    int m_lastZoom;
};

void glutCallbackIdle();
void glutCallbackDisplay();
void glutCallbackKeyboard(unsigned char keyPressed, int x, int y);
void glutCallbackMouse(int button, int state, int x, int y);
void glutCallbackMotion(int x, int y);
void glutCallbackReshape(int width, int height);

#endif // APPLICATION_H
