#include "proyectile.h"

Proyectile::Proyectile(QObject *parent, std::string type, float damage_, float x_, float y_, float vx_, float vy_, float mass_, int radio_, float g_, float K_, float e_, float V_)
    : Entity(parent, x_, y_,  vx_, vy_, mass_, radio_, g_, K_,  e_, V_)
{
    damage = damage_;
    this->type = type;
}
Proyectile::~Proyectile() {

}

float Proyectile::getDamage() const {
    return damage;
}
std::string Proyectile::getType() const {
    return type;
}
