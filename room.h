#ifndef ROOM_H
#define ROOM_H

#include <QObject>
#include <fstream>
#include <QGraphicsScene>
#include <vector>
#include <list>
#include "wall.h"
#include "enemy.h"
#include "door.h"

class Door;

class Room : public QObject {
    Q_OBJECT
public: // Variables
    Door *door;
    std::list <Door *> doors;

private: // Variables
    std::list <Wall *> walls;
    std::list <Enemy *> enemies;
    //std::list <Door *> doors;
    //QList< std::vector<int>[2] > spawnpoints;

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

private: // Methods
    void load_room(std::string file_name);

};

#endif // ROOM_H
