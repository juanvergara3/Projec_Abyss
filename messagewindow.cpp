#include "messagewindow.h"
#include "ui_messagewindow.h"
#include "mainmenu.h"
#include "mainwindow.h"

MessageWindow::MessageWindow(QWidget *parent, std::string type) :
    QMainWindow(parent), ui(new Ui::MessageWindow)
{  
    ui->setupUi(this);

    main_menu = nullptr;
    main_window = nullptr;

    if(type == "victory"){
        ui->gameoverLabel->hide();
    }
    else if(type == "gameover"){

        ui->victoryLabel_1->hide();
        ui->victoryLabel_2->hide();
    }

}

MessageWindow::~MessageWindow() {
    delete ui;
}

void MessageWindow::keyPressEvent(QKeyEvent *event) {

}

void MessageWindow::on_continueButton_clicked() {
    this->close();
    main_window->close_game();
    main_window->close();

    main_menu->showMaximized();
}

void MessageWindow::setMain_menu(MainMenu *value) {
    main_menu = value;
}
void MessageWindow::setMain_window(MainWindow *value) {
    main_window = value;
}
