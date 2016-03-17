#ifndef INPUTSTREAM_H
#define INPUTSTREAM_H

#include <openni2/OpenNI.h>
#include <opencv2/opencv.hpp>
#include <vector>
#include "datastream.h"


using namespace cv;
using namespace openni;
using namespace std;

class InputStream : public DataStream
{
public:
    InputStream(int _width, int _height, int _min_depth, int _max_depth, int _offsetLeft = 0, int _offsetRight = 0, int _offsetTop = 0, int _offsetBottom = 0);
    unsigned char* getData();
    void initialize();
    static bool isSensorConnected();
    void setMaxDepth(int maxDepth);
    void setMinDepth(int minDepth);
    void setHorisontalFlip(bool _toFlipHorisontally);
    void setVerticalFlip(bool _toFlipVertically);
    static int getConnectedSensorType();
    cv::Mat img_depth;
    Mat getRawMat();
   void Terminate();
    ~InputStream();
private:

    static int sensorType;
    openni::Status rc_depth ;
    openni::Device device;
    openni::VideoStream depth;
    const char* deviceURI;
    openni::VideoFrameRef* frame;
    openni::VideoMode videomode;



    uint16_t* raw;
    uint16_t* filtered_statistic;
    uint16_t* average;
    unsigned char* filtered_data;
    unsigned char* cropped_data;

    bool filterStatistic(int data_delta);

    bool GetDepthData(uint16_t* dst, int size, int _min_depth, int _max_depth);


    bool toFlipVertically;
    bool toFlipHorisontally;

    bool filterData();


    int width;
    int height;

    int width_cropped;
    int height_cropped;

    Mat raw_mat;

    uint16_t* history;
    int history_scan_depth;
    int current;
    int history_capacity;
    int min_depth;
    int max_depth;

    int offsetLeft;
    int offsetRight;
    int offsetTop;
    int offsetBottom;

};

#endif // INPUTSTREAM_H
