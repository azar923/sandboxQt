#include "sandbox.h"
#include "ui_sandbox.h"
#include <QDebug>


Sandbox::Sandbox(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Sandbox)
{
    ui->setupUi(this);

    settings = new Settings(this->ui->widget);

    renderTimer = new QTimer(this);

    connect(renderTimer, SIGNAL(timeout()), this, SLOT(renderSlot()));


    connect(ui->start, SIGNAL(pressed()), this, SLOT(start()));
    connect(ui->exit, SIGNAL(pressed()), this, SLOT(quit()));
    connect(ui->mode, SIGNAL(pressed()), this, SLOT(mode()));
    connect(ui->settings, SIGNAL(pressed()), this, SLOT(openSettings()));


    renderTimer->start(20);

    c = new QCursor();
    c->setPos(mapToGlobal(QPoint(width() / 2, height() / 2)));
    setCursor(*c);

    player = new QMediaPlayer(this);
    player->setMedia(QUrl::fromLocalFile("/home/maxim/Music/dreamers.mp3"));
    player->setVolume(25);
    player->play();
}

Sandbox::~Sandbox()
{
    delete ui;
}

void Sandbox::quit()
{
    close();
}

void Sandbox::openSettings()
{

    settings->show();
    settings->raise();
}

void Sandbox::mode()
{
    Scene::getInstance()->terrain->setSandboxMode();
    if (ui->mode->text() == "3D")
        ui->mode->setText("2D");
    else
        ui->mode->setText("3D");
}

void Sandbox::start()
{
    ui->start->setVisible(false);
    ui->exit->setVisible(false);
    ui->mode->setVisible(false);
    ui->settings->setVisible(false);
    Scene::getInstance()->terrain->setSandboxMode();

    Scene::getInstance()->setWindowSize(GlobalSettings::getInstance()->getScreenWidth(), GlobalSettings::getInstance()->getScreenHeight());
    Scene::getInstance()->camera->setWindowSize(GlobalSettings::getInstance()->getScreenWidth(), GlobalSettings::getInstance()->getScreenHeight());
    ui->widget->resize(GlobalSettings::getInstance()->getScreenWidth(), GlobalSettings::getInstance()->getScreenHeight());

    showFullScreen();
}

void Sandbox::renderSlot()
{
    ui->widget->update();

}

void Sandbox::keyPressEvent(QKeyEvent *event)
{
    Scene::getInstance() -> OnKeyboard(event);
    int keyInt = event->key();
    Qt::Key key = static_cast<Qt::Key>(keyInt);
    if (key == Qt::Key_Escape)
    {
        ui->start->setVisible(true);
        ui->exit->setVisible(true);
        ui->mode->setVisible(true);
        ui->settings->setVisible(true);
        Scene::getInstance()->terrain->setSandboxMode();
        Scene::getInstance()->setWindowSize(this->width(), this->height());
        Scene::getInstance()->camera->setWindowSize(this->width(),this->height());
        ui->widget->resize(this->width(), this->height());
        ui->widget->move(this->x(), this->y());
        showNormal();
    }
}




