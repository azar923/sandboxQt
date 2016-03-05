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
    void setFirstTime(bool isFirstTime);
    void setWidth(int _width);
    void setHeight(int _height);
    void setOffsetLeft(int _offsetLeft);
    void setOffsetRight(int _offsetRight);
    void setOffsetTop(int _offsetTop);
    void setOffsetBottom(int _offsetBottom);
    void setScreenWidth(int _screenWidth);
    void setScreenHeight(int _screenHeight);

    static GlobalSettings* getInstance() {
        if (singleton == 0)
            singleton = new GlobalSettings;
        return singleton;
    }

private:

    void writeSpecificAttribute(int numberOfAttribute, QString name, int value);
    QString fileName;
    int firstTime;
    int width;
    int height;
    int offsetLeft;
    int offsetRight;
    int offsetTop;
    int offsetBottom;
    int screenWidth;
    int screenHeight;

    static GlobalSettings* singleton;

    GlobalSettings();



};

#endif // GLOBALSETTINGS_H
