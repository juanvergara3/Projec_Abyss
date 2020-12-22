#include "player.h"

Player::Player(QObject *parent, float x_, float y_, float vx_, float vy_, float mass_, int radio_, float g_, float K_, float e_, float V_) :
    Entity(parent, x_, y_, vx_, vy_, mass_, radio_, g_, K_, e_, V_)
{
    health = 100;
    damage = 20;
    shot_speed = 50;
    fire_rate = 2;
    movement_speed = 15;
    jump_Speed = 40;
}

void Player::shoot(QGraphicsScene *scene) {
    Proyectile *p = new Proyectile(this, damage, this->getX(), this->getY(), shot_speed, 0, 1, 4, 1, 1e-5, 0.1, 0);

    scene->addItem(p);
    proyectiles.push_back(p);
}

float Player::getMovement_speed() const{
    return movement_speed;
}
float Player::getJump_Speed() const{
    return jump_Speed;
}

void Player::update(int y_max)
{
    this->Entity::update(y_max);

    for (auto const& k : proyectiles) {
        k->Entity::update(y_max);
    }
}

bool Player::getJumping() const {
    return jumping;
}
void Player::setJumping(bool value) {
    jumping = value;
}

