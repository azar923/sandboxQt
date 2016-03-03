#ifndef SANDBOX_H
#define SANDBOX_H

#include <QMainWindow>
#include <QTimer>
#include <QColorDialog>

namespace Ui {
class Sandbox;
}

class Sandbox : public QMainWindow
{
    Q_OBJECT

public:
    explicit Sandbox(QWidget *parent = 0);
    ~Sandbox();

private:
    Ui::Sandbox *ui;
    QTimer* renderTimer;
    QColorDialog* lightColorDialog;

private slots:
    void renderSlot();
    void setLightDirectionX(int);
    void setLightDirectionY(int);
    void setLightDirectionZ(int);
    void setLightColorR(int);
    void setLightColorG(int);
    void setLightColorB(int);
    void setKinectMinHeight(int);
    void setKinectMaxHeight(int);
    void quit();
    void start();

};

#endif // SANDBOX_H
