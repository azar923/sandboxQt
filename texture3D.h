#ifndef TEXTURE3D_H
#define TEXTURE3D_H

#include "texture.h"

class Texture3D : public Texture
{
public:
    Texture3D(char* right, char* left, char* front, char* back, char* bottom, char* top, int _index);
    bool load();

private:
    char* m_left;
    char* m_right;
    char* m_top;
    char* m_bottom;
    char* m_front;
    char* m_back;
};

#endif // TEXTURE3D_H
