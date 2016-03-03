#include "sandbox.h"
#include "ui_sandbox.h"
#include <QDebug>

Sandbox::Sandbox(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Sandbox)
{
    ui->setupUi(this);

    settings = new Settings(this);

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
    }
}




