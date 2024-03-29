#include "enemy.h"

Enemy::Enemy(QObject *parent, QGraphicsScene *s, std::string shooting_type, std::string movement_type, std::list<Proyectile *> *p, int fire_rate, int movement_rate, float movement_speed, float jump_speed, int dificulty, float x, float y, int w, int h, float g, std::string sprite) :
    Entity(parent, x, y, 0, 0, 10, w, h, g, 1e-4, 0.2, 0), fire_rate(fire_rate), movement_rate(movement_rate), movement_speed(movement_speed), jump_Speed(jump_speed)
{

    shooting_timer = new QTimer;
    movement_timer = new QTimer;

    this->sprite = new QPixmap(sprite.c_str());

    scene = s;
    proyectiles = p;
    sight = -1;

    srand(time(NULL));

    if(dificulty == 1){
        health = 60;
        damage = 10;
        shot_speed = 15;
    }
    else if(dificulty == 2){
        health = 90;
        damage = 30;
        shot_speed = 25;
    }
    else if(dificulty == 3){
        health = 120;
        damage = 40;
        shot_speed = 30;
    }
    else{
        health = 0;
        damage = 0;
        shot_speed = 0;
    }

    if(shooting_type == "single")
        connect(shooting_timer, SIGNAL(timeout()), this, SLOT(shoot_single()));

    else if(shooting_type == "double")
        connect(shooting_timer, SIGNAL(timeout()), this, SLOT(shoot_double()));

    else if(shooting_type == "cross")
        connect(shooting_timer, SIGNAL(timeout()), this, SLOT(shoot_cross()));

    else if(shooting_type == "x")
        connect(shooting_timer, SIGNAL(timeout()), this, SLOT(shoot_x()));

    else if(shooting_type == "orbit")
        connect(shooting_timer, SIGNAL(timeout()), this, SLOT(shoot_orbit()));

    if(movement_type == "jump")
        connect(movement_timer, SIGNAL(timeout()), this, SLOT(jump()));

    else if(movement_type == "left_right")
        connect(movement_timer, SIGNAL(timeout()), this, SLOT(left_right()));

    else if(movement_type == "left_right_jump")
        connect(movement_timer, SIGNAL(timeout()), this, SLOT(left_right_jump()));
}
Enemy::~Enemy() {
    shooting_timer->stop();
    movement_timer->stop();

    delete shooting_timer;
    delete movement_timer;
    delete sprite;
}

QRectF Enemy::boundingRect() const { // overloaded method
        return QRectF(-this->getWidth()/2, -this->getHeight()/2, this->getWidth(), this->getHeight());
}
void Enemy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) { // overloaded method
    painter->drawPixmap(-this->getWidth()/2, -this->getHeight()/2, sprite->scaledToHeight(this->getHeight()), 0, 0, this->getWidth(), this->getHeight());
    //painter->drawRect(boundingRect());
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

void Enemy::init() { // starts the enemy's fuctions (shooting and moving)
    shooting_timer->start(fire_rate);
    movement_timer->start(movement_rate);
}
void Enemy::stop() { // stops the enemy's fuctions (shooting and moving)
    shooting_timer->stop();
    movement_timer->stop();
}

void Enemy::shoot_single() { // shoots a single projectile on sight
    Proyectile *p = new Proyectile(this, "enemy", damage, this->getX(), this->getY(), sight*shot_speed, 0, 1, 4, 1, 1e-5, 0.1, 0);

    proyectiles->push_back(p);
    p->setPos(p->getX(), getV_limit() - p->getY());
    scene->addItem(p);
}
void Enemy::shoot_double() { // shoots two projectiles (left and right)
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
void Enemy::shoot_cross() { // shoots 4 projectiles on a cross pattern
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
void Enemy::shoot_x() { // shoots 4 projectiles on an X pattern
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
void Enemy::shoot_orbit() { // shoots a projectile that orbits this
    Proyectile *p;
    int randX, randY;

    randX = rand() % 11;
    randY = rand() % 11;

    p = new Proyectile(this, "enemy",this, damage, this->getX() + sight*30, this->getY()+10, sight*(shot_speed/randX), shot_speed/randY, 1, 4, 1, 1e-5, 0.1, 0);
    proyectiles->push_back(p);
    p->setPos(p->getX(), getV_limit() - p->getY());
    scene->addItem(p);

    sight *= -1;
}

void Enemy::jump() { // a simple jump
    set_velY(getY(), jump_Speed);
}
void Enemy::left_right() { //moves left to right
    movement_speed *= -1;

    set_velX(getX(), movement_speed);

}
void Enemy::left_right_jump() { //moves left to right but also jumps
    set_velY(getY(), jump_Speed);

    movement_speed *= -1;

    set_velX(getX(), movement_speed);
}
