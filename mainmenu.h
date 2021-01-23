#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>
#include <QFileDialog>
#include "messagewindow.h"

namespace Ui { class MainMenu; }

class MainWindow;
class PauseMenu;

class MainMenu : public QMainWindow
{
    Q_OBJECT
public: // variables

private: // variables
    QList<QWidget*> mainScreen;
    QList<QWidget*> playScreen;
    QList<QWidget*> creditsScreen;
    QList<QWidget*> howtoplayScreen;
    QList<QWidget*> singleplayerScreen;
    QList<QWidget*> multiplayerScreen;

    Ui::MainMenu *ui;

    MainWindow *mainwindow;
    PauseMenu *pausemenu;
    MessageWindow *gameover_window;
    MessageWindow *victory_window;

public: // methods
    explicit MainMenu(QWidget *parent = nullptr, MainWindow *w = nullptr);
    ~MainMenu();

    void setMainwindow(MainWindow *value);
    void setPausemenu(PauseMenu *value);

private: // methods
    void init_lists();

    void hide_mainScreen();
    void hide_playScreen();
    void hide_creditsScreen();
    void hide_howtoplayScreen();
    void hide_singleplayerScreen();
    void hide_multiplayerScreen();

    void show_mainScreen();
    void show_playScreen();
    void show_creditsScreen();
    void show_howtoplayScreen();
    void show_singleplayerScreen();
    void show_multiplayerScreen();

private slots:
    void on_playButton_clicked();
    void on_howtoplayButton_clicked();
    void on_creditsButton_clicked();
    void on_exitButton_clicked();

    void on_gobackButton_3_clicked();

    void on_gobackButton_2_clicked();

    void on_singleplayerButton_clicked();
    void on_multiplayerButton_clicked();
    void on_loadgameButton_clicked();
    void on_gobackButton_1_clicked();

    void on_playButton_single_clicked();
    void on_gobackButton_4_clicked();

    void on_playButton_2_clicked();
    void on_gobackButton_5_clicked();
};

#endif // MAINMENU_H
