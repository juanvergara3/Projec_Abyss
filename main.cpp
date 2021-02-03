#include "mainwindow.h"
#include "mainmenu.h"
#include "pausemenu.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainMenu m;

    m.showMaximized();

    return a.exec();
}
