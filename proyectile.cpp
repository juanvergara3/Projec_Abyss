#include "proyectile.h"

Proyectile::Proyectile(QObject *parent, std::string type, float damage_, float x_, float y_, float vx_, float vy_, float mass_, int radio_, float g_, float K_, float e_, float V_)
    : Entity(parent, x_, y_,  vx_, vy_, mass_, radio_, g_, K_,  e_, V_)
{
    // default projectile constructor (parabolic projectiles *)

    damage = damage_;
    this->type = type;
    movement_type = "normal";

    entity = nullptr;
}

Proyectile::Proyectile(QObject *parent, std::string type, Entity *orbit, float damage_, float x_, float y_, float vx_, float vy_, float mass_, int radio_, float g_, float K_, float e_, float V_)
    : Entity(parent, x_, y_,  vx_, vy_, mass_, radio_, g_, K_,  e_, V_)
{
    // constructor for orbital projectiles

    damage = damage_;
    this->type = type;
    movement_type = "orbital";

    entity = orbit;
}
Proyectile::~Proyectile() {
    entity = nullptr;
}

float Proyectile::getDamage() const {
    return damage;
}
std::string Proyectile::getType() const {
    return type;
}

void Proyectile::update() { // overloaded method, updates the projectile based on its type
    if(movement_type == "normal")
        this->Entity::update();
    else if(movement_type == "orbital")
        this->orbital_update(entity);
}
