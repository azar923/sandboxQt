#include "sensorcalibration.h"
#include "ui_sensorcalibration.h"
#include "sandbox.h"

SensorCalibration::SensorCalibration(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SensorCalibration)
{
    ui->setupUi(this);
    setWindowTitle("Welcome!");

    connect(ui->next, SIGNAL(pressed()), this, SLOT(createSandbox()));
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
