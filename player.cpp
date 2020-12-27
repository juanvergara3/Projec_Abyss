#include "player.h"

short Player::getDirection() const
{
    return direction;
}

Player::Player(QObject *parent, float x_, float y_, float vx_, float vy_, float mass_, int radio_, float g_, float K_, float e_, float V_) :
    Entity(parent, x_, y_, vx_, vy_, mass_, radio_, g_, K_, e_, V_)
{
    health = 100;
    damage = 20;
    shot_speed = 30;
    fire_rate = 2;
    movement_speed = 5;
    jump_Speed = 40;
    sight = 1;
    direction = 0;
}

Proyectile *Player::shoot(QGraphicsScene *scene) {
    Proyectile *p = new Proyectile(this, damage, this->getX(), this->getY(), sight*shot_speed, 0, 1, 4, 1, 1e-5, 0.1, 0);

    scene->addItem(p);
    //p->setPos(p->getX(), 720 - p->getY());

    return p;
}

void Player::update(int y_max) {
    this->Entity::update(y_max);

    int direction = this->direction;

    float dx = direction * movement_speed;
    float newPos = this->getX() + dx;

    this->set_velX(newPos, this->getVx());
}

float Player::getMovement_speed() const{
    return movement_speed;
}
float Player::getJump_Speed() const{
    return jump_Speed;
}

void Player::addDirection(int d)
{
    if (d == direction)
        return;

    direction += d;

//    if (0 != direction) {
//        if (-1 == direction)
//            setTransform(QTransform(-1, 0, 0, 1, boundingRect().width(), 0));
//        else
//            setTransform(QTransform());
//    }
}

bool Player::getJumping() const {
    return jumping;
}
void Player::setJumping(bool value) {
    jumping = value;
}
void Player::setSight(short value) {
    sight = value;
}
