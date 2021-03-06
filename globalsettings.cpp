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
    minHeight = settings.at(9);
    maxHeight = settings.at(10);
    flipHorisontal = settings.at(11);
    flipVertical = settings.at(12);
    waterMax = settings.at(13);
    sandMax = settings.at(14);
    grassMax = settings.at(15);
    stoneMax = settings.at(16);
    lightDirectionX = settings.at(17);
    lightDirectionY = settings.at(18);
    lightDirectionZ = settings.at(19);
    lightColorR = settings.at(20);
    lightColorG = settings.at(21);
    lightColorB = settings.at(22);
    lightIntensity = settings.at(23);
    contrast = settings.at(24);

    sensorMode = false;
    sensorType = -1;
}

bool GlobalSettings::getSensorMode()
{
    return sensorMode;
}

void GlobalSettings::setSensorMode(bool isSensorMode)
{
    sensorMode = isSensorMode;
}

bool GlobalSettings::getFirstTime()
{
    return (bool)firstTime;
}

bool GlobalSettings::getFlipHorisontal()
{
    return (bool)flipHorisontal;
}

bool GlobalSettings::getFlipVertical()
{
    return (bool)flipVertical;
}

int GlobalSettings::getWaterMax()
{
    return waterMax;
}

int GlobalSettings::getGrassMax()
{
    return grassMax;
}

int GlobalSettings::getStoneMax()
{
    return stoneMax;
}

int GlobalSettings::getSandMax()
{
    return sandMax;
}

int GlobalSettings::getLightDirectionX()
{
    return lightDirectionX;
}

int GlobalSettings::getLightDirectionY()
{
    return lightDirectionY;
}

int GlobalSettings::getLightDirectionZ()
{
    return lightDirectionZ;
}

int GlobalSettings::getLightColorR()
{
    return lightColorR;
}

int GlobalSettings::getLightColorG()
{
    return lightColorG;
}

int GlobalSettings::getLightColorB()
{
    return lightColorB;
}

int GlobalSettings::getLightIntensity()
{
    return lightIntensity;
}

int GlobalSettings::getContrast()
{
    return contrast;
}

int GlobalSettings::getSensorType()
{
    return sensorType;
}




void GlobalSettings::writeSpecificAttribute(int numberOfAttribute, QString name, int value)
{
    QFile file(fileName);
    file.open(QIODevice::ReadWrite);
    QTextStream in(&file);

    QFile temp("/home/maxim/SandboxQt/temp.txt");
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

void GlobalSettings::setMinHeight(int _minHeight)
{
    writeSpecificAttribute(9, "minHeight", _minHeight);
    minHeight = _minHeight;
}

void GlobalSettings::setMaxHeight(int _maxHeight)
{
    writeSpecificAttribute(10, "maxHeight", _maxHeight);
    maxHeight = _maxHeight;
}

void GlobalSettings::setHorisontalFlip(bool _horisontalFlip)
{
    writeSpecificAttribute(11, "flipHorisontal", (int)_horisontalFlip);
    flipHorisontal = (int)_horisontalFlip;
}

void GlobalSettings::setVerticalFlip(bool _verticalFlip)
{
    writeSpecificAttribute(12, "flipVertical", (int)_verticalFlip);
    flipVertical = _verticalFlip;
    qDebug() << flipVertical;
}

void GlobalSettings::setWaterMax(int _waterMax)
{
    writeSpecificAttribute(13, "waterMax", _waterMax);
    waterMax = _waterMax;
}

void GlobalSettings::setSandMax(int _sandMax)
{
    writeSpecificAttribute(14, "sandMax", _sandMax);
    sandMax = _sandMax;
}

void GlobalSettings::setGrassMax(int _grassMax)
{
    writeSpecificAttribute(15, "grassMax", _grassMax);
    grassMax = _grassMax;
}

void GlobalSettings::setStoneMax(int _stoneMax)
{
    writeSpecificAttribute(16, "stoneMax", _stoneMax);
    stoneMax = _stoneMax;
}

void GlobalSettings::setLightDirectionX(int _directionX)
{
    writeSpecificAttribute(17, "lightDirectionX", _directionX);
    lightDirectionX = _directionX;
}

void GlobalSettings::setLightDirectionY(int _directionY)
{
    writeSpecificAttribute(18, "lightDirectionY", _directionY);
    lightDirectionY = _directionY;
}

void GlobalSettings::setLightDirectionZ(int _directionZ)
{
    writeSpecificAttribute(19, "lightDirectionZ", _directionZ);
    lightDirectionZ = _directionZ;
}

void GlobalSettings::setLightColorR(int _lightColorR)
{
    writeSpecificAttribute(20, "lightColorR", _lightColorR);
    lightColorR = _lightColorR;
}

void GlobalSettings::setLightColorG(int _lightColorG)
{
    writeSpecificAttribute(21, "lightColorG", _lightColorG);
    lightColorG = _lightColorG;
}

void GlobalSettings::setLightColorB(int _lightColorB)
{
    writeSpecificAttribute(22, "lightColorB", _lightColorB);
    lightColorB = _lightColorB;
}

void GlobalSettings::setLightIntensity(int _lightIntensity)
{
    writeSpecificAttribute(23, "lightIntensity", _lightIntensity);
    lightIntensity = _lightIntensity;
}

void GlobalSettings::setContrast(int _contrast)
{
    writeSpecificAttribute(24, "contrast", _contrast);
    contrast = _contrast;
}

void GlobalSettings::setSensorType(int _sensorType)
{
    sensorType = _sensorType;
}


int GlobalSettings::getMinHeight()
{
    return minHeight;
}

int GlobalSettings::getMaxHeight()
{
    return maxHeight;
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


