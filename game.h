#ifndef GAME_H
#define GAME_H
#include <fstream>
#include "floor.h"
#include "player.h"

class Game {

private: // variables
    Floor *floor1, *floor2, *floor3;

    QGraphicsScene *scene;
    std::list<Proyectile *> *proyectiles;
    std::list<Item*> item_bank;

    Room *current_room;
    Floor *current_floor;

    unsigned int seed;

    std::string type;

    Player *p1, *p2;

public: // variables

private: // methods
    void shuffle_items();
    void load_items(std::string file_name);

public: // methods
    Game(QGraphicsScene * scene = nullptr, std::list<Proyectile *> *p = nullptr, std::string seed = "0", std::string type = "singleplayer", std::string p1_name = "Benedict", std::string p2_name = "Tomoe");
    Game(std::string file_name = "", QGraphicsScene * scene = nullptr, std::list<Proyectile *> *p = nullptr);
    ~Game();

    void reset();

    void save_game(std::string file_name);

    Item *get_random_item();

    std::string getType() const;
    Player *getP1() const;
    Player *getP2() const;
    Floor *getFloor1() const;
    unsigned int getSeed() const;

    Room *getCurrent_room() const;
    void setCurrent_room(Room *value);

    Floor *getCurrent_floor() const;
    void setCurrent_floor(Floor *value);
};

#endif // GAME_H
