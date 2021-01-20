#include "game.h"

Game::Game(QGraphicsScene * scene, std::list<Proyectile *> *p, std::string seed, std::string type, std::string p1_name, std::string p2_name)
    : scene(scene), proyectiles(p), type(type)
{
    srand(unsigned(time(NULL)));

    floor1 = new Floor(scene, proyectiles, 1);
    floor2 = new Floor(scene, proyectiles, 2);
    floor3 = new Floor(scene, proyectiles, 3);

   if(!seed.empty())
       this->seed = std::stoul(seed);
   else
       this->seed = rand();

    if(type == "singleplayer"){
        p1 = new Player(nullptr, scene, p1_name, proyectiles, 0, 0, 0, 0, 0, 20, 8, 4, 1e-5, 0.1, 0);
        p2 = nullptr;
    }
    else if (type == "multiplayer") {
        p1 = new Player(nullptr, scene, p1_name, proyectiles, 0, 0, 0, 0, 0, 20, 8, 4, 1e-5, 0.1, 0);
        p2 = new Player(nullptr, scene, p2_name, proyectiles, 200, 50, 0, 0, 0, 20, 8, 4, 1e-5, 0.1, 0);
    }

    floor1->boss->boss_door->setNext(floor2);
    floor2->boss->boss_door->setNext(floor3);
}
Game::~Game() {
    delete floor1;
    delete floor2;
    delete floor3;

    scene = nullptr;
    proyectiles = nullptr;

    delete p1;
    delete p2;
}

void Game::reset()
{
    delete floor1;
    delete floor2;
    delete floor3;

    floor1 = new Floor(scene, proyectiles, 1);
    floor2 = new Floor(scene, proyectiles, 2);
    floor3 = new Floor(scene, proyectiles, 3);

    if(type == "singleplayer"){

        std::string p1_name, p2_name;

        p1_name = p1->getName();

        delete p1;

        p1 = new Player(nullptr, scene, p1_name, proyectiles, 0, 0, 0, 0, 0, 20, 8, 4, 1e-5, 0.1, 0);
    }
    else if (type == "multiplayer") {

        std::string p1_name, p2_name;

        p1_name = p1->getName();
        p2_name = p2->getName();

        delete p1;
        delete p2;

        p1 = new Player(nullptr, scene, p1_name, proyectiles, 0, 0, 0, 0, 0, 20, 8, 4, 1e-5, 0.1, 0);
        p2 = new Player(nullptr, scene, p2_name, proyectiles, 200, 50, 0, 0, 0, 20, 8, 4, 1e-5, 0.1, 0);
    }
}

std::string Game::getType() const {
    return type;
}
Player *Game::getP1() const {
    return p1;
}
Player *Game::getP2() const {
    return p2;
}
Floor *Game::getFloor1() const {
    return floor1;
}
unsigned int Game::getSeed() const {
    return seed;
}
