#include "rotoctl_gui.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ROTOCTL_GUI w;
    w.show();
    return a.exec();
}

