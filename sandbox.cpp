#include "sandbox.h"
#include "ui_sandbox.h"
#include "dialog.h"
Sandbox::Sandbox(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Sandbox)
{
    ui->setupUi(this);
}

Sandbox::~Sandbox()
{
    delete ui;
}
