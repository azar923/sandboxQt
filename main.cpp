#include "sandbox.h"
#include <QApplication>
#include <QFile>
#include "sensorcalibration.h"
#include "crop.h"
#include "globalsettings.h"
#include <QDesktopWidget>
#include <QMessageBox>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SensorCalibration* s;
    Sandbox* w;

    GlobalSettings::getInstance()->setConfigFile("/home/maxim/SandboxQt/config.txt");

    int screenWidth = a.desktop()->screenGeometry().width();
    int screenHeight = a.desktop()->screenGeometry().height();
    GlobalSettings::getInstance()->setScreenWidth(screenWidth);
    GlobalSettings::getInstance()->setScreenHeight(screenHeight);

    bool firstTime = GlobalSettings::getInstance()->getFirstTime();
    bool isSensorConnected = InputStream::isSensorConnected();

    if (firstTime && isSensorConnected)
    {
        s = new SensorCalibration;
      //  GlobalSettings::getInstance()->setFirstTime(false);
        GlobalSettings::getInstance()->setSensorMode(true);
        s->show();
    }

    else if (isSensorConnected)
    {
        GlobalSettings::getInstance()->setSensorMode(true);
        w = new Sandbox;
        w -> show();
    }

    else if (!isSensorConnected)
    {
        w = new Sandbox;
        w -> show();
    }

    return a.exec();
}
