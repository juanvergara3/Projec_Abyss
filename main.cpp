#include "mainwindow.h"
#include "mainmenu.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainMenu w;
    w.showMaximized();
    w.show();
    return a.exec();
}
