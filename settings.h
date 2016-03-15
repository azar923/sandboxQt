#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include "scene.h"
#include <QFileDialog>
#include <QColorDialog>
#include "lightdirection.h"
#include <QPainter>
#include <QMouseEvent>

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();
 LightDirection* lightDirection;

private:
    Ui::Settings *ui;
    QFileDialog* d;
    QColorDialog* colorDialog;


private slots:


    void setLightDiffuseIntensity(int);
    void setKinectMinHeight(int);
    void setKinectMaxHeight(int);
    void setContrast(int);
    void setHorisontalFlip(bool);
    void setVerticalFlip(bool);
    void setWaterTexture();
    void setSandTexture();
    void setGrassTexture();
    void setStoneTexture();
    void setSnowTexture();
    void changeTerrain(int);
    void changeSkybox(int);

    void setResolution(int);

    void setWaterMax(int);

    void setSandMax(int);

    void setGrassMax(int);

    void setStoneMax(int);

    void resetSettings();

    void setSkyboxLeft();
    void setSkyboxRight();
    void setSkyboxTop();
    void setSkyboxBottom();
    void setSkyboxFront();
    void setSkyboxBack();

    void chooseColor();

    void setDirection();

    void reconfigure();

};

#endif // SETTINGS_H
