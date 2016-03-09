#include <iostream>
#include "texture2D.h"
#include <fstream>


Texture2D::Texture2D(char* FileName, int _index)
{
    m_textureTarget = GL_TEXTURE_2D;
    m_fileName      = FileName;
    index = _index;
    m_textureUnit = GL_TEXTURE0 + index;

    load();
}


bool Texture2D::load()
{
    Texture2D::Img img;
    img = loadBMP(m_fileName);

    glActiveTexture(m_textureUnit);

    glGenTextures(1, &m_textureObj);
    glBindTexture(m_textureTarget, m_textureObj);
    glTexImage2D(m_textureTarget, 0, GL_RGB, img.width, img.height, 0, GL_BGR, GL_UNSIGNED_BYTE, img.data);
	
	glTexParameteri(m_textureTarget, GL_TEXTURE_WRAP_R, GL_REPEAT);
	glTexParameteri(m_textureTarget, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(m_textureTarget, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(m_textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(m_textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(m_textureTarget, m_textureObj);

	return true;
}

void Texture2D::setImage(char *FileName)
{
    Texture2D::Img img;
    img = loadBMP(FileName);
    glBindTexture(m_textureTarget, m_textureObj);
    glTexImage2D(m_textureTarget, 0, GL_RGB, img.width, img.height, 0, GL_BGR, GL_UNSIGNED_BYTE, img.data);

}

char* Texture2D::getImageName()
{
    return m_fileName;
}



