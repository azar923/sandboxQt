#include "inputstream.h"
#define MAXDEPTH 255

InputStream::InputStream(int _width, int _height, int _min_depth, int _max_depth, int _offsetLeft, int _offsetRight, int _offsetTop, int _offsetBottom)
{
    rc_depth = openni::OpenNI::initialize();
    deviceURI = openni::ANY_DEVICE;
    width = _width;
    height = _height;
    history_capacity = 10;
    raw = new uint16_t[width * height];

    history = new uint16_t[width * height * history_capacity];
    filtered_statistic = new uint16_t[width * height];
    average = new uint16_t[width * height];
    history_scan_depth = 7;
    img_depth.create(height, width, CV_8UC1);
    min_depth = _min_depth;
    max_depth = _max_depth;
    current = 0;


   offsetLeft = _offsetLeft;
   offsetRight = _offsetRight;
   offsetTop = _offsetTop;
   offsetBottom = _offsetBottom;

   width_cropped = width - offsetLeft - offsetRight;
   height_cropped = height - offsetTop - offsetBottom;

   filtered_data = new unsigned char[width_cropped * height_cropped];



     for (int i = 0; i < width * height; i++)
     {
         raw[i] = 0;
         filtered_statistic[i] = 0;
         history[i] = 0;
         average[i] = 0;
     }


   initialize();

}

bool InputStream::isSensorConnected()
{
    openni::Status status = openni::OpenNI::initialize();
    openni::Array<openni::DeviceInfo> list;
    openni::OpenNI::enumerateDevices(&list);
    int num = list.getSize();
    if (num == 0)
        return false;
    else
        return true;
    openni::OpenNI::shutdown();

}

bool InputStream::initialize()
{
    rc_depth = device.open(deviceURI);

    device.setDepthColorSyncEnabled(true);

    rc_depth = depth.create(device, openni::SENSOR_DEPTH);

        if (rc_depth == openni::STATUS_OK) {
            videomode = depth.getVideoMode();
            videomode.setResolution(width, height);
            depth.setVideoMode(videomode);
            rc_depth= depth.start();

            return true;
        }

        else
        {
            std::cout << "Failed to initialize sensor";
            return false;
        }
}

void InputStream::filterStatistic(int data_delta)
{
    GetDepthData(raw, width * height, min_depth, max_depth);

    for (int i = 0; i < width * height; i++)
    {
        uint16_t b = raw[i];
        uint16_t avg = 0;
        for (int k = 0; k < history_scan_depth; k++)
        {
            avg += history[k * width * height + i];
        }

        average[i] = avg / history_scan_depth;


        if (abs(b - average[i]) < data_delta) {
            filtered_statistic[i] = b;
        }

        history[current * width * height + i] = b;
    }

    current ++;

    if (current == history_scan_depth) {
        current = 0;
     }

}

void InputStream::filterData()
{
    filterStatistic(1);

    for (int y = 0; y < img_depth.rows; y++)
        for (int x = 0; x < img_depth.cols; x++)
    {
        img_depth.at<uchar>(Point(x,y)) = uchar(filtered_statistic[y * img_depth.cols + x]);
    }

    Mat img;
    medianBlur(img_depth, img, 9);

    Mat temp1, temp2;
    Mat depth_small;

    cv::resize(img, depth_small, Size(), 0.2,0.2);

    const unsigned char noDepth = 0;

    cv::inpaint(depth_small, (depth_small == noDepth), temp1, 3.0, INPAINT_TELEA);

    cv::resize(temp1, temp2, img.size());

    temp2.copyTo(img, (img == noDepth));
    GaussianBlur(img, img, Size(7,7), 1.5);

    cv::Rect roi = cv::Rect(offsetLeft, offsetTop, width_cropped, height_cropped);
    img = img(roi);

    flip(img,img, 0);

    for (int y = 0; y < img.rows; y++)
        for (int x = 0; x < img.cols; x++)
    {
        filtered_data[y * img.cols + x] = (unsigned char)img.at<uchar>(Point(x,y));
    }

}


unsigned char* InputStream::getData()
{
    filterData();
    return filtered_data;
}

bool InputStream::GetDepthData(uint16_t* dst, int size, int _min_depth, int _max_depth)
{
    unsigned short data = 0;
    rc_depth = depth.readFrame(&frame);

    int min_depth = _min_depth;
    int max_depth = _max_depth;

    if (rc_depth == openni::STATUS_OK) {
        openni::DepthPixel* pDepth = (openni::DepthPixel*)frame.getData();

    for (int i = 0; i < size; i++)
    {
        data = pDepth[i];

        if (data > max_depth) data = max_depth;
        if (data < min_depth) data = min_depth;
        dst[i] = (unsigned char)((float)(data - min_depth) / (max_depth - min_depth) * MAXDEPTH);
    }
    return true;
    }

    else
    {
        return false;
    }

}

void InputStream::Terminate()
{
    depth.destroy();
    device.close();
    openni::OpenNI::shutdown();
}
