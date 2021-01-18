#include "floor.h"

Floor::Floor(QGraphicsScene *scene, std::list<Proyectile *> *p, short num)
    :scene(scene), proyectiles(p)
{
    load_floor(num);
}
Floor::~Floor() {
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

    load_links(num);
}

void Floor::load_links(short num)
{
    if(num == 1){
        safe->right_door->setLink(r1->left_door);
        r1->left_door->setLink(safe->right_door);

        r1->right_door->setLink(r2->left_door);
        r2->left_door->setLink(r1->right_door);

        r2->up_door->setLink(treasure->down_door);
        treasure->down_door->setLink((r2->up_door));

        r1->down_door->setLink(r3->up_door);
        r3->up_door->setLink(r1->down_door);

        r3->down_door->setLink(r4->up_door);
        r4->up_door->setLink(r3->down_door);

        r4->right_door->setLink(boss->left_door);
        boss->left_door->setLink(r4->right_door);
    }
    else if (num == 2) {
        safe->down_door->setLink(r1->up_door);
        r1->up_door->setLink(safe->down_door);

        r1->left_door->setLink(r2->right_door);
        r2->right_door->setLink(r1->left_door);

        r2->left_door->setLink(treasure->right_door);
        treasure->right_door->setLink(r2->left_door);

        r1->right_door->setLink(r3->left_door);
        r3->left_door->setLink(r1->right_door);

        r3->right_door->setLink(r4->left_door);
        r4->left_door->setLink(r3->right_door);

        r4->up_door->setLink(boss->down_door);
        boss->down_door->setLink(r4->up_door);
    }
    else if (num == 3) {
        safe->up_door->setLink(r1->right_door);
        r1->right_door->setLink(safe->up_door);

        r1->left_door->setLink(treasure->right_door);
        treasure->right_door->setLink(r1->left_door);

        safe->right_door->setLink(r2->left_door);
        r2->left_door->setLink(safe->right_door);

        r2->right_door->setLink(r3->up_door);
        r3->up_door->setLink(r2->right_door);

        r2->up_door->setLink(r4->left_door);
        r4->left_door->setLink(r2->up_door);

        r4->right_door->setLink(boss->left_door);
        boss->left_door->setLink(r4->right_door);
    }
}
