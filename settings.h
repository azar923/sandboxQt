#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include "scene.h"
#include <QFileDialog>

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();

private:
    Ui::Settings *ui;
    QFileDialog* d;

private slots:

    void setLightDirectionX(int);
    void setLightDirectionY(int);
    void setLightDirectionZ(int);
    void setLightColorR(int);
    void setLightColorG(int);
    void setLightColorB(int);
    void setLightDiffuseIntensity(int);
    void setKinectMinHeight(int);
    void setKinectMaxHeight(int);
    void setContrast(int);
    void setHorisontalFlip(int);
    void setVerticalFlip(int);
    void setWaterTexture();
    void setSandTexture();
    void setGrassTexture();
    void setStoneTexture();
    void setSnowTexture();
    void changeTerrain(int);

    void setResolution(int);

    void setWaterMax(int);

    void setSandMax(int);

    void setGrassMax(int);

    void setStoneMax(int);

};

#endif // SETTINGS_H
