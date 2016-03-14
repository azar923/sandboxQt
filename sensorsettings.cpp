#include "sensorsettings.h"
#include "ui_sensorsettings.h"
#include <QDebug>

SensorSettings::SensorSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SensorSettings)
{
    ui->setupUi(this);

    ui->finish->hide();

    setWindowTitle("Sensor settings");

    width = GlobalSettings::getInstance()->getWidth();
    height = GlobalSettings::getInstance()->getHeight();

    if (width == 320)
    {
        x = 310;
        y = 220;
    }

    else
    {
        x = 190;
        y = 80;
    }

    connect(ui->cancel, SIGNAL(pressed()), this, SLOT(close()));
    connect(ui->next, SIGNAL(pressed()), this, SLOT(next()));
    connect(ui->finish, SIGNAL(pressed()), this, SLOT(close()));

    connect(ui->resolution, SIGNAL(currentIndexChanged(int)), this, SLOT(setResolution(int)));

    isCroppingSetUp = false;

    crop = new Crop(this);

    connect(this->crop, SIGNAL(croppingFinished()), this, SLOT(setCropping()));

    connect(this->crop, SIGNAL(croppingClosed()), this, SLOT(quit()));

    offsetLeft = 0;
    offsetRight = 0;
    offsetTop = 0;
    offsetBottom = 0;


    ui->cancel->setAutoDefault(false);
    ui->finish->setAutoDefault(false);
    ui->next->setAutoDefault(false);
}

void SensorSettings::quit()
{
    qDebug() << "we are here";
}

void SensorSettings::setCropping()
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

    ui->resolution->hide();

    ui->label->setText("Sensor is set up! ");
    ui->next->hide();
    ui->cancel->hide();

    ui->finish->setVisible(true);
    GlobalSettings::getInstance()->setSensorMode(true);

}

SensorSettings::~SensorSettings()
{
    delete ui;
}

void SensorSettings::next()
{
    if (!isCroppingSetUp)
    {

        crop->setX(x);
        crop->setY(y);
        crop->setHeight(height);
        crop->setWidth(width);
        sensorStream = new InputStream(width, height,0,10000);

        crop->setDepthMap(sensorStream->getRawMat());
        crop->setup();

        crop->show();
    }
}


void SensorSettings::setResolution(int option)
{
    if (option == 1)
    {
        width = 640;
        height = 480;
        x = 190;
        y = 80;

        GlobalSettings::getInstance()->setWidth(width);
        GlobalSettings::getInstance()->setHeight(height);

        qDebug() << "res = 640";
    }

  /*  else
    {
        width = 320;
        height = 240;
        x = 310;
        y = 220;

        qDebug() << "res = 320";

        GlobalSettings::getInstance()->setWidth(width);
        GlobalSettings::getInstance()->setHeight(height);
    }*/
}
