#include "sandbox.h"
#include "ui_sandbox.h"
#include <QDebug>

Sandbox::Sandbox(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Sandbox)
{
    ui->setupUi(this);

    renderTimer = new QTimer(this);

    connect(renderTimer, SIGNAL(timeout()), this, SLOT(renderSlot()));

    ui->direction_Z->setMinimum(0);
    ui->direction_Z->setMaximum(100);
    ui->direction_Z->setValue(10);

    ui->direction_Y->setMinimum(0);
    ui->direction_Y->setMaximum(100);
    ui->direction_Y->setValue(100);

    ui->direction_X->setMinimum(0);
    ui->direction_X->setMaximum(100);
    ui->direction_X->setValue(10);

    ui->color_R->setMinimum(0);
    ui->color_R->setMaximum(100);
    ui->color_R->setValue(100);

    ui->color_G->setMinimum(0);
    ui->color_G->setMaximum(100);
    ui->color_G->setValue(100);

    ui->color_B->setMinimum(0);
    ui->color_B->setMaximum(100);
    ui->color_B->setValue(100);

    ui->maxHeight->setMinimum(0);
    ui->maxHeight->setMaximum(10000);
    ui->maxHeight->setValue(640);

    ui->minHeight->setMinimum(0);
    ui->minHeight->setMaximum(10000);
    ui->minHeight->setValue(560);

    ui->minHeightValue->setText(QString::number(ui->minHeight->value()));
    ui->maxHeightValue->setText(QString::number(ui->maxHeight->value()));




    connect(ui->direction_Z, SIGNAL(sliderMoved(int)), this, SLOT(setLightDirectionZ(int)));
    connect(ui->direction_Y, SIGNAL(sliderMoved(int)), this, SLOT(setLightDirectionY(int)));
    connect(ui->direction_X, SIGNAL(sliderMoved(int)), this, SLOT(setLightDirectionX(int)));
    connect(ui->color_R,     SIGNAL(sliderMoved(int)), this, SLOT(setLightColorR(int)));
    connect(ui->color_G,     SIGNAL(sliderMoved(int)), this, SLOT(setLightColorG(int)));
    connect(ui->color_B,     SIGNAL(sliderMoved(int)), this, SLOT(setLightColorB(int)));

    connect(ui->maxHeight, SIGNAL(sliderMoved(int)), this, SLOT(setKinectMaxHeight(int)));
    connect(ui->minHeight, SIGNAL(sliderMoved(int)), this, SLOT(setKinectMinHeight(int)));

    connect(ui->exit, SIGNAL(pressed()), this, SLOT(quit()));
    connect(ui->start, SIGNAL(pressed()), this, SLOT(start()));

  //  showFullScreen();


    renderTimer->start(20);
}

Sandbox::~Sandbox()
{
    delete ui;
}

void Sandbox::quit()
{
    close();
}

void Sandbox::start()
{
    Scene::getInstance()->setWindowSize(this->width(), this->height());
    Scene::getInstance()->terrain->setSandboxMode();
    ui->widget->resize(this->width(), this->height());
    ui->widget->move(0,0);
    ui->widget->raise();
    ui->widget->setFocus();
}

void Sandbox::renderSlot()
{
    ui->widget->update();
    Mat* sandboxView = Scene::getInstance()->getSandboxView();
    QImage sandbox_view(sandboxView->data, sandboxView->cols, sandboxView->rows, sandboxView->step, QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(sandbox_view));
}


void Sandbox::setLightDirectionZ(int z)
{
    Scene::getInstance()->lighting->dirLight.setDirectionZ(float(z/100.0));
}

void Sandbox::setLightDirectionY(int y)
{
    Scene::getInstance()->lighting->dirLight.setDirectionY(float(y/100.0));
}


void Sandbox::setLightDirectionX(int x)
{
    Scene::getInstance()->lighting->dirLight.setDirectionX(float(x/100.0));
}

void Sandbox::setLightColorR(int r)
{
    Scene::getInstance()->lighting->dirLight.setColorR(float(r/100.0));
}

void Sandbox::setLightColorG(int g)
{
    Scene::getInstance()->lighting->dirLight.setColorG(float(g/100.0));
}


void Sandbox::setLightColorB(int b)
{
    Scene::getInstance()->lighting->dirLight.setColorB(float(b/100.0));
}

void Sandbox::setKinectMaxHeight(int maxHeight)
{
    ui->maxHeightValue->setText(QString::number(ui->maxHeight->value()));
    Scene::getInstance()->terrain->stream->setMaxDepth(maxHeight);
}


void Sandbox::setKinectMinHeight(int minHeight)
{
    ui->minHeightValue->setText(QString::number(ui->minHeight->value()));
    Scene::getInstance()->terrain->stream->setMinDepth(minHeight);
}



