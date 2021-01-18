#include "mainmenu.h"
#include "ui_mainmenu.h"

MainMenu::MainMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);

    init_lists();

    hide_playScreen();
    hide_creditsScreen();
    hide_howtoplayScreen();
    hide_singleplayerScreen();
    hide_multiplayerScreen();

}
MainMenu::~MainMenu() {
    delete ui;
}

void MainMenu::init_lists() {

    mainScreen.push_back(ui->creditsButton);
    mainScreen.push_back(ui->exitButton);
    mainScreen.push_back(ui->playButton);
    mainScreen.push_back(ui->howtoplayButton);

    multiplayerScreen.push_back(ui->player1Label);
    multiplayerScreen.push_back(ui->player1Name);
    multiplayerScreen.push_back(ui->player2Label);
    multiplayerScreen.push_back(ui->player2Name);
    multiplayerScreen.push_back(ui->gobackButton_5);
    multiplayerScreen.push_back(ui->playButton_2);

    singleplayerScreen.push_back(ui->gobackButton_4);
    singleplayerScreen.push_back(ui->playButton_single);
    singleplayerScreen.push_back(ui->playerLabel);
    singleplayerScreen.push_back(ui->playerName);

    howtoplayScreen.push_back(ui->directions);
    howtoplayScreen.push_back(ui->gobackButton_2);

    playScreen.push_back(ui->gobackButton_1);
    playScreen.push_back(ui->loadgameButton);
    playScreen.push_back(ui->multiplayerButton);
    playScreen.push_back(ui->singleplayerButton);

    creditsScreen.push_back(ui->credits);
    creditsScreen.push_back(ui->gobackButton_3);
}

void MainMenu::hide_mainScreen() {
    for(int k=0; k!=mainScreen.size(); k++)
        mainScreen.at(k)->setHidden(true);
}
void MainMenu::hide_playScreen() {
    for(int k=0; k!=playScreen.size(); k++)
        playScreen.at(k)->setHidden(true);
}
void MainMenu::hide_creditsScreen() {
    for(int k=0; k!=creditsScreen.size(); k++)
        creditsScreen.at(k)->setHidden(true);
}
void MainMenu::hide_howtoplayScreen() {
    for(int k=0; k!=howtoplayScreen.size(); k++)
        howtoplayScreen.at(k)->setHidden(true);
}
void MainMenu::hide_singleplayerScreen() {
    for(int k=0; k!=singleplayerScreen.size(); k++)
            singleplayerScreen.at(k)->setHidden(true);
}
void MainMenu::hide_multiplayerScreen() {
    for(int k=0; k!=multiplayerScreen.size(); k++)
        multiplayerScreen.at(k)->setHidden(true);
}

void MainMenu::show_mainScreen() {
    for(int k=0; k!=mainScreen.size(); k++)
        mainScreen.at(k)->setHidden(false);
}
void MainMenu::show_playScreen() {
    for(int k=0; k!=playScreen.size(); k++)
        playScreen.at(k)->setHidden(false);
}
void MainMenu::show_creditsScreen() {
    for(int k=0; k!=creditsScreen.size(); k++)
        creditsScreen.at(k)->setHidden(false);
}
void MainMenu::show_howtoplayScreen() {
    for(int k=0; k!=howtoplayScreen.size(); k++)
        howtoplayScreen.at(k)->setHidden(false);
}
void MainMenu::show_singleplayerScreen() {
    for(int k=0; k!=singleplayerScreen.size(); k++)
        singleplayerScreen.at(k)->setHidden(false);
}
void MainMenu::show_multiplayerScreen() {
    for(int k=0; k!=multiplayerScreen.size(); k++)
        multiplayerScreen.at(k)->setHidden(false);
}

void MainMenu::on_playButton_clicked() {
    hide_mainScreen();
    show_playScreen();
}
void MainMenu::on_howtoplayButton_clicked() {
    hide_mainScreen();
    show_howtoplayScreen();
}
void MainMenu::on_creditsButton_clicked() {
    hide_mainScreen();
    show_creditsScreen();
}
void MainMenu::on_exitButton_clicked() {
    this->close();
}


