#ifndef WAITFORSENSOR_H
#define WAITFORSENSOR_H

#include <QDialog>
#include <QTimer>
#include "sandbox.h"

namespace Ui {
class WaitForSensor;
}

class WaitForSensor : public QDialog
{
    Q_OBJECT

public:
    explicit WaitForSensor(QWidget *parent = 0);
    ~WaitForSensor();

private:
    Ui::WaitForSensor *ui;
    QTimer* timer;
    bool isSensorFound;
    bool isSandboxCreated;
    Sandbox* sandbox;

private slots:
    void quit();
    void next();
    void checkForSensor();
};

#endif // WAITFORSENSOR_H
