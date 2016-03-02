#ifndef SHADERTECHNIQUE_H
#define SHADERTECHNIQUE_H

#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <string>
#include <iostream>
#include <fstream>


class ShaderTechnique : protected QOpenGLFunctions
{
public:
    ShaderTechnique(const char* vname, const char* fname);
    unsigned int p;
private:
    void loadFile(const char* fn, std::string& str);
    void CreateShaderProgram(const char* vname, const char* fname);
    unsigned int loadShader(std::string& source,unsigned int mode);
    unsigned int f;
    unsigned int v;

};

#endif // SHADERTECHNIQUE_H
