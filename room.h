#ifndef ROOM_H
#define ROOM_H

#include <QObject>
#include <fstream>
#include <QGraphicsScene>
#include <vector>
#include <list>
#include "wall.h"
#include "enemy.h"

class Room : public QObject {
    Q_OBJECT

public: // Variables

private: // Variables
    //QList <Wall *> walls;
    std::list <Wall *> walls;
    std::list <Enemy *> enemies;
    //QList< std::vector<int>[2] > spawnpoints;

    QGraphicsScene *scene;

    const int v_limit, h_limit;

public: // Methods
    explicit Room(QObject *parent = nullptr, QGraphicsScene* scene = nullptr , std::list<Proyectile *> *p = nullptr, std::string file_name_ = "");
    ~Room();

    void load_room();

    std::list<Enemy *> getEnemies() const;

private: // Methods
    void load_room(std::string file_name);
    //void check_collitions();

};

#endif // ROOM_H
