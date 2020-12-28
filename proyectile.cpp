#include "proyectile.h"


float Proyectile::getDamage() const
{
    return damage;
}

Proyectile::Proyectile(QObject *parent, float damage_, float x_, float y_, float vx_, float vy_, float mass_, int radio_, float g_, float K_, float e_, float V_)
    : Entity(parent, x_, y_,  vx_, vy_, mass_, radio_, g_, K_,  e_, V_)
{
    damage = damage_;
}

Proyectile::~Proyectile() {
    //delete this;
}
