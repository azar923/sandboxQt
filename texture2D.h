#ifndef TEXTURE2D_H
#define	TEXTURE2D_H

#include <string>
#include "texture.h"

#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>

class Texture2D : public Texture
{
public:
    Texture2D(char* FileName, int _index);
    bool load();
    void setImage(char* FileName);
    char* getImageName();

private:
    char* m_fileName;
};


#endif	

