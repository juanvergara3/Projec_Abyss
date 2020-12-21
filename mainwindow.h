#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QGraphicsScene>
#include <QKeyEvent>
#include "room.h"
#include "player.h"

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

    Player *p1;

    Room *r1;

    int h_limit, v_limit;

public: // Methods
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void keyPressEvent(QKeyEvent *event);

private: // Methods
    void check_collitions(Player *p);

public slots:
    void update_bodies();

};
#endif // MAINWINDOW_H
