#include "filestream.h"
#include <fstream>
#include <opencv2/opencv.hpp>



Filestream::Filestream(const char* filename, int _width, int _height, int _offsetLeft, int _offsetRight, int _offsetTop, int _offsetBottom)
{
    isCropped = false;
    width = _width;
    height = _height;
    toFlip = false;
    data = new unsigned char[width * height];

    loadFromRawFile(filename, width * height, data);

    offsetLeft = _offsetLeft;
    offsetRight = _offsetRight;
    offsetTop = _offsetTop;
    offsetBottom = _offsetBottom;

    width_cropped = width - offsetLeft - offsetRight;
    height_cropped = height - offsetTop - offsetBottom;

    cropped_data = new unsigned char[width_cropped * height_cropped];

    crop(offsetLeft, offsetRight, offsetTop, offsetBottom);

}

void Filestream::loadFromImage()
{
    cv::Mat img = cv::imread("/home/maxim/h_or.jpg",0);
    for (int y = 0; y < img.rows; y++)
        for (int x = 0; x < img.cols; x++)
    {
        data[y * img.cols + x] = (unsigned char)img.at<uchar>(cv::Point(x,y));
    }
}

void Filestream::loadFromRawFile(const char* filename, int nSize, unsigned char* data)
{
    FILE *pFile = NULL;
    pFile = fopen( filename, "rb" );
    fread( data, 1, nSize, pFile );
    fclose(pFile);
}
void Filestream::crop(int left, int right, int top, int bottom)
{

    cv::Mat mat;
    mat.create(height, width, CV_8UC1);

    for (int y = 0; y < mat.rows; y++)
        for (int x = 0; x < mat.cols; x++)
        {
            mat.at<uchar>(cv::Point(x,y)) = data[y * mat.cols + x];
        }

    cv::Rect roi = cv::Rect(offsetLeft, offsetTop, width_cropped, height_cropped);
    mat = mat(roi);

    for (int y = 0; y < mat.rows; y++)
        for (int x = 0; x < mat.cols; x++)
    {
        cropped_data[y * mat.cols + x] = (unsigned char)mat.at<uchar>(cv::Point(x,y));
    }

}

unsigned char* Filestream::getData() {
    return cropped_data;
}

void Filestream::setMaxDepth(int maxDepth)
{

}

void Filestream::setFlip(bool _toFlip)
{
    toFlip = _toFlip;
}

void Filestream::setMinDepth(int minDepth)
{

}
