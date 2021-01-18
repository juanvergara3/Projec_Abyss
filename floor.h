#ifndef FLOOR_H
#define FLOOR_H
#include "room.h"

class Floor {
private: // variables
    Room *treasure, *boss;
    Room *r1,*r2, *r3, *r4;

    QGraphicsScene *scene;
    std::list<Proyectile *> *proyectiles;

public: // variables
    Room *safe;

private: // methods
    void load_floor(short num);
    void load_links(short num);

public: // methods
    Floor(QGraphicsScene *scene = nullptr, std::list<Proyectile *> *p = nullptr, short num = 0);
    ~Floor();
};

#endif // FLOOR_H
