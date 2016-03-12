#include "sandbox.h"
#include "ui_sandbox.h"
#include <QDebug>
#include <QFileDialog>
#include <QColorDialog>


Sandbox::Sandbox(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Sandbox)
{
    ui->setupUi(this);

    renderTimer = new QTimer(this);

    connect(renderTimer, SIGNAL(timeout()), this, SLOT(renderSlot()));

    connect(ui->start, SIGNAL(pressed()), this, SLOT(start()));
    connect(ui->exit, SIGNAL(pressed()), this, SLOT(quit()));
    connect(ui->mode, SIGNAL(pressed()), this, SLOT(mode()));
    connect(ui->settings, SIGNAL(pressed()), this, SLOT(openSettings()));

    renderTimer->start(0);

    ui->start->setAutoDefault(false);
    ui->mode->setAutoDefault(false);
    ui->exit->setAutoDefault(false);
    ui->settings->setAutoDefault(false);

    inGameMode = false;

    settings = new Settings(this);
    this->resize(GlobalSettings::getInstance()->getScreenWidth(), GlobalSettings::getInstance()->getScreenHeight());
    ui->widget->resize(GlobalSettings::getInstance()->getScreenWidth(), GlobalSettings::getInstance()->getScreenHeight());
    ui->exit->move(this->width() * 0.1, this->height() * 0.9);
    ui->settings->move(this->width() * 0.35, this->height() * 0.8);
    ui->mode->move(this->width() * 0.45, this->height() * 0.8);
    ui->start->move(this->width() * 0.5, this->height() * 0.8);

    isRolledUp = false;

    showFullScreen();

    //Add resize according to window screen
}

Sandbox::~Sandbox()
{
    delete ui;
}

void Sandbox::quit()
{
    exit(0);
}

void Sandbox::openSettings()
{
    settings->raise();
    settings->setFocus();
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
    if (!Scene::getInstance()->terrain->isSandboxMode())
        Scene::getInstance()->terrain->setSandboxMode();

    Scene::getInstance()->setWindowSize(GlobalSettings::getInstance()->getScreenWidth(), GlobalSettings::getInstance()->getScreenHeight());
    Scene::getInstance()->camera->setWindowSize(GlobalSettings::getInstance()->getScreenWidth(), GlobalSettings::getInstance()->getScreenHeight());
    ui->widget->resize(GlobalSettings::getInstance()->getScreenWidth(), GlobalSettings::getInstance()->getScreenHeight());

    showFullScreen();

    inGameMode = true;
}

void Sandbox::renderSlot()
{
    ui->widget->repaint();
}

void Sandbox::keyPressEvent(QKeyEvent *event)
{
    Scene::getInstance() -> OnKeyboard(event);
    int keyInt = event->key();
    Qt::Key key = static_cast<Qt::Key>(keyInt);
    if (key == Qt::Key_Escape)
    {
        if (inGameMode)
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
            inGameMode = false;
        }

        else
        {
            exit(0);
        }
    }

    if (key == Qt::Key_F11)
    {
        if (!isRolledUp)
        {

            showNormal();
            this->resize(this->width() / 2, this->height() / 2);
            ui->widget->resize(this->width(), this->height());
            ui->widget->move(this->x(), this->y());
            Scene::getInstance()->setWindowSize(this->width(), this->height());
            Scene::getInstance()->camera->setWindowSize(this->width(),this->height());

            ui->exit->move(this->width() * 0.1, this->height() * 0.8);
            ui->settings->move(this->width() * 0.3, this->height() * 0.6);
            ui->mode->move(this->width() * 0.45, this->height() * 0.6);
            ui->start->move(this->width() * 0.5, this->height() * 0.6);

            isRolledUp = true;

            ui->start->hide();

        }

        else
        {
            showFullScreen();
            this->resize(GlobalSettings::getInstance()->getScreenWidth(), GlobalSettings::getInstance()->getScreenHeight());
            Scene::getInstance()->setWindowSize(GlobalSettings::getInstance()->getScreenWidth(), GlobalSettings::getInstance()->getScreenHeight());
            Scene::getInstance()->camera->setWindowSize(GlobalSettings::getInstance()->getScreenWidth(), GlobalSettings::getInstance()->getScreenHeight());
            ui->widget->resize(GlobalSettings::getInstance()->getScreenWidth(), GlobalSettings::getInstance()->getScreenHeight());
            ui->widget->move(0, 0);
            ui->start->setVisible(true);
            ui->exit->move(this->width() * 0.1, this->height() * 0.9);
            ui->settings->move(this->width() * 0.35, this->height() * 0.8);
            ui->mode->move(this->width() * 0.45, this->height() * 0.8);
            ui->start->move(this->width() * 0.5, this->height() * 0.8);
            isRolledUp = false;


        }



    }
}




