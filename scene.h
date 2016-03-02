#ifndef SCENE_H
#define SCENE_H

#include "pipeline.h"
#include "camera.h"
#include "lighting.h"
#include "skybox.h"
#include "terrain.h"
#include "inputstream.h"

#include <QOpenGLFunctions>
#include <QOpenGLBuffer>


class Scene : protected QOpenGLFunctions
{
public:
    Scene(int _WINDOW_WIDTH, int _WINDOW_HEIGHT);
    void render();
    void OnMouse(int button, int state, int ax, int ay);
    void OnSpecialKeyboard(int Key, int x, int y);
    void OnPassiveMouse(int x, int y);
    void OnKeyboard(unsigned char Key, int x, int y);

    void createFrameBuffer();
    void createScreenQuad();


    int WINDOW_WIDTH;
    int WINDOW_HEIGHT;


private:
    struct ScreenVertex {
        Vector3f pos;
        Vector2f tex;
    };



    Pipeline* pipeline;
    Camera* camera;
    Lighting* lighting;
    Skybox* skybox;
    Terrain* terrain;

    GLuint FBO;
    GLuint DBO;
    GLuint renderTexture;

    GLuint VBO;

    ShaderTechnique* technique;

};

#endif // SCENE_H

