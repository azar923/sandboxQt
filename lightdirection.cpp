#include "lightdirection.h"
#include "ui_lightdirection.h"
#include "globalsettings.h"
#include "scene.h"

LightDirection::LightDirection(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LightDirection)
{
    ui->setupUi(this);
    setWindowTitle("Choose light direction");

    int width = this->width();
    int height = this->height();
    float new_x = (float)GlobalSettings::getInstance()->getLightDirectionX() / 100.0;
    float new_y = (float)GlobalSettings::getInstance()->getLightDirectionZ() / 100.0;

    int lightPos_x = (new_x + 1.0) * (float)width / 2.0;
    int lightPos_y = (new_y + 1.0) * (float)height / 2.0;

    lightPos = QPoint(lightPos_x, lightPos_y);
    toDraw = true;

    light = new QImage("/home/maxim/sun.png");

}



void LightDirection::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    if (this->isEnabled())
    {
        qDebug() << "We are here";
        QPen pen;
        pen.setWidth(10);
        pen.setColor(Qt::red);
        painter.setPen(pen);

        Mat sandbox_view = *Scene::getInstance()->getSandboxView();
        cvtColor(sandbox_view, sandbox_view, CV_BGRA2RGB);
        Mat resized  = Mat::zeros(sandbox_view.cols /3, sandbox_view.rows / 3, CV_8UC3);
        cv::resize(sandbox_view, resized, Size(resized.rows, resized.cols));
        flip(resized, resized, 0);

        QImage q_image((uchar*)resized.data,resized.cols, resized.rows, resized.step, QImage::Format_RGB888);

        painter.drawImage(0,0,q_image);
        painter.drawImage(lightPos.x() - light->width() / 2, lightPos.y() - light->height() / 2, *light);
        toDraw = false;
        painter.end();
    }

}

LightDirection::~LightDirection()
{
    delete ui;
}

void LightDirection::mousePressEvent(QMouseEvent *event)
{
    QPoint pos = event->pos();
    int width = this->width();
    int height = this->height();
    float new_x = pos.x() * 2.0 / (float)width - 1;
    float new_y = pos.y() * 2.0 / (float)height - 1;

    Scene::getInstance()->lighting->dirLight.setDirectionX(new_x);
    Scene::getInstance()->lighting->dirLight.setDirectionZ(new_y);

    Mat sandbox_view = *Scene::getInstance()->getSandboxView();
    cvtColor(sandbox_view, sandbox_view, CV_BGRA2RGB);
    Mat resized  = Mat::zeros(sandbox_view.cols /3, sandbox_view.rows / 3, CV_8UC3);
    cv::resize(sandbox_view, resized, Size(resized.rows, resized.cols));

    QImage q_image((uchar*)resized.data,resized.cols, resized.rows, resized.step, QImage::Format_RGB888);

    GlobalSettings::getInstance()->setLightDirectionX(new_x * 100);
    GlobalSettings::getInstance()->setLightDirectionZ(new_y * 100);

    lightPos = QPoint(event->pos());
    toDraw = true;
    repaint();
}
