#ifndef SANDBOX_H
#define SANDBOX_H

#include <QMainWindow>
#include <QTimer>
#include <QColorDialog>
#include "settings.h"


namespace Ui {
class Sandbox;
}

class Sandbox : public QMainWindow
{
    Q_OBJECT

public:
    explicit Sandbox(QWidget *parent = 0);
    ~Sandbox();
    void keyPressEvent(QKeyEvent* event); Q_DECL_OVERRIDE

private:
    Ui::Sandbox *ui;
    QTimer* renderTimer;
    QCursor* c;
    Settings* settings;

private slots:
    void renderSlot();
    void quit();
    void start();
    void mode();
    void openSettings();

};

#endif // SANDBOX_H
