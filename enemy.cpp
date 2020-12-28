#include "enemy.h"

float Enemy::getHealth() const
{
    return health;
}

void Enemy::take_damage(int damage)
{
    health -= damage;
}

Enemy::Enemy(QObject *parent, int dificulty, float x_, float y_, float vx_, float vy_, float mass_, int radio_, float g_, float K_, float e_, float V_) :
    Entity(parent, x_, y_, vx_, vy_, mass_, radio_, g_, K_, e_, V_)
{
    shooting_timer = new QTimer;

    if(dificulty == 1){
        health = 40;
        damage = 10;
        movement_speed = 10; //***
        jump_Speed = 20; //***
    }
    else if(dificulty == 2){
        health = 60;
        damage = 20;
        movement_speed = 10; //***
        jump_Speed = 20; //***

    }
    else if(dificulty == 3){
        health = 80;
        damage = 30;
        movement_speed = 10; //***
        jump_Speed = 20; //***

    }
    else if(dificulty == 4){
        health = 100;
        damage = 40;
        movement_speed = 10; //***
        jump_Speed = 20; //***

    }
    else if(dificulty == 5){
        health = 120;
        damage = 50;
        movement_speed = 10; //***
        jump_Speed = 20; //***

    }
    else{
        health = 0;
        damage = 0;
        movement_speed = 0; //***
        jump_Speed = 0; //***
    }
}

Enemy::~Enemy() {

}

Proyectile *Enemy::shoot(QGraphicsScene *scene)
{
    Proyectile *p = new Proyectile(this, damage, this->getX(), this->getY(), sight*shot_speed, 0, 1, 4, 1, 1e-5, 0.1, 0);

    scene->addItem(p);
    //p->setPos(p->getX(), 720 - p->getY());

    return p;
}
