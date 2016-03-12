#ifndef SKYBOX_H
#define SKYBOX_H
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include "pipeline.h"
#include "camera.h"
#include "shadertechnique.h"
#include "texture3D.h"


class Skybox : protected QOpenGLFunctions
{
public:

    Skybox();
    void render(Pipeline *p, Camera *c, int WINDOW_WIDTH, int WINDOW_HEIGHT);

    void setLeft(char* FileName);
    void setRight(char* FileName);
    void setTop(char* FileName);
    void setBottom(char* FileName);
    void setFront(char* FileName);
    void setBack(char* FileName);


private:
    Texture3D* texture;
    GLuint VBO;
    GLuint IBO;
    ShaderTechnique* skyboxTechnique;
    GLuint WVPLocation;
    GLuint textureLocation;
};

#endif // SKYBOX_H
