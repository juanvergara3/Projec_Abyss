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
#include "room.h"
#include "player.h"
#include "item.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public: // Variables

private: // Variables
    Ui::MainWindow *ui;

    QGraphicsScene *scene;

    QTimer *timer;

    Boss *boss;

    Room *current_room;
    std::string current_room_type;

    Room *r1;
    Room *r2;

    int h_limit, v_limit;

    std::list<Proyectile*> proyectiles;
    std::list<Enemy*> enemies;
    std::list<Item*> item_bank;

    Player *p1, *p2;

public: // Methods
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    void mousePressEvent(QMouseEvent *event);

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
