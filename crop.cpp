#include "crop.h"
#include "ui_crop.h"
#include <QDebug>

Crop::Crop(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Crop)
{
    ui->setupUi(this);

    setWindowTitle("Cropping");
    connect(ui->finish, SIGNAL(pressed()), this, SLOT(finished()));

    connect(this, SIGNAL(destroyed(QObject*)), this, SLOT(quit()));

    isAreaSelected = false;

    ui->finish->setAutoDefault(false);


}

Crop::~Crop()
{
    delete ui;
}

void Crop::quit()
{
    emit croppingClosed();
}

void Crop::setup()
{
    rubberBand = new QRubberBand(QRubberBand::Rectangle, this);

    QPoint topLeft(x, y);
    QPoint bottomRight(x + width, y + height);
    image = new QRect(topLeft, bottomRight);

    toDraw = false;
    toClear = false;

    cropping = QRect(0,0,0,0);
}

void Crop::setX(int _x)
{
    x = _x;
}

void Crop::setDepthMap(cv::Mat img)
{
    QImage q_image((uchar*)img.data,img.cols, img.rows, img.step, QImage::Format_RGB888);
    depthmap = q_image;

}



void Crop::setY(int _y)
{
    y = _y;
}

void Crop::finished()
{
    emit croppingFinished();
    close();
}

void Crop::setWidth(int _width)
{
    width = _width;
}

void Crop::setHeight(int _height)
{
    height = _height;
}

void Crop::drawRect(QPainter *painter, QRect *rect)
{
     painter->drawRect(*rect);
}

void Crop::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen pen;
    pen.setWidth(3);
    pen.setColor(Qt::red);
    painter.setPen(pen);
    painter.drawImage(QPoint(x, y), depthmap);
    outOfRange = false;
    if ((toDraw) && (!outOfRange))
    {
        painter.drawRect(cropping);
        toDraw = false;
    }
    painter.end();

}


void Crop::mousePressEvent(QMouseEvent *event)
{
    origin = event->pos();

    offsetLeft = 0;
    offsetRight = 0;
    offsetTop = 0;
    offsetBottom = 0;

    bool cont = image->contains(origin);
    if (cont)
    {
        rubberBand->setGeometry(QRect(origin, QSize()));
        rubberBand->show();
        repaint();
        cropping = QRect(0,0,0,0);
    }
}

void Crop::mouseMoveEvent(QMouseEvent *event)
{

    rubberBand->setGeometry(QRect(origin, event->pos()).normalized());
    cropping = QRect(origin, event->pos()).normalized();


}

void Crop::mouseReleaseEvent(QMouseEvent *event)
{

    rubberBand->hide();

    bool end_cont = image->contains(event->pos());
    bool origin_cont = image->contains(origin);
    if ((!end_cont) || (!origin_cont))
    {
        outOfRange = true;
        offsetLeft = 0;
        offsetRight = 0;
        offsetTop = 0;
        offsetBottom = 0;
    }
    else
        if ((cropping.width() > 0) && (cropping.height() > 0))
        {
            outOfRange = false;
            toDraw = true;

            offsetLeft = cropping.topLeft().x() - image->topLeft().x();
            offsetRight = image->topRight().x() - cropping.topRight().x();
            offsetTop = cropping.topLeft().y() - image->topLeft().y();
            offsetBottom = image->bottomRight().y() - cropping.bottomRight().y();

            isAreaSelected = true;
        }

    repaint();

}
