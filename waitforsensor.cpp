#include "waitforsensor.h"
#include "ui_waitforsensor.h"
#include "inputstream.h"
#include "globalsettings.h"

WaitForSensor::WaitForSensor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WaitForSensor)
{
    ui->setupUi(this);
    setWindowTitle("No depth sensor found");

    ui->next->setAutoDefault(false);
    ui->exit->setAutoDefault(false);

    connect(ui->next, SIGNAL(pressed()), this, SLOT(next()));
    connect(ui->exit, SIGNAL(pressed()), this, SLOT(quit()));

    timer = new QTimer(this);

    isSensorFound = false;
    isSandboxCreated = false;

    connect(timer, SIGNAL(timeout()), this, SLOT(checkForSensor()));
    timer->start(1000);
}

WaitForSensor::~WaitForSensor()
{
    delete ui;
}


void WaitForSensor::next()
{
    if (!isSandboxCreated)
    {
        sandbox = new Sandbox(this);
        sandbox->show();
        this->setVisible(false);
        isSandboxCreated = true;
        timer->stop();
    }

}

void WaitForSensor::quit()
{
    exit(0);
}

void WaitForSensor::checkForSensor()
{
    isSensorFound = InputStream::isSensorConnected();

    if (isSensorFound)
    {
        int sensorType = InputStream::getConnectedSensorType();
        GlobalSettings::getInstance()->setSensorType(sensorType);
        QPalette palette = ui->label->palette();
        GlobalSettings::getInstance()->setSensorMode(true);
        palette.setColor(ui->label->foregroundRole(), Qt::darkGreen);
        ui->label->setPalette(palette);
        ui->label->setText("Sensor was found! Click 'Next' to continue");
        timer->stop();
        setWindowTitle("Sensor was found!");

        if (sensorType == 1)
        {
            ui->sensorType->setText("Sensor type : Kinect v2");
        }

        else
        {
            ui->sensorType->setText("Sensor type : Kinect v1");
        }
    }
}
