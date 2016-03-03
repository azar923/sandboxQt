#ifndef SANDBOXWIDGET_H
#define SANDBOXWIDGET_H

#include <QGLWidget>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include "scene.h"
#include <QTimer>
#include <QMouseEvent>
#include <QKeyEvent>
class SandboxWidget : public QGLWidget, public QOpenGLFunctions
{
    Q_OBJECT
public:
    SandboxWidget(QWidget* parent = 0);

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    Scene* scene;


    void mouseMoveEvent(QMouseEvent* event); Q_DECL_OVERRIDE

};

#endif // SANDBOXWIDGET_H
