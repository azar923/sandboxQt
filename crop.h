#ifndef CROP_H
#define CROP_H

#include <QDialog>
#include <QRubberBand>
#include <QMouseEvent>
#include <QPainter>
#include <opencv2/opencv.hpp>

namespace Ui {
class Crop;
}

class Crop : public QDialog
{
    Q_OBJECT

public:
    explicit Crop(QWidget *parent = 0);
    ~Crop();

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

    void paintEvent(QPaintEvent* event);
    void drawRect(QPainter* painter, QRect* rect);

    void setX(int _x);
    void setY(int _y);
    void setHeight(int _height);
    void setWidth(int _width);
    void setup();


    int offsetRight;
    int offsetLeft;
    int offsetBottom;
    int offsetTop;

    bool isAreaSelected;

    void setDepthMap(cv::Mat img);

private:
    Ui::Crop *ui;
    QRubberBand* rubberBand;
    QPoint origin;
    QRect* image;
    QRect cropping;
    bool toDraw;
    bool toClear;
    QPoint lastPos;
    bool outOfRange;
    QImage depthmap;

    int x;
    int y;
    int width;
    int height;



signals:
    void croppingFinished();
    void croppingClosed();

public slots:
    void finished();
    void quit();
    void setDefaultCropping();
};

#endif // CROP_H
