#ifndef SENSORSETTINGS_H
#define SENSORSETTINGS_H

#include <QDialog>
#include <QRubberBand>

#include <QMouseEvent>
#include <QPainter>
#include "crop.h"

#include "inputstream.h"
#include "globalsettings.h"

namespace Ui {
class SensorSettings;
}

class SensorSettings : public QDialog
{
    Q_OBJECT

public:
    explicit SensorSettings(QWidget *parent = 0);
    ~SensorSettings();

private:
    Ui::SensorSettings *ui;
    bool isResolutionSetUp;
    bool isCroppingSetUp;
    int width;
    int height;

    int x;
    int y;


    Crop* crop;

    int offsetLeft;
    int offsetRight;
    int offsetTop;
    int offsetBottom;

    InputStream* sensorStream;


public slots:
    void next();
    void setResolution(int);
    void setCropping();
};

#endif // SENSORSETTINGS_H
