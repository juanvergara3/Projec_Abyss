#include "messagewindow.h"
#include "ui_messagewindow.h"
#include "mainmenu.h"
#include "mainwindow.h"

MessageWindow::MessageWindow(QWidget *parent, std::string type) :
    QMainWindow(parent), ui(new Ui::MessageWindow)
{  

    // window that says game over or victory, nothing special

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

void MessageWindow::keyPressEvent(QKeyEvent *event) { // if esc or enter are pressed on this screen it counts as if you clicked the continue button
    if(event->key() == Qt::Key_Enter)
        on_continueButton_clicked();
    else if(event->key() == Qt::Key_Escape)
        on_continueButton_clicked();
}

void MessageWindow::on_continueButton_clicked() { // takes you back to the main menu
    this->close();
    main_window->close_game();

    main_menu->showMaximized();
}

void MessageWindow::setMain_menu(MainMenu *value) {
    main_menu = value;
}
void MessageWindow::setMain_window(MainWindow *value) {
    main_window = value;
}
