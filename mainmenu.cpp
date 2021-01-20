#include "mainmenu.h"
#include "ui_mainmenu.h"
#include "mainwindow.h"
#include "pausemenu.h"

MainMenu::MainMenu(QWidget *parent, MainWindow *w) :
    QMainWindow(parent), ui(new Ui::MainMenu), mainwindow(w), pausemenu(nullptr)
{
    mainwindow = new MainWindow(nullptr, nullptr);
    pausemenu = new PauseMenu(nullptr, nullptr);

    gameover_window = new MessageWindow(nullptr, "gameover");
    victory_window = new MessageWindow(nullptr, "victory");

    gameover_window->setMain_menu(this);
    gameover_window->setMain_window(mainwindow);
    victory_window->setMain_menu(this);
    victory_window->setMain_window(mainwindow);

    mainwindow->setPause_menu(pausemenu);
    mainwindow->setMain_menu(this);
    mainwindow->setVictory_window(victory_window);
    mainwindow->setGameover_window(gameover_window);

    pausemenu->setMain_window(mainwindow);
    pausemenu->setMain_menu(this);

    ui->setupUi(this);

    init_lists();

    hide_playScreen();
    hide_creditsScreen();
    hide_howtoplayScreen();
    hide_singleplayerScreen();
    hide_multiplayerScreen();
}
MainMenu::~MainMenu() {
    //mainwindow->close();
    //pausemenu->close();

    //delete mainwindow;
    //delete pausemenu;
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
    multiplayerScreen.push_back(ui->seed_multi);
    multiplayerScreen.push_back(ui->seedLabel_2);

    singleplayerScreen.push_back(ui->gobackButton_4);
    singleplayerScreen.push_back(ui->playButton_single);
    singleplayerScreen.push_back(ui->playerLabel);
    singleplayerScreen.push_back(ui->playerName);
    singleplayerScreen.push_back(ui->seed_single);
    singleplayerScreen.push_back(ui->seedLabel_1);

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

void MainMenu::on_playButton_clicked() { // on main screen
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
    //mainwindow->close();
    //pausemenu->close();
}

void MainMenu::on_gobackButton_3_clicked() { // on credits screen
    hide_creditsScreen();
    show_mainScreen();
}

void MainMenu::on_gobackButton_2_clicked() { // on how to play screen
    hide_howtoplayScreen();
    show_mainScreen();
}

void MainMenu::on_singleplayerButton_clicked() { // on play screen
    hide_playScreen();
    show_singleplayerScreen();
}
void MainMenu::on_multiplayerButton_clicked() {
    hide_playScreen();
    show_multiplayerScreen();
}
void MainMenu::on_loadgameButton_clicked() {

}
void MainMenu::on_gobackButton_1_clicked() {
    hide_playScreen();
    show_mainScreen();
}

void MainMenu::on_playButton_single_clicked() { // on single player screen
    hide_singleplayerScreen();
    show_mainScreen();
    //this->hide();
    this->close();

    mainwindow->close_game();
    mainwindow->setGame(new Game(mainwindow->getScene(), mainwindow->getProyectiles(), ui->seed_single->text().toStdString(), "singleplayer", ui->playerName->text().toStdString(), "Tomoe"));
    mainwindow->showMaximized();
}
void MainMenu::on_gobackButton_4_clicked() {
    hide_singleplayerScreen();
    show_playScreen();
}

void MainMenu::on_playButton_2_clicked() { // on multiplayer screen
    hide_multiplayerScreen();
    show_mainScreen();
    //this->hide();
    this->close();

    mainwindow->close_game();
    mainwindow->setGame(new Game(mainwindow->getScene(), mainwindow->getProyectiles(), ui->seed_multi->text().toStdString(), "multiplayer", ui->player1Name->text().toStdString(), ui->player2Name->text().toStdString()));
    mainwindow->showMaximized();
}
void MainMenu::on_gobackButton_5_clicked() {
    hide_multiplayerScreen();
    show_playScreen();
}

void MainMenu::setMainwindow(MainWindow *value) {
    mainwindow = value;
}
void MainMenu::setPausemenu(PauseMenu *value) {
    pausemenu = value;
}
