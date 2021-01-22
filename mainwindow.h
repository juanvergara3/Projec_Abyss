#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QMouseEvent>
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include <fstream>
#include "game.h"
#include "messagewindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class PauseMenu;
class MainMenu;

class MainWindow : public QMainWindow {
    Q_OBJECT

public: // Variables

private: // Variables
    Ui::MainWindow *ui;
    PauseMenu *pause_menu;
    MainMenu *main_menu;

    MessageWindow *gameover_window;
    MessageWindow *victory_window;

    QGraphicsScene *scene;

    QTimer *timer;

    Game *game;
    Boss *boss;
    Room *current_room;
    std::string current_room_type;
    Floor *current_floor;
    Player *p1, *p2;
    Spring *spring;

    std::list<Proyectile*> proyectiles;
    std::list<Enemy*> enemies;
    std::list<Item*> item_bank;

     int h_limit, v_limit;

public: // Methods
    MainWindow(QWidget *parent = nullptr, PauseMenu *p = nullptr);
    ~MainWindow();

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    void mousePressEvent(QMouseEvent *event);

    void pause();
    void resume();
    void reset_game();
    void close_game();
    void game_over();
    void victory();

    void setPause_menu(PauseMenu *value);
    void setMain_menu(MainMenu *value);

    void setGame(Game *value);

    std::list<Proyectile *> *getProyectiles();
    QGraphicsScene *getScene() const;

    void setGameover_window(MessageWindow *value);

    void setVictory_window(MessageWindow *value);

private: // Methods
    void check_collitions(Player *p);
    bool check_collitions(Proyectile *p);
    void check_collitions(Enemy *e);
    void check_collitions(Boss *b);

    Item *get_random_item();

    void load_items(std::string file_name);

public slots:
    void update_bodies();

};
#endif // MAINWINDOW_H
