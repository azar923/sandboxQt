#include "sandboxwidget.h"

SandboxWidget::SandboxWidget(QWidget* parent) : QGLWidget(parent)
{
}


void SandboxWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 1.0, 0.0, 1.0);

    scene = new Scene(750, 500);
}

void SandboxWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
}

void SandboxWidget::paintGL()
{
    scene -> render();
    showFullScreen();
}
