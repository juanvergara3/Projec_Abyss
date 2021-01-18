#include "mainwindow.h"
#include "mainmenu.h"
#include "pausemenu.h" //termporary

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainMenu m;
    PauseMenu p;
    MainWindow w;

    w.setPause_menu(&p);
    p.setMain_window(&w);

    w.showMaximized();
    return a.exec();
}
