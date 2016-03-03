#include "sandbox.h"
#include <QApplication>
#include <QFile>
#include "sensorcalibration.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SensorCalibration* s;
    Sandbox* w;

    QFile file("/home/maxim/Sandbox_Qt/config.txt");

    file.open(QIODevice::ReadWrite);
    QTextStream in(&file);

    QString string = in.readLine(50);
    QStringList values = string.split("=");
    qDebug() << values.at(1).toInt();
    if (values.at(1).toInt() == 0)
    {
        s = new SensorCalibration;
        s->show();
    }

    else
    {
        w = new Sandbox;
        w -> show();
    }


    return a.exec();
}
