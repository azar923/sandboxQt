#include "sandboxwidget.h"



SandboxWidget::SandboxWidget(QWidget* parent) : QGLWidget(parent)
{
    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);
    QCursor c = cursor();
    c.setPos(mapToGlobal(QPoint(width() / 2, height() / 2)));
    c.setShape(Qt::BlankCursor);
    setCursor(c);
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

void SandboxWidget::keyPressEvent(QKeyEvent *event)
{
    Scene::getInstance() -> OnKeyboard(event);
    int keyInt = event->key();
    Qt::Key key = static_cast<Qt::Key>(keyInt);
    if (key == Qt::Key_Escape)
    {
        resize(380,280);
        move(780,40);
        Scene::getInstance() -> setWindowSize(380, 280);
        Scene::getInstance()->terrain->setSandboxMode();
    }
}

