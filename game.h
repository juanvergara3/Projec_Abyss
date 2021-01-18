#ifndef GAME_H
#define GAME_H
#include "floor.h"

class Game {

private: // variables
    Floor *floor1, *floor2, *floor3;

    QGraphicsScene *scene;
    std::list<Proyectile *> *proyectiles;

public: // variables

private: // methods

public: // methods
    Game(QGraphicsScene * scene = nullptr, std::list<Proyectile *> *p = nullptr, unsigned int seed = 0);
    ~Game();
};

#endif // GAME_H
