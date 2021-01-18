#include "mainwindow.h"
#include "mainmenu.h"
#include "pausemenu.h" //termporary

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainMenu w;
    PauseMenu w;
    //MainWindow w;
    w.showMaximized();
    w.show();
    return a.exec();
}
