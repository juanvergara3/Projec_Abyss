#include "mainwindow.h"
#include "mainmenu.h"
#include "pausemenu.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainMenu m;
    //PauseMenu p;
    //MainWindow w;

    //m.setMainwindow(&w);
    //m.setPausemenu(&p);
    //w.setPause_menu(&p);
   //w.setMain_menu(&m);
    //p.setMain_window(&w);
    //p.setMain_menu(&m);

    m.showMaximized();
    //w.close();
    //p.close();

    return a.exec();
}
