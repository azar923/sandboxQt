#include "terrain.h"
#include <iostream>
#include <time.h>

using namespace std;

Terrain::Terrain(const int _width, const int _height, int _offsetLeft, int _offsetRight, int _offsetTop, int _offsetBottom)
{
    width = _width;
    height = _height;
    setOffset(_offsetLeft, _offsetRight, _offsetTop, _offsetBottom);

}

void Terrain::setup()
{


    kinectMode = 0;

    initializeOpenGLFunctions();

    bool isSensorConnected = InputStream::isSensorConnected();

    if (isSensorConnected)
    {
        stream = new InputStream(width, height, 560, 640, offsetLeft, offsetRight, offsetTop, offsetBottom);
        cout << "Kinect stream was created" << endl;
        kinectMode = 1;

    }

    else
    {
        cout << "Kinect was not initialized" << endl;
        stream = new Filestream("/home/maxim/sandbox_mat/map.raw", width, height, offsetLeft, offsetRight, offsetTop, offsetBottom);
    }

    width  -= (offsetLeft +   offsetRight);
    height -= (offsetBottom + offsetTop);

    dx = 2.0 / (width-1);
    dy = 2.0 / (height-1);
    dx_tex = 1.0 / (width-1);
    dy_tex = 1.0 / (height-1);

    Vertices_terrain.resize(width * height);
    Indices.resize( (width-1) * (height - 1) * 6);

    specularIntensity = 0.0;
    sandboxMode = 0;

    terrainTechnique = new ShaderTechnique("/home/maxim/Sandbox_Qt/shaders/terrain.vert","/home/maxim/Sandbox_Qt/shaders/terrain.frag" );

    grass     =  new Texture2D ("/home/maxim/sandbox_mat/terrain/grass.bmp", 0 );
    sand      =  new Texture2D ("/home/maxim/sandbox_mat/terrain/sand.bmp",  1 );
    stone     =  new Texture2D ("/home/maxim/sandbox_mat/terrain/stone.bmp", 2 );
    snow      =  new Texture2D ("/home/maxim/sandbox_mat/terrain/snow.bmp",  3 );
    water_tex =  new Texture2D ("/home/maxim/sandbox_mat/terrain/water.bmp", 4 );
    reflection = new Texture2D ("/home/maxim/sandbox_mat/terrain/reflection.bmp", 6);

    cout << "Textures were loaded" << endl;

    alpha = 1.5;
    beta = 0.25;

    createBuffer();
    setUniforms();

    cout << "Terrain was created" << endl;
}

void Terrain::setOffset(int _left, int _right, int _top, int _bottom)
{
    offsetLeft = _left;
    offsetRight = _right;
    offsetTop = _top;
    offsetBottom = _bottom;
}

void Terrain::setAlpha(float a)
{
    alpha = a;
}

void Terrain::setBeta(float b)
{
    beta = b;
}

void Terrain::setHeight(unsigned char* data)
{
    for (int i = 0; i < height ; i++)
        for (int j = 0; j < width ; j++)
        {
            int idx = i * width + j;

            Vertices_terrain[idx].pos.z =  1.0 - data[idx] / 255.0;
        }

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Terrain::Vertex_terrain) * Vertices_terrain.size(), &Vertices_terrain[0]);
}

void Terrain::setHeight(int value)
{
    for (int i = 0; i < height ; i++)
        for (int j = 0; j < width ; j++)
        {
            int idx = i * width + j;
            Vertices_terrain[idx].pos.z = value;
        }

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Terrain::Vertex_terrain) * Vertices_terrain.size(), &Vertices_terrain[0]);
}



void Terrain::setHeightMouse(int button, int state, int ax, int ay, int WINDOW_WIDTH, int WINDOW_HEIGHT)
{

}


unsigned int Terrain::chain(unsigned int i, unsigned int j, int w)
{
    return i * w + j;
}

void Terrain::createBuffer()
{

    for (int i = 0; i < height ; i++)
        for (int j = 0; j < width; j++)
        {
            int idx = i * width + j;

            Vertices_terrain[idx].pos = Vector3f(-1.0 + j * dx , 1 - i * dy,  0.0);
            Vertices_terrain[idx].pos.z = 0.0;
            Vertices_terrain[idx].tex = Vector2f(j * dx_tex, 1 - i * dy_tex);
        }

    int ind = 0;

    for(int i = 0; i < height - 1; i++)
    {
        for(int j = 0; j < width - 1; j++)
        {
            Indices[ind] = chain(i, j, width);
            Indices[ind + 1] = chain(i, j + 1, width);
            Indices[ind + 2] = chain(i + 1, j + 1, width);
            Indices[ind + 3] = chain(i + 1, j + 1, width);
            Indices[ind + 4] = chain(i + 1, j, width);
            Indices[ind + 5] = chain(i, j , width);

            ind += 6;
        }
    }

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Indices.size(), &Indices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex_terrain) * Vertices_terrain.size(), 0, GL_STREAM_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex_terrain) * Vertices_terrain.size(), &Vertices_terrain[0]);
}

void Terrain::setUniforms()
{

    glUseProgram(terrainTechnique->p);
    grassLocation  =   glGetUniformLocation(terrainTechnique->p, "grass" );
    sandLocation   =   glGetUniformLocation(terrainTechnique->p, "sand"  );
    stoneLocation  =   glGetUniformLocation(terrainTechnique->p, "stone" );
    snowLocation   =   glGetUniformLocation(terrainTechnique->p, "snow");
    waterLocation  =   glGetUniformLocation(terrainTechnique->p, "water");
    reflectionLocation = glGetUniformLocation(terrainTechnique->p, "reflection");

    gWVPLocation   =   glGetUniformLocation(terrainTechnique->p, "gWVP");
    gWorldLocation =   glGetUniformLocation(terrainTechnique->p, "gWorld");

    dirLightColorLocation = glGetUniformLocation(terrainTechnique->p, "gDirectionalLight.Color");
    dirLightAmbientIntensityLocation = glGetUniformLocation(terrainTechnique->p, "gDirectionalLight.AmbientIntensity");
    dirLightDiffuseIntensityLocation = glGetUniformLocation(terrainTechnique->p, "gDirectionalLight.DiffuseIntensity");
    dirLightDirectionLocation = glGetUniformLocation(terrainTechnique->p, "gDirectionalLight.Direction");

    matSpecularIntensityLocation = glGetUniformLocation(terrainTechnique->p, "gMatSpecularIntensity");
    specularPowerLocation = glGetUniformLocation(terrainTechnique->p, "gSpecularPower");
    eyePosLocation = glGetUniformLocation(terrainTechnique->p, "gEyeWorldPos");
    sandboxModeLocation = glGetUniformLocation(terrainTechnique->p, "sandboxMode");
    timerLocation = glGetUniformLocation(terrainTechnique->p, "timer");

    alphaLocation = glGetUniformLocation(terrainTechnique->p, "alpha");
    betaLocation = glGetUniformLocation(terrainTechnique->p, "beta");


    glUniform1i(grassLocation,  grass->getIndex());
    glUniform1i(sandLocation,   sand->getIndex());
    glUniform1i(stoneLocation,  stone->getIndex());
    glUniform1i(snowLocation,   snow->getIndex());
    glUniform1i(waterLocation,  water_tex->getIndex());
    glUniform1i(reflectionLocation, reflection->getIndex());

    glUseProgram(NULL);

}

void Terrain::computeNormals()
{

    for (int i = 0; i < (width-1) * (height-1) * 6; i += 3)
    {
        unsigned int Index0 = Indices[i];
        unsigned int Index1 = Indices[i + 1];
        unsigned int Index2 = Indices[i + 2];

        Vector3f v1 = Vertices_terrain[Index1].pos - Vertices_terrain[Index0].pos;
        Vector3f v2 = Vertices_terrain[Index2].pos - Vertices_terrain[Index1].pos;
        Vector3f Normal = v1.Cross(v2);
        Normal.Normalize();

        Vertices_terrain[Index0].normal += Normal;
        Vertices_terrain[Index1].normal += Normal;
        Vertices_terrain[Index2].normal += Normal;
    }

    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
        {
            Vertices_terrain[i * width + j].normal.Normalize();
        }

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex_terrain) * Vertices_terrain.size(), &Vertices_terrain[0]);

}

void Terrain::setSandboxMode()
{
    if (sandboxMode == 1)
        sandboxMode = 0;
    else
        sandboxMode = 1;
}



void Terrain::render(Pipeline* p, Camera* c, Lighting* l, int WINDOW_WIDTH, int WINDOW_HEIGHT)
{

    setHeight(stream->getData());

    timer = clock();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    computeNormals();

    p->Scale(200.0 , 200.0, 200.0);
    p->Rotate(-90.0f, 0.0f, 0.0f);
    p->WorldPos(-100.0f, 0.0f, 100.0f);
    p->SetCamera(c->GetPos(), c->GetTarget(),c->GetUp() );

    p->SetPerspectiveProj(60.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 1.0f, 1000.0f);

    glUseProgram(terrainTechnique->p);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glUniform1i(timerLocation, timer);
    glUniform3f(dirLightColorLocation, l->dirLight.Color.x, l->dirLight.Color.y, l->dirLight.Color.z);
    glUniform1f(dirLightAmbientIntensityLocation, l->dirLight.AmbientIntensity);
    glUniform1f(dirLightDiffuseIntensityLocation, l->dirLight.DiffuseIntensity);

    glUniform1f(alphaLocation, alpha);
    glUniform1f(betaLocation, beta);

    Vector3f direction = l->dirLight.Direction;
    direction.Normalize();

    Vector3f pos = c->GetPos();

    glUniform3f(dirLightDirectionLocation, direction.x, direction.y, direction.z);
    glUniform3f(eyePosLocation, pos.x, pos.y, pos.z);
    glUniform1f(matSpecularIntensityLocation, specularIntensity);
    glUniform1f(specularPowerLocation, l->specularPower);
    glUniform1i(sandboxModeLocation, sandboxMode);

    glUniformMatrix4fv(gWVPLocation, 1, GL_TRUE, (const GLfloat*)p->GetWVPTrans());
    glUniformMatrix4fv(gWorldLocation, 1, GL_TRUE, (const GLfloat*)p->GetWorldTrans());

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex_terrain), 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex_terrain), (const GLvoid*)12);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex_terrain), (const GLvoid*)24);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);


    glDrawElements(GL_TRIANGLES, (width - 1) * (height - 1) * 6, GL_UNSIGNED_INT, 0);
    glUseProgram(NULL);



    glUseProgram(NULL);

    timer = 0;

}
