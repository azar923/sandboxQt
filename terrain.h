#ifndef TERRAIN_H
#define TERRAIN_H

#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <vector>

#include "pipeline.h"
#include "camera.h"
#include "texture2D.h"
#include "shadertechnique.h"
#include "inputstream.h"
#include "filestream.h"
#include "lighting.h"

using namespace std;

class Terrain : protected QOpenGLFunctions
{
public:
    Terrain(const int _width, const int _height, int _offsetLeft = 0, int _offsetRight = 0, int _offsetTop = 0, int _offsetBottom = 0);
    void render(Pipeline* p, Camera* c, Lighting* l, int WINDOW_WIDTH, int WINDOW_HEIGHT);
    void setHeightMouse(int button, int state, int ax, int ay, int WINDOW_WIDTH, int WINDOW_HEIGHT);
    void setHeight(unsigned char* data);
    void setHeight(int value);
    void setSandboxMode();
    DataStream* stream;

    void setAlpha(float a);
    void setBeta(float b);

private:

    struct Vertex_terrain
    {
        Vector3f pos;
        Vector3f normal;
        Vector2f tex;
    };

    void createBuffer();
    void setUniforms();
    void computeNormals();

    unsigned int chain(unsigned int i, unsigned int j, int w);



    float dx, dy, dx_tex, dy_tex;

    Texture2D* grass = 0;
    Texture2D* sand = 0;
    Texture2D* stone = 0;
    Texture2D* snow = 0;
    Texture2D* water_tex = 0;
    Texture2D* reflection = 0;

    GLuint grassLocation;
    GLuint sandLocation;
    GLuint stoneLocation;
    GLuint snowLocation;
    GLuint waterLocation;
    GLuint reflectionLocation;



    float* particles;
    int* phases;
    int* active_indices;
    float* velocities;

    bool left_button_pressed = false;
    bool right_button_pressed = true;

    int width;
    int height;

    int sandboxMode;
    int kinectMode;

    float specularIntensity;

    int timer;

    float alpha;
    float beta;


    vector<Vertex_terrain> Vertices_terrain;
    GLuint VBO, IBO;
    GLuint particles_VBO;
    vector<unsigned int> Indices;
    ShaderTechnique* terrainTechnique;

    QOpenGLShaderProgram* program;


    GLuint gWVPLocation;
    GLuint gWorldLocation;
    GLuint dirLightColorLocation;
    GLuint dirLightAmbientIntensityLocation;
    GLuint dirLightDiffuseIntensityLocation;
    GLuint dirLightDirectionLocation;
    GLuint matSpecularIntensityLocation;
    GLuint specularPowerLocation;
    GLuint sandboxModeLocation;
    GLuint eyePosLocation;
    GLuint timerLocation;


    GLuint offsetLeft;
    GLuint offsetRight;
    GLuint offsetTop;
    GLuint offsetBottom;

    GLuint alphaLocation;
    GLuint betaLocation;

};

#endif // TERRAIN_H
