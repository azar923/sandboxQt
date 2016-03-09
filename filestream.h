#ifndef FILESTREAM_H
#define FILESTREAM_H
#include "datastream.h"
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>

class Filestream : public DataStream
{
public:
    Filestream(const char* filename, int _width, int _height, int _offsetLeft = 0, int _offsetRight = 0, int _offsetTop = 0, int _offsetBottom = 0);
    unsigned char* getData();
    void crop(int left, int right, int top, int bottom);
    void setMaxDepth(int maxDepth);
    void setMinDepth(int minDepth);

    void setHorisontalFlip(bool _toFlipHorisontally);
    void setVerticalFlip(bool _toFlipVertically);


private:
    void loadFromRawFile (const char* strName, int nSize, unsigned char* data);
    void loadFromImage();

    unsigned char* data;
    unsigned char* cropped_data;
    int width;
    int height;
    bool isCropped;
    int width_cropped;
    int height_cropped;

    int offsetLeft;
    int offsetRight;
    int offsetTop;
    int offsetBottom;

    bool toFlip;
};

#endif // FILESTREAM_H
