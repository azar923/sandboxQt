#include "scene.h"
#include <math.h>
#include <opencv2/cudaimgproc.hpp>
#include <opencv2/cudafilters.hpp>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>




Scene* Scene::singleton = 0;
Scene::Scene(int _WINDOW_WIDTH, int _WINDOW_HEIGHT)
{
    initializeOpenGLFunctions();
    Vector3f pos = Vector3f(-100.0f, 300.0f, -50.0f);
    Vector3f target = Vector3f(0.0f, -0.6f, 0.4f);
    Vector3f up = Vector3f(0.0f, 1.0f, 0.0f);

    WINDOW_HEIGHT = _WINDOW_HEIGHT;
    WINDOW_WIDTH = _WINDOW_WIDTH;

    camera = new Camera(WINDOW_WIDTH, WINDOW_HEIGHT, pos, target, up);
    pipeline = new Pipeline;
    lighting = new Lighting;

    lighting->setDirectionalLight();

    skybox = new Skybox;

    int terrain_width = GlobalSettings::getInstance()->getWidth();
    int terrain_height = GlobalSettings::getInstance()->getHeight();
    int terrain_offset_left = GlobalSettings::getInstance()->getOffsetLeft();
    int terrain_offset_right = GlobalSettings::getInstance()->getOffsetRight();
    int terrain_offset_top = GlobalSettings::getInstance()->getOffsetTop();
    int terrain_offset_bottom = GlobalSettings::getInstance()->getOffsetBottom();

    terrain = new Terrain(terrain_width, terrain_height, terrain_offset_left, terrain_offset_right, terrain_offset_top, terrain_offset_bottom);
    terrain->setup();

    createFrameBuffer();
    createScreenQuad();

    technique = new ShaderTechnique("/home/maxim/sandbox/shaders/scene.vert","/home/maxim/sandbox/shaders/scene.frag" );

}

void Scene::setWindowSize(int WIDTH, int HEIGHT)
{
    WINDOW_WIDTH = WIDTH;
    WINDOW_HEIGHT = HEIGHT;

    camera->setWindowSize(WIDTH, HEIGHT);
}


void Scene::createScreenQuad()
{
    ScreenVertex vertices[4];

    vertices[0].pos = Vector3f(-1.0, 1.0, 0.0);
    vertices[0].tex = Vector2f(0.0, 1.0);

    vertices[1].pos = Vector3f(1.0, 1.0, 0.0);
    vertices[1].tex = Vector2f(1.0, 1.0);

    vertices[2].pos = Vector3f(1.0, -1.0, 0.0);
    vertices[2].tex = Vector2f(1.0, 0.0);

    vertices[3].pos = Vector3f(-1.0, -1.0, 0.0);
    vertices[3].tex = Vector2f(0.0, 0.0);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

}

void Scene::createFrameBuffer()
{
    glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    glGenTextures(1, &renderTexture);
    glActiveTexture(GL_TEXTURE9);
    glBindTexture(GL_TEXTURE_2D, renderTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WINDOW_WIDTH, WINDOW_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, renderTexture, 0);
    glGenRenderbuffers(1, &DBO);
    glBindRenderbuffer(GL_RENDERBUFFER, DBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, WINDOW_WIDTH, WINDOW_HEIGHT);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, DBO);
    GLenum drawBufs[] = {GL_COLOR_ATTACHMENT0};

    glDrawBuffers(1, drawBufs);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void Scene::render()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glViewport(0,0, WINDOW_WIDTH, WINDOW_HEIGHT);

    terrain->render(pipeline, camera, lighting, WINDOW_WIDTH, WINDOW_HEIGHT);
    skybox->render(pipeline, camera, WINDOW_WIDTH, WINDOW_HEIGHT);
}

Mat* Scene::getSandboxView()
{
    return sandboxView;
}


void Scene::OnMouse(int button, int state, int ax, int ay)
{
    terrain->setHeightMouse(button, state, ax, ay, WINDOW_WIDTH, WINDOW_HEIGHT);
}



void Scene::OnPassiveMouse(int x, int y)
{
    camera -> OnMouse(x, y);
}

void Scene::OnKeyboard(QKeyEvent* event)
{
    camera->OnKeyboard(event);
}




