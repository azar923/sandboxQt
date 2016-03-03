#include "sandbox.h"
#include <QApplication>
#include <QColorDialog>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Sandbox w;
    w.show();
    return a.exec();
}
