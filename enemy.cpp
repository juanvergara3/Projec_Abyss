#include "enemy.h"

Enemy::Enemy(QObject *parent, QGraphicsScene *s, std::string type, std::list<Proyectile *> *p, int dificulty, float x_, float y_, float vx_, float vy_, float mass_, int radio_, float g_, float K_, float e_, float V_) :
    Entity(parent, x_, y_, vx_, vy_, mass_, radio_, g_, K_, e_, V_)
{
    shooting_timer = new QTimer;
    movement_timer = new QTimer;

    connect(movement_timer, SIGNAL(timeout()), this, SLOT(jump()));

    scene = s;
    proyectiles = p;
    sight = 1;

    if(dificulty == 1){
        health = 40;
        damage = 10;
        movement_speed = 10; //***
        jump_Speed = 20; //***
        shot_speed = 5;
        fire_rate = 2500;
    }
    else if(dificulty == 2){
        health = 60;
        damage = 20;
        movement_speed = 10; //***
        jump_Speed = 20; //***
        shot_speed = 10;
        fire_rate = 2000;
    }
    else if(dificulty == 3){
        health = 80;
        damage = 30;
        movement_speed = 10; //***
        jump_Speed = 20; //***
        shot_speed = 15;
        fire_rate = 1500;
    }
    else if(dificulty == 4){
        health = 100;
        damage = 40;
        movement_speed = 10; //***
        jump_Speed = 20; //***
        shot_speed = 20;
        fire_rate = 1000;
    }
    else if(dificulty == 5){
        health = 120;
        damage = 50;
        movement_speed = 10; //***
        jump_Speed = 20; //***
        shot_speed = 25;
        fire_rate = 500;
    }
    else{
        health = 0;
        damage = 0;
        movement_speed = 0; //***
        jump_Speed = 0; //***
        shot_speed = 0;
        fire_rate = 0;
    }

    if(type == "single"){

        connect(shooting_timer, SIGNAL(timeout()), this, SLOT(shoot_single()));

    }
    else if(type == "double"){

        connect(shooting_timer, SIGNAL(timeout()), this, SLOT(shoot_double()));

    }
    else if(type == "cross"){

        connect(shooting_timer, SIGNAL(timeout()), this, SLOT(shoot_cross()));

    }
    else if(type == "x"){

        connect(shooting_timer, SIGNAL(timeout()), this, SLOT(shoot_x()));

    }
    else if(type == "orbit"){

    }
    else if(type == "circular"){ // might be?

    }
}
Enemy::~Enemy() {
    delete shooting_timer;
    delete movement_timer;
}

int Enemy::getDamage() const {
    return damage;
}
int Enemy::getHealth() const {
    return health;
}

void Enemy::take_damage(int damage) {
    health -= damage;
}

void Enemy::init() {
    shooting_timer->start(fire_rate);
    movement_timer->start(2000);
}
void Enemy::stop() {
    shooting_timer->stop();
    movement_timer->stop();
}

void Enemy::shoot_single() {
    Proyectile *p = new Proyectile(this, "enemy", damage, this->getX(), this->getY(), sight*shot_speed, 0, 1, 4, 1, 1e-5, 0.1, 0);

    proyectiles->push_back(p);
    p->setPos(p->getX(), getV_limit() - p->getY());
    scene->addItem(p);
}
void Enemy::shoot_double() {
    Proyectile *p;

    p = new Proyectile(this, "enemy", damage, this->getX(), this->getY(), sight*shot_speed, 0, 1, 4, 1, 1e-5, 0.1, 0);
    proyectiles->push_back(p);
    p->setPos(p->getX(), getV_limit() - p->getY());
    scene->addItem(p);

    p = new Proyectile(this, "enemy", damage, this->getX(), this->getY(), -sight*shot_speed, 0, 1, 4, 1, 1e-5, 0.1, 0);
    proyectiles->push_back(p);
    p->setPos(p->getX(), getV_limit() - p->getY());
    scene->addItem(p);
}
void Enemy::shoot_cross() {
    Proyectile *p;

    p = new Proyectile(this, "enemy", damage, this->getX(), this->getY(), sight*shot_speed, 0, 1, 4, 1, 1e-5, 0.1, 0);
    proyectiles->push_back(p);
    p->setPos(p->getX(), getV_limit() - p->getY());
    scene->addItem(p);

    p = new Proyectile(this, "enemy", damage, this->getX(), this->getY(), -sight*shot_speed, 0, 1, 4, 1, 1e-5, 0.1, 0);
    proyectiles->push_back(p);
    p->setPos(p->getX(), getV_limit() - p->getY());
    scene->addItem(p);

    p = new Proyectile(this, "enemy", damage, this->getX(), this->getY(), 0, sight*shot_speed, 1, 4, 1, 1e-5, 0.1, 0);
    proyectiles->push_back(p);
    p->setPos(p->getX(), getV_limit() - p->getY());
    scene->addItem(p);

    p = new Proyectile(this, "enemy", damage, this->getX(), this->getY(), 0, -sight*shot_speed, 1, 4, 1, 1e-5, 0.1, 0);
    proyectiles->push_back(p);
    p->setPos(p->getX(), getV_limit() - p->getY());
    scene->addItem(p);
}
void Enemy::shoot_x() {
    Proyectile *p;

    p = new Proyectile(this, "enemy", damage, this->getX(), this->getY(), sight*(shot_speed), sight*(shot_speed), 1, 4, 1, 1e-5, 0.1, 0);
    proyectiles->push_back(p);
    p->setPos(p->getX(), getV_limit() - p->getY());
    scene->addItem(p);

    p = new Proyectile(this, "enemy", damage, this->getX(), this->getY(), -sight*(shot_speed), -sight*(shot_speed), 1, 4, 1, 1e-5, 0.1, 0);
    proyectiles->push_back(p);
    p->setPos(p->getX(), getV_limit() - p->getY());
    scene->addItem(p);

    p = new Proyectile(this, "enemy", damage, this->getX(), this->getY(), -sight*shot_speed, sight*shot_speed, 1, 4, 1, 1e-5, 0.1, 0);
    proyectiles->push_back(p);
    p->setPos(p->getX(), getV_limit() - p->getY());
    scene->addItem(p);

    p = new Proyectile(this, "enemy", damage, this->getX(), this->getY(), sight*shot_speed, -sight*shot_speed, 1, 4, 1, 1e-5, 0.1, 0);
    proyectiles->push_back(p);
    p->setPos(p->getX(), getV_limit() - p->getY());
    scene->addItem(p);
}
void Enemy::shoot_orbit() {

}

void Enemy::jump() {
    set_velY(getY(), 30);
}
