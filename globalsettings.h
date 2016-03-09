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

    static GlobalSettings* singleton;

    GlobalSettings();



};

#endif // GLOBALSETTINGS_H
