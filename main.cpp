#include "sandbox.h"
#include <QApplication>

#include "dialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Sandbox w;
    w.show();
    return a.exec();
}
