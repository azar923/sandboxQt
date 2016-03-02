#ifndef SANDBOXWIDGET_H
#define SANDBOXWIDGET_H

#include <QGLWidget>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include "scene.h"

class SandboxWidget : public QGLWidget, public QOpenGLFunctions
{
    Q_OBJECT
public:
    SandboxWidget(QWidget* parent = 0);

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    Scene* scene;
};

#endif // SANDBOXWIDGET_H
