#include "texture3D.h"

Texture3D::Texture3D(char* right, char* left, char* front, char* back, char* bottom, char* top, int _index)
{

    m_textureTarget = GL_TEXTURE_CUBE_MAP;
    m_right = right;
    m_left = left;
    m_top = top;
    m_bottom = bottom;
    m_front = front;
    m_back = back;

    index = _index;
    m_textureUnit = GL_TEXTURE0 + index;

    load();

}


bool Texture3D::load()
{
    glActiveTexture(m_textureUnit);
    glEnable(GL_TEXTURE_CUBE_MAP);
    glGenTextures(1, &m_textureObj);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureObj);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    Texture::Img img = loadBMP(m_right);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, img.width, img.height, 0, GL_BGR, GL_UNSIGNED_BYTE, img.data);

    img = loadBMP(m_left);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, img.width, img.height, 0, GL_BGR, GL_UNSIGNED_BYTE, img.data);

    img = loadBMP(m_front);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, img.width, img.height, 0, GL_BGR, GL_UNSIGNED_BYTE, img.data);

    img = loadBMP(m_back);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, img.width, img.height, 0, GL_BGR, GL_UNSIGNED_BYTE, img.data);

    img = loadBMP(m_bottom);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, img.width, img.height, 0, GL_BGR, GL_UNSIGNED_BYTE, img.data);

    img = loadBMP(m_top);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, img.width, img.height, 0, GL_BGR, GL_UNSIGNED_BYTE, img.data);

}

void Texture3D::setLeft(char *FileName)
{
    Texture3D::Img img;
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureObj);
    img = loadBMP(FileName);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, img.width, img.height, 0, GL_BGR, GL_UNSIGNED_BYTE, img.data);
}

void Texture3D::setRight(char *FileName)
{
    Texture3D::Img img;
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureObj);
    img = loadBMP(FileName);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, img.width, img.height, 0, GL_BGR, GL_UNSIGNED_BYTE, img.data);
}

void Texture3D::setFront(char *FileName)
{
    Texture3D::Img img;
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureObj);
    img = loadBMP(FileName);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, img.width, img.height, 0, GL_BGR, GL_UNSIGNED_BYTE, img.data);
}

void Texture3D::setBack(char *FileName)
{
    Texture3D::Img img;
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureObj);
    img = loadBMP(FileName);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, img.width, img.height, 0, GL_BGR, GL_UNSIGNED_BYTE, img.data);
}

void Texture3D::setTop(char *FileName)
{
    Texture3D::Img img;
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureObj);
    img = loadBMP(FileName);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, img.width, img.height, 0, GL_BGR, GL_UNSIGNED_BYTE, img.data);
}

void Texture3D::setBottom(char *FileName)
{
    Texture3D::Img img;
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureObj);
    img = loadBMP(FileName);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, img.width, img.height, 0, GL_BGR, GL_UNSIGNED_BYTE, img.data);
}
