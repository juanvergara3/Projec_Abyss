#include "game.h"

Game::Game(QGraphicsScene * scene, std::list<Proyectile *> *p, unsigned int seed)
    : scene(scene), proyectiles(p)
{
    floor1 = new Floor(scene, proyectiles, 1);
    floor2 = new Floor(scene, proyectiles, 2);
    floor3 = new Floor(scene, proyectiles, 3);


}
Game::~Game()
{
    delete floor1;
    delete floor2;
    delete floor3;
}
