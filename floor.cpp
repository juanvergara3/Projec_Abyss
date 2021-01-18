#include "floor.h"

Floor::Floor(QGraphicsScene *scene, std::list<Proyectile *> *p, short num)
    :scene(scene), proyectiles(p)
{
    load_floor(num);
}

Floor::~Floor()
{
    delete safe;
    delete treasure;
    delete boss;
    delete r1;
    delete r2;
    delete r3;
    delete r4;
}

void Floor::load_floor(short num) {

    if(num == 1){
        safe = new Room(nullptr, scene, proyectiles, "f1-safe");
        treasure = new Room(nullptr, scene, proyectiles, "f1-item");
        boss = new Room(nullptr, scene, proyectiles, "lamprey");
        r1 = new Room(nullptr, scene, proyectiles, "f1-1");
        r2 = new Room(nullptr, scene, proyectiles, "f1-2");
        r3 = new Room(nullptr, scene, proyectiles, "f1-3");
        r4 = new Room(nullptr, scene, proyectiles, "f1-4");
    }
    else if (num == 2) {
        safe = new Room(nullptr, scene, proyectiles, "f2-safe");
        treasure = new Room(nullptr, scene, proyectiles, "f2-item");
        boss = new Room(nullptr, scene, proyectiles, "priest");
        r1 = new Room(nullptr, scene, proyectiles, "f2-1");
        r2 = new Room(nullptr, scene, proyectiles, "f2-2");
        r3 = new Room(nullptr, scene, proyectiles, "f2-3");
        r4 = new Room(nullptr, scene, proyectiles, "f2-4");
    }
    else if (num == 3) {
        safe = new Room(nullptr, scene, proyectiles, "f3-safe");
        treasure = new Room(nullptr, scene, proyectiles, "f3-item");
        boss = new Room(nullptr, scene, proyectiles, "expelled");
        r1 = new Room(nullptr, scene, proyectiles, "f3-1");
        r2 = new Room(nullptr, scene, proyectiles, "f3-2");
        r3 = new Room(nullptr, scene, proyectiles, "f3-3");
        r4 = new Room(nullptr, scene, proyectiles, "f3-4");
    }
    else{
        safe = nullptr;
        treasure = nullptr;
        boss = nullptr;
        r1 = nullptr;
        r2 = nullptr;
        r3 = nullptr;
        r4 = nullptr;
    }
}
