#ifndef GLOBALSETTINGS_H
#define GLOBALSETTINGS_H

#include <QString>

class GlobalSettings
{
public:

    void setConfigFile(const QString filePath);
    bool getFirstTime();
    int getWidth();
    int getHeight();
    int getOffsetLeft();
    int getOffsetRight();
    int getOffsetTop();
    int getOffsetBottom();
    int getScreenWidth();
    int getScreenHeight();
    int getMaxHeight();
    int getMinHeight();
    bool getFlipHorisontal();
    bool getFlipVertical();
    int getWaterMax();
    int getSandMax();
    int getGrassMax();
    int getStoneMax();
    int getLightDirectionX();
    int getLightDirectionY();
    int getLightDirectionZ();
    int getLightColorR();
    int getLightColorG();
    int getLightColorB();
    int getLightIntensity();
    bool getSensorMode();

    void setFirstTime(bool isFirstTime);
    void setWidth(int _width);
    void setHeight(int _height);
    void setOffsetLeft(int _offsetLeft);
    void setOffsetRight(int _offsetRight);
    void setOffsetTop(int _offsetTop);
    void setOffsetBottom(int _offsetBottom);
    void setScreenWidth(int _screenWidth);
    void setScreenHeight(int _screenHeight);
    void setMinHeight(int _minHeight);
    void setMaxHeight(int _maxHeight);
    void setVerticalFlip(bool _verticalFlip);
    void setHorisontalFlip(bool _horisontalFlip);
    void setWaterMax(int _waterMax);
    void setSandMax(int _sandMax);
    void setGrassMax(int _grassMax);
    void setStoneMax(int _stoneMax);
    void setLightDirectionX(int _directionX);
    void setLightDirectionY(int _directionY);
    void setLightDirectionZ(int _directionZ);
    void setLightColorR(int _lightColorR);
    void setLightColorG(int _lightColorG);
    void setLightColorB(int _lightColorB);
    void setLightIntensity(int _lightIntensity);
    void setSensorMode(bool isSensorMode);

    static GlobalSettings* getInstance() {
        if (singleton == 0)
            singleton = new GlobalSettings;
        return singleton;
    }

private:

    void writeSpecificAttribute(int numberOfAttribute, QString name, int value);
    QString fileName;
    int firstTime;  // 0
    int width;      // 1
    int height;     // 2
    int offsetLeft; // 3
    int offsetRight;// 4
    int offsetTop;  // 5
    int offsetBottom; // 6
    int screenWidth;  // 7
    int screenHeight; // 8
    int minHeight; // 9
    int maxHeight; // 10
    int flipHorisontal; //11
    int flipVertical;  //12
    int waterMax; //13
    int sandMax; //14
    int grassMax; //15
    int stoneMax; //16
    int lightDirectionX; //17
    int lightDirectionY; //18
    int lightDirectionZ;//19
    int lightColorR;//20
    int lightColorG;//21
    int lightColorB;//22
    int lightIntensity;//23

    bool sensorMode;

    static GlobalSettings* singleton;

    GlobalSettings();



};

#endif // GLOBALSETTINGS_H
