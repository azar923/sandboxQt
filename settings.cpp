#include "settings.h"
#include "ui_settings.h"
#include "globalsettings.h"
#include <QFileDialog>
#include <QMessageBox>

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    setWindowTitle("Settings");

    ui->chooseColor->setAutoDefault(false);
    ui->setDirection->setAutoDefault(false);
    ui->loadGrass->setAutoDefault(false);
    ui->loadWater->setAutoDefault(false);
    ui->loadSand->setAutoDefault(false);
    ui->loadStone->setAutoDefault(false);
    ui->loadSnow->setAutoDefault(false);
    ui->loadSkyboxLeft->setAutoDefault(false);
    ui->loadSkyboxRight->setAutoDefault(false);
    ui->loadSkyboxTop->setAutoDefault(false);
    ui->loadSkyboxBottom->setAutoDefault(false);
    ui->loadSkyboxFront->setAutoDefault(false);
    ui->loadSkyboxBack->setAutoDefault(false);
    ui->reset->setAutoDefault(false);
    ui->reconfigure->setAutoDefault(false);


    ui->maxHeight->setMinimum(0);
    ui->maxHeight->setMaximum(1000);
    ui->maxHeight->setValue(GlobalSettings::getInstance()->getMaxHeight() / 10);

    ui->minHeight->setMinimum(0);
    ui->minHeight->setMaximum(1000);
    ui->minHeight->setValue(GlobalSettings::getInstance()->getMinHeight() / 10);

    ui->diffuse->setMinimum(0);
    ui->diffuse->setMaximum(100);
    ui->diffuse->setValue(GlobalSettings::getInstance()->getLightIntensity());

    ui->minHeightValue->setText(QString::number(ui->minHeight->value()));
    ui->maxHeightValue->setText(QString::number(ui->maxHeight->value()));


    ui->contrast->setMinimum(0);
    ui->contrast->setMaximum(100);
    ui->contrast->setValue(GlobalSettings::getInstance()->getContrast());
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

    connect(ui->maxHeight, SIGNAL(sliderMoved(int)), this, SLOT(setKinectMaxHeight(int)));
    connect(ui->minHeight, SIGNAL(sliderMoved(int)), this, SLOT(setKinectMinHeight(int)));


    connect(ui->diffuse, SIGNAL(sliderMoved(int)), this, SLOT(setLightDiffuseIntensity(int)));

    connect(ui->contrast, SIGNAL(sliderMoved(int)), this, SLOT(setContrast(int)));



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


    connect(ui->terrainTextures, SIGNAL(activated(int)), this, SLOT(changeTerrain(int)));


    connect(ui->waterMax, SIGNAL(sliderMoved(int)), this, SLOT(setWaterMax(int)));
    connect(ui->sandMax, SIGNAL(sliderMoved(int)), this, SLOT(setSandMax(int)));
    connect(ui->grassMax, SIGNAL(sliderMoved(int)), this, SLOT(setGrassMax(int)));
    connect(ui->stoneMax, SIGNAL(sliderMoved(int)), this, SLOT(setStoneMax(int)));

    connect(ui->reset, SIGNAL(clicked(bool)), this, SLOT(resetSettings()));

    connect(ui->changeSkybox, SIGNAL(activated(int)), this, SLOT(changeSkybox(int)));


    connect(ui->loadSkyboxLeft, SIGNAL(pressed()), this, SLOT(setSkyboxLeft()));
    connect(ui->loadSkyboxRight, SIGNAL(pressed()), this, SLOT(setSkyboxRight()));
    connect(ui->loadSkyboxTop, SIGNAL(pressed()), this, SLOT(setSkyboxTop()));
    connect(ui->loadSkyboxBottom, SIGNAL(pressed()), this, SLOT(setSkyboxBottom()));
    connect(ui->loadSkyboxFront, SIGNAL(pressed()), this, SLOT(setSkyboxFront()));
    connect(ui->loadSkyboxBack, SIGNAL(pressed()), this, SLOT(setSkyboxBack()));

    ui->loadGrass->hide();
    ui->loadSand->hide();
    ui->loadSnow->hide();
    ui->loadStone->hide();
    ui->loadWater->hide();

    ui->loadSkyboxLeft->hide();
    ui->loadSkyboxRight->hide();
    ui->loadSkyboxTop->hide();
    ui->loadSkyboxBottom->hide();
    ui->loadSkyboxFront->hide();
    ui->loadSkyboxBack->hide();

    bool toFlipVertically = GlobalSettings::getInstance()->getFlipVertical();
    if (toFlipVertically)
        ui->flip_vert->setCheckState(Qt::Checked);

    bool toFlipHorisontally = GlobalSettings::getInstance()->getFlipHorisontal();
    if (toFlipHorisontally)
        ui->flip_hor->setCheckState(Qt::Checked);




    bool sensorMode = GlobalSettings::getInstance()->getSensorMode();
    qDebug() << "SensorMode: " << sensorMode;

    if (!sensorMode)
    {
        QPalette palette = ui->pleaseConnect->palette();
        palette.setColor(ui->pleaseConnect->foregroundRole(), Qt::red);
        ui->pleaseConnect->setPalette(palette);
        ui->pleaseConnect->setText("Please, connect depth sensor to get access to these settings");

        ui->flip_hor->setDisabled(true);
        ui->flip_vert->setDisabled(true);
        ui->minHeight->setDisabled(true);
        ui->maxHeight->setDisabled(true);
        ui->reconfigure->setDisabled(true);
    }

    else
        ui->pleaseConnect->hide();

    colorDialog = new QColorDialog(this);

    connect(ui->chooseColor, SIGNAL(pressed()), this, SLOT(chooseColor()));
    connect(ui->setDirection, SIGNAL(pressed()), this, SLOT(setDirection()));

    lightDirection = new LightDirection(this);
    int window_width = GlobalSettings::getInstance()->getScreenWidth();
    int window_height = GlobalSettings::getInstance()->getScreenHeight();
    lightDirection->resize(window_width / 3, window_height / 3);

    connect(ui->flip_hor, SIGNAL(toggled(bool)), this, SLOT(setHorisontalFlip(bool)));
    connect(ui->flip_vert, SIGNAL(toggled(bool)), this, SLOT(setVerticalFlip(bool)));

    connect(ui->reconfigure, SIGNAL(pressed()), this, SLOT(reconfigure()));

}

void Settings::reconfigure()
{
    QMessageBox* box = new QMessageBox(this);
    box->setText("You will be able to reconfigure your sensor after next start of this program");
    box->show();
    box->setWindowTitle("Reconfigure sensor");
    GlobalSettings::getInstance()->setFirstTime(true);
}

void Settings::setDirection()
{

    lightDirection->setPixmap();
    lightDirection->show();

}

void Settings::chooseColor()
{
    QColorDialog* d = new QColorDialog(this);
    QColor color = d->getColor(Qt::white, this, "LightColor");

    if (color.isValid())
    {
        Scene::getInstance()->lighting->dirLight.setColorR(color.redF());
        Scene::getInstance()->lighting->dirLight.setColorG(color.greenF());
        Scene::getInstance()->lighting->dirLight.setColorB(color.blueF());
        GlobalSettings::getInstance()->setLightColorR(color.redF() * 100);
        GlobalSettings::getInstance()->setLightColorG(color.greenF() * 100);
        GlobalSettings::getInstance()->setLightColorB(color.blueF() * 100);
    }
}

Settings::~Settings()
{
    delete ui;
}

void Settings::resetSettings()
{
    GlobalSettings::getInstance()->setMinHeight(560);
    Scene::getInstance()->terrain->stream->setMinDepth(560);

    GlobalSettings::getInstance()->setMaxHeight(640);
    Scene::getInstance()->terrain->stream->setMaxDepth(640);

    GlobalSettings::getInstance()->setHorisontalFlip(false);
    Scene::getInstance()->terrain->stream->setHorisontalFlip(false);

    GlobalSettings::getInstance()->setVerticalFlip(false);
    Scene::getInstance()->terrain->stream->setVerticalFlip(false);

    GlobalSettings::getInstance()->setWaterMax(50);
    Scene::getInstance()->terrain->setWaterMax(50);

    GlobalSettings::getInstance()->setSandMax(100);
    Scene::getInstance()->terrain->setSandMax(100);

    GlobalSettings::getInstance()->setGrassMax(150);
    Scene::getInstance()->terrain->setGrassMax(150);

    GlobalSettings::getInstance()->setStoneMax(200);
    Scene::getInstance()->terrain->setStoneMax(200);

    Scene::getInstance()->terrain->setAlpha(1.5);
    Scene::getInstance()->terrain->setBeta(0.25);

    GlobalSettings::getInstance()->setLightDirectionX(10);
    GlobalSettings::getInstance()->setLightDirectionY(100);
    GlobalSettings::getInstance()->setLightDirectionZ(10);
    GlobalSettings::getInstance()->setLightColorR(100);
    GlobalSettings::getInstance()->setLightColorG(100);
    GlobalSettings::getInstance()->setLightColorB(100);
    GlobalSettings::getInstance()->setLightIntensity(100);
    Scene::getInstance()->lighting->dirLight.setDirectionX(0.1);
    Scene::getInstance()->lighting->dirLight.setDirectionY(1.0);
    Scene::getInstance()->lighting->dirLight.setDirectionZ(0.1);
    Scene::getInstance()->lighting->dirLight.setColorR(1.0);
    Scene::getInstance()->lighting->dirLight.setColorG(1.0);
    Scene::getInstance()->lighting->dirLight.setColorB(1.0);
    Scene::getInstance()->lighting->dirLight.setDiffuseIntensity(1.0);

    ui->waterMax->setValue(50);
    ui->sandMax->setValue(100);
    ui->grassMax->setValue(150);
    ui->stoneMax->setValue(200);

    ui->waterMaxLabel->setText(QString::number(ui->waterMax->value()));
    ui->sandMaxLabel->setText(QString::number(ui->sandMax->value()));
    ui->grassMaxLabel->setText(QString::number(ui->grassMax->value()));
    ui->stoneMaxLabel->setText(QString::number(ui->stoneMax->value()));

    ui->contrast->setValue(50);
    GlobalSettings::getInstance()->setContrast(50);

    ui->contrastValue->setText(QString::number(50));
    float alpha = 1.0 + float(50) * 0.02;
    float beta = float(50) / 100.0;
    Scene::getInstance()->terrain->setBeta(beta);
    Scene::getInstance()->terrain->setAlpha(alpha);





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

    Scene::getInstance()->terrain->setWaterTexture("/home/maxim/sandbox_mat/terrain/water.bmp");
    Scene::getInstance()->terrain->setSandTexture("/home/maxim/sandbox_mat/terrain/sand.bmp");
    Scene::getInstance()->terrain->setGrassTexture("/home/maxim/sandbox_mat/terrain/grass.bmp");
    Scene::getInstance()->terrain->setStoneTexture("/home/maxim/sandbox_mat/terrain/stone.bmp");
    Scene::getInstance()->terrain->setSnowTexture("/home/maxim/sandbox_mat/terrain/snow.bmp");

    Scene::getInstance()->skybox->setLeft("/home/maxim/sandbox_mat/sea/left.bmp");
    Scene::getInstance()->skybox->setRight("/home/maxim/sandbox_mat/sea/right.bmp");
    Scene::getInstance()->skybox->setTop("/home/maxim/sandbox_mat/sea/top.bmp");
    Scene::getInstance()->skybox->setBottom("/home/maxim/sandbox_mat/sea/bottom.bmp");
    Scene::getInstance()->skybox->setFront("/home/maxim/sandbox_mat/sea/front.bmp");
    Scene::getInstance()->skybox->setBack("/home/maxim/sandbox_mat/sea/back.bmp");


    ui->terrainTextures->setCurrentIndex(0);
    ui->changeSkybox->setCurrentIndex(0);

    ui->diffuse->setValue(100);

    ui->maxHeight->setValue(64);
    ui->minHeight->setValue(56);




}

void Settings::changeSkybox(int index)
{
    if (index == 2)
    {
        ui->loadSkyboxLeft->show();
        ui->loadSkyboxRight->show();
        ui->loadSkyboxTop->show();
        ui->loadSkyboxBottom->show();
        ui->loadSkyboxFront->show();
        ui->loadSkyboxBack->show();
    }

    else
    {
        ui->loadSkyboxLeft->hide();
        ui->loadSkyboxRight->hide();
        ui->loadSkyboxTop->hide();
        ui->loadSkyboxBottom->hide();
        ui->loadSkyboxFront->hide();
        ui->loadSkyboxBack->hide();
    }
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

void Settings::setResolution(int index)
{
    if (index == 1)
        Scene::getInstance()->changeTerrain();
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

    if (!filename.isEmpty())
    {
        Scene::getInstance()->terrain->setSandTexture((char*)filename.toStdString().c_str());
        ui->sandImg->setPixmap(QPixmap::fromImage(QImage(filename)));
    }
}

void Settings::setGrassTexture()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                            tr("Open Image"), "/home/maxim/", tr("Image Files (*.bmp)"));

    if (!filename.isEmpty())
    {
        Scene::getInstance()->terrain->setGrassTexture((char*)filename.toStdString().c_str());
        ui->grassImg->setPixmap(QPixmap::fromImage(QImage(filename)));
    }
}

void Settings::setStoneTexture()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                            tr("Open Image"), "/home/maxim/", tr("Image Files (*.bmp)"));

    if (!filename.isEmpty())
    {
        Scene::getInstance()->terrain->setStoneTexture((char*)filename.toStdString().c_str());
        ui->stoneImg->setPixmap(QPixmap::fromImage(QImage(filename)));
    }
}

void Settings::setSnowTexture()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                            tr("Open Image"), "/home/maxim/", tr("Image Files (*.bmp)"));

    if (!filename.isEmpty())
    {
        Scene::getInstance()->terrain->setSnowTexture((char*)filename.toStdString().c_str());
        ui->snowImg->setPixmap(QPixmap::fromImage(QImage(filename)));
    }
}

void Settings::setSkyboxLeft()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                            tr("Open Image"), "/home/maxim/", tr("Image Files (*.bmp)"));

    if (!filename.isEmpty())
    {
        Scene::getInstance()->skybox->setLeft((char*)filename.toStdString().c_str());

        ui->imgSkyboxLeft->setPixmap(QPixmap::fromImage(QImage(filename)));
    }

}

void Settings::setSkyboxRight()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                            tr("Open Image"), "/home/maxim/", tr("Image Files (*.bmp)"));

    if (!filename.isEmpty())
    {

       Scene::getInstance()->skybox->setRight((char*)filename.toStdString().c_str());
        ui->imgSkyboxRight->setPixmap(QPixmap::fromImage(QImage(filename)));
    }

}

void Settings::setSkyboxTop()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                            tr("Open Image"), "/home/maxim/", tr("Image Files (*.bmp)"));

    if (!filename.isEmpty())
    {
        Scene::getInstance()->skybox->setTop((char*)filename.toStdString().c_str());
        ui->imgSkyboxTop->setPixmap(QPixmap::fromImage(QImage(filename)));
    }

}

void Settings::setSkyboxBottom()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                            tr("Open Image"), "/home/maxim/", tr("Image Files (*.bmp)"));

    if (!filename.isEmpty())
    {
        Scene::getInstance()->skybox->setBottom((char*)filename.toStdString().c_str());
        ui->imgSkyboxBottom->setPixmap(QPixmap::fromImage(QImage(filename)));
    }

}

void Settings::setSkyboxFront()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                            tr("Open Image"), "/home/maxim/", tr("Image Files (*.bmp)"));

    if (!filename.isEmpty())
    {
        Scene::getInstance()->skybox->setFront((char*)filename.toStdString().c_str());
        ui->imgSkyboxFront->setPixmap(QPixmap::fromImage(QImage(filename)));
    }

}

void Settings::setSkyboxBack()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                            tr("Open Image"), "/home/maxim/", tr("Image Files (*.bmp)"));

    if (!filename.isEmpty())
    {
        Scene::getInstance()->skybox->setBack((char*)filename.toStdString().c_str());
        ui->imgSkyboxBack->setPixmap(QPixmap::fromImage(QImage(filename)));
    }

}



void Settings::setLightDiffuseIntensity(int d)
{
    Scene::getInstance()->lighting->dirLight.setDiffuseIntensity(float(d/100.0));
    GlobalSettings::getInstance()->setLightIntensity(d);
}


void Settings::setKinectMaxHeight(int maxHeight)
{
   ui->maxHeightValue->setText(QString::number(ui->maxHeight->value()));
   GlobalSettings::getInstance()->setMaxHeight(maxHeight * 10);
   Scene::getInstance()->terrain->stream->setMaxDepth(maxHeight * 10);
}


void Settings::setKinectMinHeight(int minHeight)
{
    ui->minHeightValue->setText(QString::number(ui->minHeight->value()));
    GlobalSettings::getInstance()->setMinHeight(minHeight * 10);
    Scene::getInstance()->terrain->stream->setMinDepth(minHeight * 10);
}


void Settings::setContrast(int contrast)
{
    GlobalSettings::getInstance()->setContrast(contrast);
    ui->contrastValue->setText(QString::number(contrast));
    float alpha = 1.0 + float(contrast) * 0.02;
    float beta = float(contrast) / 100.0;
    Scene::getInstance()->terrain->setBeta(beta);
    Scene::getInstance()->terrain->setAlpha(alpha);
}

void Settings::setHorisontalFlip(bool checked)
{
    if (checked)
    {
        Scene::getInstance()->terrain->stream->setHorisontalFlip(true);
        GlobalSettings::getInstance()->setHorisontalFlip(true);
    }
    else
    {
        Scene::getInstance()->terrain->stream->setHorisontalFlip(false);
        GlobalSettings::getInstance()->setHorisontalFlip(false);
    }
}

void Settings::setVerticalFlip(bool checked)
{
    qDebug() << checked;
    if (checked)
    {
        Scene::getInstance()->terrain->stream->setVerticalFlip(true);
        GlobalSettings::getInstance()->setVerticalFlip(true);
    }
    else
    {
        Scene::getInstance()->terrain->stream->setVerticalFlip(false);
        GlobalSettings::getInstance()->setVerticalFlip(false);
    }
}

