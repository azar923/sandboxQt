#include "settings.h"
#include "ui_settings.h"
#include "globalsettings.h"
#include <QFileDialog>

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    setWindowTitle("Settings");

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
    ui->maxHeight->setValue(GlobalSettings::getInstance()->getMaxHeight());

    ui->minHeight->setMinimum(0);
    ui->minHeight->setMaximum(10000);
    ui->minHeight->setValue(GlobalSettings::getInstance()->getMinHeight());

    ui->diffuse->setMinimum(0);
    ui->diffuse->setMaximum(100);
    ui->diffuse->setValue(100);

    ui->minHeightValue->setText(QString::number(ui->minHeight->value()));
    ui->maxHeightValue->setText(QString::number(ui->maxHeight->value()));


    ui->contrast->setMinimum(0);
    ui->contrast->setMaximum(100);
    ui->contrast->setValue(50);
    ui->contrastValue->setText(QString::number(ui->contrast->value()));

    ui->waterMax->setMinimum(0);
    ui->waterMax->setMaximum(255);
    ui->waterMax->setValue(GlobalSettings::getInstance()->getWaterMax());
    ui->waterMaxLabel->setText(QString::number(ui->waterMax->value()));



    ui->sandMax->setMinimum(0);
    ui->sandMax->setMaximum(255);
    ui->sandMax->setValue(GlobalSettings::getInstance()->getSandMax());
    ui->sandMaxLabel->setText(QString::number(ui->sandMax->value()));

    ui->grassMax->setMinimum(0);
    ui->grassMax->setMaximum(255);
    ui->grassMax->setValue(GlobalSettings::getInstance()->getGrassMax());
    ui->grassMaxLabel->setText(QString::number(ui->grassMax->value()));


    ui->stoneMax->setMinimum(0);
    ui->stoneMax->setMaximum(255);
    ui->stoneMax->setValue(GlobalSettings::getInstance()->getStoneMax());
    ui->stoneMaxLabel->setText(QString::number(ui->stoneMax->value()));

    connect(ui->direction_Z, SIGNAL(sliderMoved(int)), this, SLOT(setLightDirectionZ(int)));
    connect(ui->direction_Y, SIGNAL(sliderMoved(int)), this, SLOT(setLightDirectionY(int)));
    connect(ui->direction_X, SIGNAL(sliderMoved(int)), this, SLOT(setLightDirectionX(int)));
    connect(ui->color_R,     SIGNAL(sliderMoved(int)), this, SLOT(setLightColorR(int)));
    connect(ui->color_G,     SIGNAL(sliderMoved(int)), this, SLOT(setLightColorG(int)));
    connect(ui->color_B,     SIGNAL(sliderMoved(int)), this, SLOT(setLightColorB(int)));

    connect(ui->maxHeight, SIGNAL(sliderMoved(int)), this, SLOT(setKinectMaxHeight(int)));
    connect(ui->minHeight, SIGNAL(sliderMoved(int)), this, SLOT(setKinectMinHeight(int)));


    connect(ui->diffuse, SIGNAL(sliderMoved(int)), this, SLOT(setLightDiffuseIntensity(int)));

    connect(ui->contrast, SIGNAL(sliderMoved(int)), this, SLOT(setContrast(int)));

    connect(ui->flip_hor, SIGNAL(stateChanged(int)), this, SLOT(setHorisontalFlip(int)));
    connect(ui->flip_vert, SIGNAL(stateChanged(int)), this, SLOT(setVerticalFlip(int)));

    connect(ui->loadWater, SIGNAL(pressed()), this, SLOT(setWaterTexture()));
    connect(ui->loadSand, SIGNAL(pressed()), this, SLOT(setSandTexture()));
    connect(ui->loadGrass, SIGNAL(pressed()), this, SLOT(setGrassTexture()));
    connect(ui->loadStone, SIGNAL(pressed()), this, SLOT(setStoneTexture()));
    connect(ui->loadSnow, SIGNAL(pressed()), this, SLOT(setSnowTexture()));

    ui->waterImg->setPixmap(QPixmap::fromImage(QImage("/home/maxim/sandbox_mat/terrain/water.bmp")));
    ui->sandImg->setPixmap(QPixmap::fromImage(QImage("/home/maxim/sandbox_mat/terrain/sand.bmp")));
    ui->grassImg->setPixmap(QPixmap::fromImage(QImage("/home/maxim/sandbox_mat/terrain/grass.bmp")));
    ui->stoneImg->setPixmap(QPixmap::fromImage(QImage("/home/maxim/sandbox_mat/terrain/stone.bmp")));
    ui->snowImg->setPixmap(QPixmap::fromImage(QImage("/home/maxim/sandbox_mat/terrain/snow.bmp")));

    ui->imgSkyboxLeft->setPixmap(QPixmap::fromImage(QImage("/home/maxim/sandbox_mat/sea/left.bmp")));
    ui->imgSkyboxRight->setPixmap(QPixmap::fromImage(QImage("/home/maxim/sandbox_mat/sea/right.bmp")));
    ui->imgSkyboxTop->setPixmap(QPixmap::fromImage(QImage("/home/maxim/sandbox_mat/sea/top.bmp")));
    ui->imgSkyboxBottom->setPixmap(QPixmap::fromImage(QImage("/home/maxim/sandbox_mat/sea/bottom.bmp")));
    ui->imgSkyboxFront->setPixmap(QPixmap::fromImage(QImage("/home/maxim/sandbox_mat/sea/front.bmp")));
    ui->imgSkyboxBack->setPixmap(QPixmap::fromImage(QImage("/home/maxim/sandbox_mat/sea/back.bmp")));


    connect(ui->comboBox, SIGNAL(activated(int)), this, SLOT(changeTerrain(int)));
    connect(ui->resolution, SIGNAL(activated(int)), this, SLOT(setResolution(int)));

    connect(ui->waterMax, SIGNAL(sliderMoved(int)), this, SLOT(setWaterMax(int)));
    connect(ui->sandMax, SIGNAL(sliderMoved(int)), this, SLOT(setSandMax(int)));
    connect(ui->grassMax, SIGNAL(sliderMoved(int)), this, SLOT(setGrassMax(int)));
    connect(ui->stoneMax, SIGNAL(sliderMoved(int)), this, SLOT(setStoneMax(int)));

    ui->loadGrass->hide();
    ui->loadSand->hide();
    ui->loadSnow->hide();
    ui->loadStone->hide();
    ui->loadWater->hide();

}

Settings::~Settings()
{
    delete ui;
}

void Settings::setWaterMax(int waterMax)
{
    Scene::getInstance()->terrain->setWaterMax(waterMax);
    ui->waterMaxLabel->setText(QString::number(ui->waterMax->value()));
    GlobalSettings::getInstance()->setWaterMax(waterMax);
}

void Settings::setSandMax(int sandMax)
{
    Scene::getInstance()->terrain->setSandMax(sandMax);
    ui->sandMaxLabel->setText(QString::number(ui->sandMax->value()));
    GlobalSettings::getInstance()->setSandMax(sandMax);
}

void Settings::setGrassMax(int grassMax)
{
    Scene::getInstance()->terrain->setGrassMax(grassMax);
    ui->grassMaxLabel->setText(QString::number(ui->grassMax->value()));
    GlobalSettings::getInstance()->setGrassMax(grassMax);
}

void Settings::setStoneMax(int stoneMax)
{
    Scene::getInstance()->terrain->setStoneMax(stoneMax);
    ui->stoneMaxLabel->setText(QString::number(ui->stoneMax->value()));
    GlobalSettings::getInstance()->setStoneMax(stoneMax);
}

void Settings::setResolution(int)
{
}

void Settings::changeTerrain(int index)
{
    if (index == 2)
    {
        ui->loadGrass->show();
        ui->loadSand->show();
        ui->loadSnow->show();
        ui->loadStone->show();
        ui->loadWater->show();
    }

    else
    {
        ui->loadGrass->hide();
        ui->loadSand->hide();
        ui->loadSnow->hide();
        ui->loadStone->hide();
        ui->loadWater->hide();
    }
}

void Settings::setWaterTexture()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                            tr("Open Image"), "/home/maxim/", tr("Image Files (*.bmp)"));

    if (!filename.isEmpty())
    {
        Scene::getInstance()->terrain->setWaterTexture((char*)filename.toStdString().c_str());
        ui->waterImg->setPixmap(QPixmap::fromImage(QImage(filename)));
    }
}

void Settings::setSandTexture()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                            tr("Open Image"), "/home/maxim/", tr("Image Files (*.bmp)"));

    Scene::getInstance()->terrain->setSandTexture((char*)filename.toStdString().c_str());
    ui->sandImg->setPixmap(QPixmap::fromImage(QImage(filename)));
}

void Settings::setGrassTexture()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                            tr("Open Image"), "/home/maxim/", tr("Image Files (*.bmp)"));

    Scene::getInstance()->terrain->setGrassTexture((char*)filename.toStdString().c_str());
    ui->grassImg->setPixmap(QPixmap::fromImage(QImage(filename)));
}

void Settings::setStoneTexture()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                            tr("Open Image"), "/home/maxim/", tr("Image Files (*.bmp)"));

    Scene::getInstance()->terrain->setStoneTexture((char*)filename.toStdString().c_str());
    ui->stoneImg->setPixmap(QPixmap::fromImage(QImage(filename)));
}

void Settings::setSnowTexture()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                            tr("Open Image"), "/home/maxim/", tr("Image Files (*.bmp)"));

    Scene::getInstance()->terrain->setSnowTexture((char*)filename.toStdString().c_str());
    ui->snowImg->setPixmap(QPixmap::fromImage(QImage(filename)));
}

void Settings::setLightDirectionZ(int z)
{
    Scene::getInstance()->lighting->dirLight.setDirectionZ(float(z/100.0));
}

void Settings::setLightDirectionY(int y)
{
    Scene::getInstance()->lighting->dirLight.setDirectionY(float(y/100.0));
}


void Settings::setLightDirectionX(int x)
{
    Scene::getInstance()->lighting->dirLight.setDirectionX(float(x/100.0));
}

void Settings::setLightColorR(int r)
{
    Scene::getInstance()->lighting->dirLight.setColorR(float(r/100.0));
}

void Settings::setLightColorG(int g)
{
    Scene::getInstance()->lighting->dirLight.setColorG(float(g/100.0));
}


void Settings::setLightColorB(int b)
{
    Scene::getInstance()->lighting->dirLight.setColorB(float(b/100.0));
}

void Settings::setLightDiffuseIntensity(int d)
{
    Scene::getInstance()->lighting->dirLight.setDiffuseIntensity(float(d/100.0));
}


void Settings::setKinectMaxHeight(int maxHeight)
{
   ui->maxHeightValue->setText(QString::number(ui->maxHeight->value()));
   GlobalSettings::getInstance()->setMaxHeight(maxHeight);
   Scene::getInstance()->terrain->stream->setMaxDepth(maxHeight);
}


void Settings::setKinectMinHeight(int minHeight)
{
    ui->minHeightValue->setText(QString::number(ui->minHeight->value()));
    GlobalSettings::getInstance()->setMinHeight(minHeight);
    Scene::getInstance()->terrain->stream->setMinDepth(minHeight);
}


void Settings::setContrast(int contrast)
{
    ui->contrastValue->setText(QString::number(contrast));
    float alpha = 1.0 + float(contrast) * 0.02;
    float beta = float(contrast) / 100.0;
    Scene::getInstance()->terrain->setBeta(beta);
    Scene::getInstance()->terrain->setAlpha(alpha);
}

void Settings::setHorisontalFlip(int state)
{
    if (state != 0)
        Scene::getInstance()->terrain->stream->setHorisontalFlip(true);
    else
        Scene::getInstance()->terrain->stream->setHorisontalFlip(false);
}

void Settings::setVerticalFlip(int state)
{
    if (state != 0)
        Scene::getInstance()->terrain->stream->setVerticalFlip(true);
    else
        Scene::getInstance()->terrain->stream->setVerticalFlip(false);
}

