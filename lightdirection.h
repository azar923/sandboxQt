#ifndef LIGHTDIRECTION_H
#define LIGHTDIRECTION_H

#include <QDialog>

namespace Ui {
class LightDirection;
}

class LightDirection : public QDialog
{
    Q_OBJECT

public:
    explicit LightDirection(QWidget *parent = 0);
    ~LightDirection();
    void setPixmap();
    void mousePressEvent(QMouseEvent *event);

private:
    Ui::LightDirection *ui;
};

#endif // LIGHTDIRECTION_H
