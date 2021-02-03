#ifndef ROOM_H
#define ROOM_H

#include <QObject>
#include <fstream>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <list>
#include "wall.h"
#include "enemy.h"
#include "door.h"
#include "item.h"
#include "boss.h"
#include "spring.h"

class Door;

class Room : public QObject, public QGraphicsItem {
    Q_OBJECT
public: // Variables
    Door *left_door;
    Door *right_door;
    Door *up_door;
    Door *down_door;

    Door *boss_door;

private: // Variables
    std::list <Wall *> walls;
    std::list <Enemy *> enemies;
    Item *item;
    Boss *boss;
    Spring *spring;

    std::string type;

    int itemX, itemY;

    QGraphicsScene *scene;

    QPixmap *bg;

    bool cleared;

    const int v_limit, h_limit;

    std::string name;

public: // Methods
    Room(QObject *parent = nullptr, QGraphicsScene* scene = nullptr , std::list<Proyectile *> *p = nullptr, std::string name_ = "");
    ~Room();

    void load_room();
    void deload_room();

    std::list<Enemy *> getEnemies() const;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget);

    void clear_room();

    bool isClear() const;

    int getItemX() const;
    int getItemY() const;

    void remove_item();

    void spawn_heart();
    void spawn_item(Item *i);

    std::string getType() const;

    Boss *getBoss() const;

    Spring *getSpring() const;

    std::string getName() const;

private: // Methods

};

#endif // ROOM_H
