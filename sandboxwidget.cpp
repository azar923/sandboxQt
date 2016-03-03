#include "sandboxwidget.h"



SandboxWidget::SandboxWidget(QWidget* parent) : QGLWidget(parent)
{
    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);

}


void SandboxWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 1.0);
}

void SandboxWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
}

void SandboxWidget::paintGL()
{
    Scene::getInstance() -> render();
}

void SandboxWidget::mouseMoveEvent(QMouseEvent *event)
{
    Scene::getInstance() -> OnPassiveMouse(event->x(), event->y());
}



