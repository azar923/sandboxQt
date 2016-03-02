#ifndef SANDBOX_H
#define SANDBOX_H

#include <QMainWindow>

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
};

#endif // SANDBOX_H
