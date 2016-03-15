#include "sensorcalibration.h"
#include "ui_sensorcalibration.h"
#include "sandbox.h"
#include <QFileDialog>
#include <QMessageBox>

SensorCalibration::SensorCalibration(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SensorCalibration)
{
    ui->setupUi(this);
    setWindowTitle("Welcome!");
    isConnected = false;
    isSandboxCreated = false;

    crop = new Crop(this);

    isCroppingSetUp = false;


    connect(this->crop, SIGNAL(croppingFinished()), this, SLOT(setCropping()));


    offsetLeft = 0;
    offsetRight = 0;
    offsetTop = 0;
    offsetBottom = 0;

    ui->option->setVisible(false);
    ui->setup->setVisible(false);
    sensorType = -1;

    connect(ui->next, SIGNAL(pressed()), this, SLOT(createSandbox()));

    bool isConnected = InputStream::isSensorConnected();
    QPalette palette = ui->isFound->palette();

    if (isConnected)
    {

        ui->isFound->setText("Depth sensor is found and successfully initialized");
        palette.setColor(ui->isFound->foregroundRole(), Qt::darkGreen);
        ui->isFound->setPalette(palette);
        ui->option->setVisible(true);
        ui->option->setText("Now you can click 'Set up' to adjust sensor settings\n or you can click 'Next' to skip this step and continue with defaults");
        ui->setup->setVisible(true);
        GlobalSettings::getInstance()->setSensorMode(true);

        sensorType = GlobalSettings::getInstance()->getSensorType();

        if (sensorType == 1)
        {
            ui->sensorType->setText("Sensor type : Kinect v2");
            GlobalSettings::getInstance()->setWidth(512);
            GlobalSettings::getInstance()->setHeight(424);
            GlobalSettings::getInstance()->setSensorType(sensorType);

        }

        else if (sensorType == 0)
        {
            ui->sensorType->setText("Sensor type : Kinect v1");
            GlobalSettings::getInstance()->setWidth(640);
            GlobalSettings::getInstance()->setHeight(480);
            GlobalSettings::getInstance()->setSensorType(sensorType);
        }

    }

    else
    {
        palette.setColor(ui->isFound->foregroundRole(), Qt::red);
        ui->isFound->setPalette(palette);
        ui->isFound->setText("There is no depth sensor connected. Connect sensor and click 'Refresh'\n or click 'Next' and standard depth map will be loaded");
    }

    connect(ui->refresh, SIGNAL(pressed()), this, SLOT(refresh()));
    connect(ui->setup, SIGNAL(pressed()), this, SLOT(setup()));
    connect(ui->exit, SIGNAL(pressed()), this, SLOT(quit()));

    ui->refresh->setAutoDefault(false);
    ui->setup->setAutoDefault(false);
    ui->next->setAutoDefault(false);
    ui->exit->setAutoDefault(false);

}

SensorCalibration::~SensorCalibration()
{
    delete ui;
}

void SensorCalibration::quit()
{
    exit(0);
}

void SensorCalibration::setCropping()
{
    qDebug() << "Cropping is set";

    if (crop->isAreaSelected)
    {
        offsetLeft = crop->offsetLeft;
        offsetRight = crop->offsetRight;
        offsetTop = crop->offsetTop;
        offsetBottom = crop->offsetBottom;
    }
    isCroppingSetUp = true;

    GlobalSettings::getInstance()->setOffsetLeft(offsetLeft);
    GlobalSettings::getInstance()->setOffsetRight(offsetRight);
    GlobalSettings::getInstance()->setOffsetTop(offsetTop);
    GlobalSettings::getInstance()->setOffsetBottom(offsetBottom);

    sensorStream->Terminate();

    GlobalSettings::getInstance()->setSensorMode(true);
    GlobalSettings::getInstance()->setFirstTime(false);

    QMessageBox* box = new QMessageBox(this);
    box->setWindowTitle("Finish");
    box->setText("Sensor is set up!");
    box->show();
}



void SensorCalibration::createSandbox()
{
    if (!isSandboxCreated)
    {
        sandbox = new Sandbox(this);
        sandbox->show();
        this->setVisible(false);
        qDebug() << "sandbox is created";
        isSandboxCreated = true;
    }
}

void SensorCalibration::refresh()
{
    if (!isConnected)
    {
        isConnected = InputStream::isSensorConnected();

        if (isConnected)
        {
            QPalette palette = ui->isFound->palette();
            ui->isFound->setText("Depth sensor is found and successfully initialized");
            palette.setColor(ui->isFound->foregroundRole(), Qt::darkGreen);
            ui->isFound->setPalette(palette);
            ui->option->setVisible(true);
            ui->option->setText("Now you can click 'Set up' to adjust sensor settings\n or you can click 'Next' to skip this step and continue with defaults");
            ui->setup->setVisible(true);
            GlobalSettings::getInstance()->setSensorMode(true);

            sensorType = GlobalSettings::getInstance()->getSensorType();

            if (sensorType == 1)
            {
                ui->sensorType->setText("Sensor type : Kinect v2");
                GlobalSettings::getInstance()->setWidth(512);
                GlobalSettings::getInstance()->setHeight(424);
                GlobalSettings::getInstance()->setSensorType(sensorType);

            }

            else if (sensorType == 0)
            {
                ui->sensorType->setText("Sensor type : Kinect v1");
                GlobalSettings::getInstance()->setWidth(640);
                GlobalSettings::getInstance()->setHeight(480);
                GlobalSettings::getInstance()->setSensorType(sensorType);
            }
        }
    }
}

void SensorCalibration::setup()
{
    if (GlobalSettings::getInstance()->getSensorType() == 1)
    {
        crop->setX(230);
        crop->setY(80);
    }

    else
    {
        crop->setX(190);
        crop->setY(80);
    }
    crop->setHeight(GlobalSettings::getInstance()->getHeight());
    crop->setWidth(GlobalSettings::getInstance()->getWidth());
    sensorStream = new InputStream(GlobalSettings::getInstance()->getWidth(), GlobalSettings::getInstance()->getHeight(),0,10000);

    crop->setDepthMap(sensorStream->getRawMat());

    crop->setup();

    crop->show();
}
