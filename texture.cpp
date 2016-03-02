#include "texture.h"
#include <fstream>

Texture::Img Texture::loadBMP(char* filename)
{
    unsigned char header[54];                // Each BMP file begins by a 54-bytes header
    unsigned int dataPos;                    // Position in the file where the actual data begins
    unsigned int width, height;
    unsigned int imageSize;                  // = width*height*3

    unsigned char * data;                    // Actual RGB data

    FILE * file = fopen(filename,"rb");

    if (!file)
        {
            printf("Image could not be opened\n");
            printf(filename);

        }

    if ( fread(header, 1, 54, file)!=54 )
        {
            printf("Not a correct BMP file\n");

        }

    if ( header[0]!='B' || header[1]!='M' )
        {
            printf("Not a correct BMP file\n");

        }

    dataPos    = *(int*)&(header[0x0A]);
    imageSize  = *(int*)&(header[0x22]);
    width      = *(int*)&(header[0x12]);
    height     = *(int*)&(header[0x16]);

    if (imageSize==0)    imageSize=width*height*3;		// 3 : one byte for each Red, Green and Blue component
    if (dataPos==0)      dataPos=54;					// The BMP header is done that way

    data = new unsigned char[imageSize];


    fread(data,1,imageSize,file);
    fclose(file);

    Texture::Img img;
    img.data = data;
    img.width = width;
    img.height = height;

    return img;

}

int Texture::getIndex()
{
    return index;
}
