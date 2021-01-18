#include "pausemenu.h"
#include "ui_pausemenu.h"

PauseMenu::PauseMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PauseMenu)
{
    ui->setupUi(this);

    init_lists();

    hide_resetScreen();
    hide_menuScreen();
}
PauseMenu::~PauseMenu() {
    delete ui;
}

void PauseMenu::init_lists() {
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

}
void PauseMenu::on_saveButton_clicked() {

}
void PauseMenu::on_restartButton_clicked() {
    hide_mainScreen();
    show_resetScreen();
}
void PauseMenu::on_exitButton_clicked() {
    hide_mainScreen();
    show_menuScreen();
}

void PauseMenu::on_noButton_res_clicked() { // on reset screen
    hide_resetScreen();
    show_mainScreen();
}
void PauseMenu::on_yesButton_res_clicked() {

}

void PauseMenu::on_noButton_men_clicked() { // on menu screen
    hide_menuScreen();
    show_mainScreen();
}
void PauseMenu::on_yesButton_men_clicked() {

}
