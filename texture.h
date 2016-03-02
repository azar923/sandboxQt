#ifndef TEXTURE_H
#define TEXTURE_H
#include <string>
#include "texture.h"
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>

class Texture
{
public:
    virtual bool load() = 0;

    struct Img {
        unsigned char* data;
        int width;
        int height;
    };

    int getIndex();

    Texture::Img loadBMP(char* filename);
protected:
    GLenum m_textureTarget;
    GLenum m_textureUnit;
    GLuint m_textureObj;
    int index;
};

#endif // TEXTURE_H
