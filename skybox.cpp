#include "skybox.h"
#include <iostream>
using namespace std;

Skybox::Skybox()
{
    initializeOpenGLFunctions();
    skyboxTechnique = new ShaderTechnique("/home/maxim/Sandbox_Qt/shaders/skybox.vert","/home/maxim/Sandbox_Qt/shaders/skybox.frag" );
    GLfloat CubeVertices[] = {-1.0, 1.0, 1.0,
                          -1.0, -1.0, 1.0,
                          1.0, -1.0, 1.0,
                          1.0, 1.0, 1.0,
                          -1.0, 1.0, -1.0,
                          -1.0, -1.0, -1.0,
                          1.0, -1.0, -1.0,
                          1.0, 1.0, -1.0};
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(CubeVertices), CubeVertices, GL_STATIC_DRAW);

    unsigned int CubeIndices[] = {0, 1, 2, 3,
                              3, 2, 6, 7,
                              7, 6, 5, 4,
                              4, 5, 1, 0,
                              0, 3, 7, 4,
                              1, 2, 6, 5};

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(CubeIndices), CubeIndices, GL_STATIC_DRAW);

    texture = new Texture3D("/home/maxim/sandbox_mat/sea/right.bmp",  "/home/maxim/sandbox_mat/sea/left.bmp",
                            "/home/maxim/sandbox_mat/sea/front.bmp",  "/home/maxim/sandbox_mat/sea/back.bmp",
                            "/home/maxim/sandbox_mat/sea/bottom.bmp", "/home/maxim/sandbox_mat/sea/top.bmp", 5);


}

void Skybox::render(Pipeline* p, Camera* c, int WINDOW_WIDTH, int WINDOW_HEIGHT)
{

    GLint OldCullFaceMode;
    glGetIntegerv(GL_CULL_FACE_MODE, &OldCullFaceMode);
    GLint OldDepthFuncMode;
    glGetIntegerv(GL_DEPTH_FUNC, &OldDepthFuncMode);

    glCullFace(GL_FRONT);
    glDepthFunc(GL_LEQUAL);
    p->Scale(1000.0 , 1000.0, 1000.0);
    p->Rotate(180.0f, 0.0f, 0.0f);
    p->WorldPos(c->GetPos().x, c->GetPos().y, c->GetPos().z);

    p->SetCamera(c->GetPos(), c->GetTarget(), c->GetUp() );

    p->SetPerspectiveProj(60.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 1.0f, 1000.0f);

    glUseProgram(skyboxTechnique->p);
    textureLocation = glGetUniformLocation(skyboxTechnique->p, "skybox");
    glUniform1i(textureLocation, texture->getIndex());
    WVPLocation = glGetUniformLocation(skyboxTechnique->p, "gWVP");
    glUniformMatrix4fv(WVPLocation, 1, GL_TRUE, (const GLfloat*)p->GetWVPTrans());
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    glDrawElements(GL_QUADS, 24 , GL_UNSIGNED_INT, 0);
    glDisableVertexAttribArray(0);

    glCullFace(OldCullFaceMode);
    glDepthFunc(OldDepthFuncMode);

    glUseProgram(NULL);
}


