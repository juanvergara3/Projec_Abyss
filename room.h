#ifndef ROOM_H
#define ROOM_H

#include <QObject>
#include <fstream>
#include <QGraphicsScene>
#include <list>
#include "wall.h"
#include "enemy.h"
#include "door.h"
#include "item.h"
#include "boss.h"

class Door;

class Room : public QObject {
    Q_OBJECT
public: // Variables
    std::list <Door *> doors;

private: // Variables
    std::list <Wall *> walls;
    std::list <Enemy *> enemies;
    Item *item;
    Boss *boss;

    std::string type; // ***change the type on the load room function***

    int itemX, itemY;

    QGraphicsScene *scene;

    bool cleared;

    const int v_limit, h_limit;

public: // Methods
    explicit Room(QObject *parent = nullptr, QGraphicsScene* scene = nullptr , std::list<Proyectile *> *p = nullptr, std::string file_name_ = "");
    ~Room();

    void load_room();
    void deload_room();

    std::list<Enemy *> getEnemies() const;

    void clear_room();

    bool isClear() const;

    int getItemX() const;
    int getItemY() const;

    void remove_item();

    void spawn_heart();
    void spawn_item(Item *i);

    std::string getType() const;

    Boss *getBoss() const;

private: // Methods
    void load_room(std::string file_name);

};

#endif // ROOM_H
