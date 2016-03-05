#include "globalsettings.h"
#include <QDebug>
#include <QFile>
#include <QVector>
GlobalSettings* GlobalSettings::singleton = 0;

GlobalSettings::GlobalSettings()
{

}

void GlobalSettings::setConfigFile(const QString filePath)
{
    fileName = filePath;
    qDebug() << fileName;


    QFile file(filePath);

    file.open(QIODevice::ReadWrite);
    QTextStream in(&file);

    QVector<int> settings;

    while(!in.atEnd())
    {
        QString string = in.readLine(100);
        QStringList values = string.split("=");
        settings.push_back(values.at(1).toInt());
    }

    file.close();

    firstTime = settings.at(0);
    width = settings.at(1);
    height = settings.at(2);
    offsetLeft = settings.at(3);
    offsetRight = settings.at(4);
    offsetTop = settings.at(5);
    offsetBottom = settings.at(6);
    screenWidth = settings.at(7);
    screenHeight = settings.at(8);
}

bool GlobalSettings::getFirstTime()
{
    return (bool)firstTime;
}

void GlobalSettings::writeSpecificAttribute(int numberOfAttribute, QString name, int value)
{
    QFile file(fileName);
    file.open(QIODevice::ReadWrite);
    QTextStream in(&file);

    QFile temp("/home/maxim/Sandbox_Qt/temp.txt");
    temp.open(QIODevice::ReadWrite | QIODevice::Truncate);
    QTextStream temp_in(&temp);

    int i = 0;

    while (!in.atEnd())
    {
        QString s = in.readLine(100);
        if (i != numberOfAttribute)
            temp_in << s << "\n";
        else
        {
            temp_in << name;
            temp_in << "=";
            temp_in << QString::number(value);
            temp_in << "\n";
        }

        i++;
    }

    file.close();
    temp.close();

    file.remove();
    temp.rename(fileName);
}

void GlobalSettings::setFirstTime(bool isFirstTime)
{
    writeSpecificAttribute(0, "firstTime", (int)isFirstTime);
    firstTime = (int)isFirstTime;

}

void GlobalSettings::setWidth(int _width)
{
    writeSpecificAttribute(1, "width", _width);
    width = _width;
}

void GlobalSettings::setHeight(int _height)
{
    writeSpecificAttribute(2, "height", _height);
    height = _height;
}

void GlobalSettings::setOffsetLeft(int _offsetLeft)
{
    writeSpecificAttribute(3, "offsetLeft", _offsetLeft);
    offsetLeft = _offsetLeft;
}

void GlobalSettings::setOffsetRight(int _offsetRight)
{
    writeSpecificAttribute(4, "offsetRight", _offsetRight);
    offsetRight = _offsetRight;
}

void GlobalSettings::setOffsetTop(int _offsetTop)
{
    writeSpecificAttribute(5, "offsetTop", _offsetTop);
    offsetTop = _offsetTop;
}

void GlobalSettings::setOffsetBottom(int _offsetBottom)
{
    writeSpecificAttribute(6, "offsetBottom", _offsetBottom);
    offsetBottom = _offsetBottom;
}

void GlobalSettings::setScreenWidth(int _screenWidth)
{
    writeSpecificAttribute(7, "screenWidth", _screenWidth);
    screenWidth = _screenWidth;
}

void GlobalSettings::setScreenHeight(int _screenHeight)
{
    writeSpecificAttribute(8, "screenHeight", _screenHeight);
    screenHeight = _screenHeight;
}

int GlobalSettings::getScreenHeight()
{
    return screenHeight;
}

int GlobalSettings::getScreenWidth()
{
    return screenWidth;
}

int GlobalSettings::getWidth()
{
    return width;
}

int GlobalSettings::getHeight()
{
    return height;
}

int GlobalSettings::getOffsetLeft()
{
    return offsetLeft;
}

int GlobalSettings::getOffsetRight()
{
    return offsetRight;
}

int GlobalSettings::getOffsetTop()
{
    return offsetTop;
}

int GlobalSettings::getOffsetBottom()
{
    return offsetBottom;
}


