#include "sensorsettings.h"
#include "ui_sensorsettings.h"

SensorSettings::SensorSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SensorSettings)
{
    ui->setupUi(this);

    ui->pushButton->hide();

    setWindowTitle("Sensor settings");

    connect(ui->cancel, SIGNAL(pressed()), this, SLOT(close()));
    connect(ui->next, SIGNAL(pressed()), this, SLOT(next()));
    connect(ui->pushButton, SIGNAL(pressed()), this, SLOT(close()));

    isCroppingSetUp = false;
}

SensorSettings::~SensorSettings()
{
    delete ui;
}

void SensorSettings::next()
{
    if (!isCroppingSetUp)
    {
        ui->comboBox->hide();
        ui->label->setText("Plese, set sensor cropping");
        isCroppingSetUp = true;
    }

    else
    {
        ui->label->setText("Sensor is set up! ");
        ui->next->hide();
        ui->cancel->hide();
        ui->pushButton->setVisible(true);
    }
}
