#ifndef ROOM_H
#define ROOM_H

#include <QObject>
#include <fstream>
#include <QGraphicsScene>
#include "wall.h"
#include <vector>

class Room : public QObject {
    Q_OBJECT

public: // Variables

private: // Variables
    QList <Wall *> walls;

    //QList< std::vector<int>[2] > spawnpoints;

public: // Methods
    explicit Room(QObject *parent = nullptr, std::string file_name_ = "");
    ~Room();

    void load_walls(QGraphicsScene* scene);

private: // Methods
    void load_walls(std::string file_name);

};

#endif // ROOM_H
