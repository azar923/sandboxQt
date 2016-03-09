#ifndef DATASTREAM_H
#define DATASTREAM_H


class DataStream
{
public:
    virtual unsigned char* getData() = 0;
    virtual void setMaxDepth(int maxDepth) = 0;
    virtual void setMinDepth(int minDepth) = 0;
    virtual void setHorisontalFlip(bool _toFlipHorisontally) = 0;
    virtual void setVerticalFlip(bool _toFlipVertically) = 0;
};

#endif // DATASTREAM_H
