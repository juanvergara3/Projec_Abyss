#include "pausemenu.h"
#include "ui_pausemenu.h"
#include "mainwindow.h"
#include "mainmenu.h"

PauseMenu::PauseMenu(QWidget *parent, MainWindow *m) :
    QMainWindow(parent), ui(new Ui::PauseMenu), main_window(m), main_menu(nullptr)
{
    ui->setupUi(this);

    init_lists();

    hide_resetScreen();
    hide_menuScreen();

    current_screen = "main";
}
PauseMenu::~PauseMenu() {

    //this->close();

    main_menu = nullptr;
    main_window = nullptr;
    delete ui;
}

void PauseMenu::init_lists() {

    // the pause window is divided on 3 "screens" that are represented by QLists

    mainScreen.push_back(ui->pausedLabel);
    mainScreen.push_back(ui->resumeButton);
    mainScreen.push_back(ui->saveButton);
    mainScreen.push_back(ui->restartButton);
    mainScreen.push_back(ui->exitButton);

    resetScreen.push_back(ui->resLabel);
    resetScreen.push_back(ui->yesButton_res);
    resetScreen.push_back(ui->noButton_res);

    menuScreen.push_back(ui->menLabel);
    menuScreen.push_back(ui->yesButton_men);
    menuScreen.push_back(ui->noButton_men);
}

void PauseMenu::hide_mainScreen() {
    for(int k=0; k!=mainScreen.size(); k++)
        mainScreen.at(k)->setHidden(true);
}
void PauseMenu::hide_resetScreen() {
    for(int k=0; k!=resetScreen.size(); k++)
        resetScreen.at(k)->setHidden(true);
}
void PauseMenu::hide_menuScreen() {
    for(int k=0; k!=menuScreen.size(); k++)
        menuScreen.at(k)->setHidden(true);
}

void PauseMenu::show_mainScreen() {
    for(int k=0; k!=mainScreen.size(); k++)
        mainScreen.at(k)->setHidden(false);
}
void PauseMenu::show_resetScreen() {
    for(int k=0; k!=resetScreen.size(); k++)
        resetScreen.at(k)->setHidden(false);
}
void PauseMenu::show_menuScreen() {
    for(int k=0; k!=menuScreen.size(); k++)
        menuScreen.at(k)->setHidden(false);
}

void PauseMenu::on_resumeButton_clicked() { // on main screen
    //takes you back to the game

    this->close();
    main_window->showMaximized();
    main_window->resume();
}
void PauseMenu::on_saveButton_clicked() {

    //saves your game

    main_window->getGame()->setCurrent_room(main_window->getCurrent_room());
    main_window->getGame()->setCurrent_floor(main_window->getCurrent_floor());

    std::string filename = QFileDialog::getSaveFileName(this, "Save", "", "Text file (*.txt)").toStdString();

    if(!filename.empty())
        main_window->getGame()->save_game(filename);

}
void PauseMenu::on_restartButton_clicked() {

    // takes you to the "reset screen"

    hide_mainScreen();
    show_resetScreen();

    current_screen = "restart";
}
void PauseMenu::on_exitButton_clicked() {

    // takes you to the "menu screen"

    hide_mainScreen();
    show_menuScreen();

    current_screen = "exit";
}

void PauseMenu::on_noButton_res_clicked() { // on reset screen

    // takes you back to the "main screen"

    hide_resetScreen();
    show_mainScreen();

    current_screen = "main";
}
void PauseMenu::on_yesButton_res_clicked() {

    // resets your game and resumes it

    hide_resetScreen();
    show_mainScreen();

    this->close();

    main_window->showMaximized();
    main_window->reset_game();
}

void PauseMenu::on_noButton_men_clicked() { // on menu screen

    // takes you back to the "main screen"

    hide_menuScreen();
    show_mainScreen();

    current_screen = "main";
}
void PauseMenu::on_yesButton_men_clicked() {

    // closes your game and takes you to the main menu

    hide_menuScreen();
    show_mainScreen();

    this->close();
    main_window->close_game();
    main_window->close();

    main_menu->showMaximized();
}

void PauseMenu::setMain_window(MainWindow *value) {
    main_window = value;
}
void PauseMenu::setMain_menu(MainMenu *value) {
    main_menu = value;
}
void PauseMenu::keyPressEvent(QKeyEvent *event) {

    // pressing esc or back space makes you go back. pressing enter while on the reset or menu screens counts as if you clicked yes

    if(event->key() == Qt::Key_Escape){
        if(current_screen == "main"){
            //this->hide();
            this->close();
            main_window->showMaximized();
            main_window->resume();
        }
        else if (current_screen == "restart") {
            on_noButton_res_clicked();
        }
        else if (current_screen == "exit") {
            on_noButton_men_clicked();
        }
    }
    else if(event->key() == Qt::Key_Backspace){
        if(current_screen == "main"){
            //this->hide();
            this->close();
            main_window->showMaximized();
            main_window->resume();
        }
        else if (current_screen == "restart") {
            on_noButton_res_clicked();
        }
        else if (current_screen == "exit") {
            on_noButton_men_clicked();
        }
    }
    else if (event->key() == Qt::Key_Enter) {
        if (current_screen == "restart") {
            on_yesButton_res_clicked();
        }
        else if (current_screen == "exit") {
            on_yesButton_men_clicked();
        }
    }
}

