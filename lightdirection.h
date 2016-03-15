#ifndef LIGHTDIRECTION_H
#define LIGHTDIRECTION_H

#include <QDialog>
#include <QPainter>

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
    void paintEvent(QPaintEvent* event);
    bool toDraw;
    bool firstOpen;

    QPoint lightPos;

    QImage* light;

private:
    Ui::LightDirection *ui;


};

#endif // LIGHTDIRECTION_H
