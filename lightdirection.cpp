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


}

void LightDirection::setPixmap()
{
   ui->label->resize(this->size());
   Mat sandbox_view = *Scene::getInstance()->getSandboxView();
   cvtColor(sandbox_view, sandbox_view, CV_BGRA2RGB);
   QImage q_image((uchar*)sandbox_view.data,sandbox_view.cols, sandbox_view.rows, sandbox_view.step, QImage::Format_RGB888);
   ui->label->setPixmap(QPixmap::fromImage(q_image));

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
    QImage q_image((uchar*)sandbox_view.data,sandbox_view.cols, sandbox_view.rows, sandbox_view.step, QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(q_image));

    GlobalSettings::getInstance()->setLightDirectionX(new_x * 100);
    GlobalSettings::getInstance()->setLightDirectionZ(new_y * 100);
}
