#ifndef SENSORSETTINGS_H
#define SENSORSETTINGS_H

#include <QDialog>

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

public slots:
    void next();
};

#endif // SENSORSETTINGS_H
