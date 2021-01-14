#ifndef PROYECTILE_H
#define PROYECTILE_H
#include "entity.h"
#include "wall.h"

class Player;
class Enemy;
class Boss;

class Proyectile: public Entity {
    Q_OBJECT
public: // Variables

private: // Variables
    float damage;
    float shot_speed;

    std::string type;
    std::string movement_type;

    Player *player;
    Enemy *enemy;
    Boss *boss;

    Entity *entity;

public: // Methods
    explicit Proyectile(QObject *parent = nullptr, std::string type = "", float damage_ = 0, float x_ = 0, float y_ = 0, float vx_ = 0, float vy_ = 0, float mass_ = 0, int radio_ = 0, float g_ = 0, float K_ = 0, float e_ = 0, float V_ = 0);
    Proyectile(QObject *parent = nullptr, Player *orbit = nullptr , float damage_ = 0, float x_ = 0, float y_ = 0, float vx_ = 0, float vy_ = 0, float mass_ = 0, int radio_ = 0, float g_ = 0, float K_ = 0, float e_ = 0, float V_ = 0);
    Proyectile(QObject *parent = nullptr, Enemy *orbit = nullptr , float damage_ = 0, float x_ = 0, float y_ = 0, float vx_ = 0, float vy_ = 0, float mass_ = 0, int radio_ = 0, float g_ = 0, float K_ = 0, float e_ = 0, float V_ = 0);
    Proyectile(QObject *parent = nullptr, Boss  *orbit = nullptr , float damage_ = 0, float x_ = 0, float y_ = 0, float vx_ = 0, float vy_ = 0, float mass_ = 0, int radio_ = 0, float g_ = 0, float K_ = 0, float e_ = 0, float V_ = 0);
    ~Proyectile();

    float getDamage() const;

    std::string getType() const;

    void update();

private: // Methods

};

#endif // PROYECTILE_H
