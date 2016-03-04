#include "sensorcalibration.h"
#include "ui_sensorcalibration.h"
#include "sandbox.h"

SensorCalibration::SensorCalibration(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SensorCalibration)
{
    ui->setupUi(this);
    setWindowTitle("Welcome!");
    isConnected = false;

    ui->option->setVisible(false);
    ui->setup->setVisible(false);

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
    }
    else
    {
        palette.setColor(ui->isFound->foregroundRole(), Qt::red);
        ui->isFound->setPalette(palette);
        ui->isFound->setText("There is no depth sensor connected. Connect sensor and click 'Refresh'\n or click 'Next' and standard depth map will be loaded");
    }

    connect(ui->refresh, SIGNAL(pressed()), this, SLOT(refresh()));
    connect(ui->setup, SIGNAL(pressed()), this, SLOT(setup()));
}

SensorCalibration::~SensorCalibration()
{
    delete ui;
}


void SensorCalibration::createSandbox()
{
    sandbox = new Sandbox(this);
    sandbox->show();
    this->setVisible(false);
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
        }
    }
}

void SensorCalibration::setup()
{
    settings = new SensorSettings(this);
    settings->show();
}
