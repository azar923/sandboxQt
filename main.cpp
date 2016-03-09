#include "sandbox.h"
#include <QApplication>
#include <QFile>
#include "sensorcalibration.h"
#include "crop.h"
#include "globalsettings.h"
#include <QDesktopWidget>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SensorCalibration* s;
    Sandbox* w;

    GlobalSettings::getInstance()->setConfigFile("/home/maxim/Sandbox_Qt/config.txt");

   // int screenWidth = a.desktop()->screenGeometry().width();
   // int screenHeight = a.desktop()->screenGeometry().height();
    //GlobalSettings::getInstance()->setScreenWidth(screenWidth);
  //  GlobalSettings::getInstance()->setScreenHeight(screenHeight);


    bool firstTime = GlobalSettings::getInstance()->getFirstTime();

    qDebug() << "First";

    if (firstTime)
    {
        s = new SensorCalibration;
        //GlobalSettings::getInstance()->setFirstTime(false);

        s->show();
    }

    else
    {
        w = new Sandbox;
        w -> show();
    }

    return a.exec();
}
