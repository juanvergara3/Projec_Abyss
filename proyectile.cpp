#include "proyectile.h"
#include "player.h"
#include "enemy.h"
#include "boss.h"

Proyectile::Proyectile(QObject *parent, std::string type, float damage_, float x_, float y_, float vx_, float vy_, float mass_, int radio_, float g_, float K_, float e_, float V_)
    : Entity(parent, x_, y_,  vx_, vy_, mass_, radio_, g_, K_,  e_, V_)
{
    damage = damage_;
    this->type = type;
    movement_type = "normal";

    player = nullptr;
    enemy = nullptr;
    boss = nullptr;
}
Proyectile::Proyectile(QObject *parent, Player *orbit, float damage_, float x_, float y_, float vx_, float vy_, float mass_, int radio_, float g_, float K_, float e_, float V_)
    : Entity(parent, x_, y_,  vx_, vy_, mass_, radio_, g_, K_,  e_, V_)
{
    damage = damage_;
    type = "player";
    movement_type = "orbital";

    entity = orbit;

    player = orbit;
    enemy = nullptr;
    boss = nullptr;
}
Proyectile::Proyectile(QObject *parent, Enemy *orbit, float damage_, float x_, float y_, float vx_, float vy_, float mass_, int radio_, float g_, float K_, float e_, float V_)
    : Entity(parent, x_, y_,  vx_, vy_, mass_, radio_, g_, K_,  e_, V_)
{
    damage = damage_;
    type = "enemy";
    movement_type = "orbital";

    entity = orbit;

    player = nullptr;
    enemy = orbit;
    boss = nullptr;
}
Proyectile::Proyectile(QObject *parent, Boss *orbit, float damage_, float x_, float y_, float vx_, float vy_, float mass_, int radio_, float g_, float K_, float e_, float V_)
    : Entity(parent, x_, y_,  vx_, vy_, mass_, radio_, g_, K_,  e_, V_)
{
    damage = damage_;
    type = "boss";
    movement_type = "orbital";

    entity = orbit;

    player = nullptr;
    enemy = nullptr;
    boss = orbit;
}
Proyectile::~Proyectile() {
    entity = nullptr;

    player = nullptr;
    enemy = nullptr;
    boss = nullptr;
}

float Proyectile::getDamage() const {
    return damage;
}
std::string Proyectile::getType() const {
    return type;
}

void Proyectile::update() {
    if(movement_type == "normal")
        this->Entity::update();
    else if(movement_type == "orbital")
        this->orbital_update(entity);
}
