#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include "scene.h"

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

private slots:

    void setLightDirectionX(int);
    void setLightDirectionY(int);
    void setLightDirectionZ(int);
    void setLightColorR(int);
    void setLightColorG(int);
    void setLightColorB(int);
    void setLightAmbientIntensity(int);
    void setLightDiffuseIntensity(int);
    void setKinectMinHeight(int);
    void setKinectMaxHeight(int);
    void setContrast(int);
    void setFlip(int);

};

#endif // SETTINGS_H
