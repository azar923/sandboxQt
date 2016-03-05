#ifndef SENSORCALIBRATION_H
#define SENSORCALIBRATION_H

#include <QDialog>
#include "sandbox.h"
#include "filestream.h"
#include "sensorsettings.h"

namespace Ui {
class SensorCalibration;
}

class SensorCalibration : public QDialog
{
    Q_OBJECT

public:
    explicit SensorCalibration(QWidget *parent = 0);
    ~SensorCalibration();

private:
    Ui::SensorCalibration *ui;

    Sandbox* sandbox;


    bool isConnected;

    SensorSettings* settings;

public slots:
    void createSandbox();
    void refresh();
    void setup();
};

#endif // SENSORCALIBRATION_H
