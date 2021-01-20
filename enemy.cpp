#include "enemy.h"

Enemy::Enemy(QObject *parent, QGraphicsScene *s, std::string shooting_type, std::string movement_type, std::list<Proyectile *> *p, int dificulty, float x_, float y_, float vx_, float vy_, float mass_, int radio_, float g_, float K_, float e_, float V_) :
    Entity(parent, x_, y_, vx_, vy_, mass_, radio_, g_, K_, e_, V_)
{
    shooting_timer = new QTimer;
    movement_timer = new QTimer;

    scene = s;
    proyectiles = p;
    sight = 1;

    srand(time(NULL));

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
        jump_Speed = 30; //***
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

    if(shooting_type == "single"){

        connect(shooting_timer, SIGNAL(timeout()), this, SLOT(shoot_single()));

    }
    else if(shooting_type == "double"){

        connect(shooting_timer, SIGNAL(timeout()), this, SLOT(shoot_double()));

    }
    else if(shooting_type == "cross"){

        connect(shooting_timer, SIGNAL(timeout()), this, SLOT(shoot_cross()));

    }
    else if(shooting_type == "x"){

        connect(shooting_timer, SIGNAL(timeout()), this, SLOT(shoot_x()));

    }
    else if(shooting_type == "orbit"){
        connect(shooting_timer, SIGNAL(timeout()), this, SLOT(shoot_orbit()));
    }
    else if(shooting_type == "circular"){ // might be?

    }

    if(movement_type == "jump"){

        connect(movement_timer, SIGNAL(timeout()), this, SLOT(jump()));

    }
    else if(movement_type == "left_right"){

        connect(movement_timer, SIGNAL(timeout()), this, SLOT(left_right()));

    }
    else if(movement_type == "left_right_jump"){

        connect(movement_timer, SIGNAL(timeout()), this, SLOT(left_right_jump()));

    }
}
Enemy::~Enemy() {
    shooting_timer->stop();
    movement_timer->stop();

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
    movement_timer->start(1000);
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
    Proyectile *p;
    int randX, randY;

    randX = rand() % 11;
    randY = rand() % 11;

    p = new Proyectile(this, this, damage, this->getX() + sight*30, this->getY()+10, sight*(shot_speed/randX), shot_speed/randY, 1, 4, 1, 1e-5, 0.1, 0);
    proyectiles->push_back(p);
    p->setPos(p->getX(), getV_limit() - p->getY());
    scene->addItem(p);

    sight *= -1;
}

void Enemy::jump() {
    set_velY(getY(), jump_Speed);
}
void Enemy::left_right()
{
    movement_speed *= -1;

    set_velX(getX(), movement_speed);

}
void Enemy::left_right_jump()
{
    set_velY(getY(), jump_Speed);

    movement_speed *= -1;

    set_velX(getX(), movement_speed);
}
