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
#include <QOpenGLFunctions_4_0_Core>


class Scene : protected QOpenGLFunctions_4_0_Core
{
public:
    Scene(int _WINDOW_WIDTH, int _WINDOW_HEIGHT);
    void render();
    void OnMouse(int button, int state, int ax, int ay);
    void OnPassiveMouse(int x, int y);
    void OnKeyboard(QKeyEvent* event);

    void createFrameBuffer();
    void createScreenQuad();


    int WINDOW_WIDTH;
    int WINDOW_HEIGHT;

    static Scene* getInstance() {
        if (singleton == 0)
            singleton = new Scene(380, 280);
        return singleton;
    }

    Pipeline* pipeline;
    Camera* camera;
    Lighting* lighting;
    Skybox* skybox;
    Terrain* terrain;

    Mat* getSandboxView();

    void setWindowSize(int WIDTH, int HEIGHT);


private:

    static Scene* singleton;
    struct ScreenVertex {
        Vector3f pos;
        Vector2f tex;
    };



    Mat* sandboxView;

    GLuint FBO;
    GLuint DBO;
    GLuint renderTexture;

    GLuint VBO;

    ShaderTechnique* technique;

};

#endif // SCENE_H

