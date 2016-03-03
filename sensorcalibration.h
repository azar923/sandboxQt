#ifndef SENSORCALIBRATION_H
#define SENSORCALIBRATION_H

#include <QDialog>
#include "sandbox.h"

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

public slots:
    void createSandbox();
};

#endif // SENSORCALIBRATION_H
