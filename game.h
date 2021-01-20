#ifndef GAME_H
#define GAME_H
#include "floor.h"
#include "player.h"

class Game {

private: // variables
    Floor *floor1, *floor2, *floor3;

    QGraphicsScene *scene;
    std::list<Proyectile *> *proyectiles;

    unsigned int seed;

    std::string type;

    Player *p1, *p2;

public: // variables

private: // methods

public: // methods
    Game(QGraphicsScene * scene = nullptr, std::list<Proyectile *> *p = nullptr, std::string seed = "0", std::string type = "singleplayer", std::string p1_name = "Benedict", std::string p2_name = "Tomoe");
    ~Game();

    void reset();

    std::string getType() const;
    Player *getP1() const;
    Player *getP2() const;
    Floor *getFloor1() const;
    unsigned int getSeed() const;
};

#endif // GAME_H
