#include "player.h"

std::string Player::getName() const
{
    return name;
}

float Player::getHealth() const
{
    return health;
}

bool Player::getAlive() const
{
    return alive;
}

void Player::die() {
    alive = false;
}

Player::Player(QObject *parent, QGraphicsScene *s, std::string name, std::list<Proyectile *> *p, int statPos, float x_, float y_, float vx_, float vy_, float mass_, int radio_, float g_, float K_, float e_, float V_) :
    Entity(parent, x_, y_, vx_, vy_, mass_, radio_, g_, K_, e_, V_)
{
    health = 100;
    max_health = 100;
    damage = 20;
    shot_speed = 30;
    movement_speed = 1.5;
    jump_Speed = 40;
    g = g_;
    g_p = 1;
    r = radio_;
    r_p = 4;
    e = e_;
    shooting_mode = "single";

    sight = 1;
    direction = 0;

    this->name = name;

    alive = true;

    proyectiles = p;

    scene = s;

    init_stats(statPos);
}
Player::~Player() {
    delete health_bar;
    delete name_label;
    delete max_health_label;
    delete damage_label;
    delete shot_speed_label;
    delete movement_speed_label;
    delete jump_speed_label;
}

void Player::shoot() {
    Proyectile *p;

    if(shooting_mode == "single"){
        p = new Proyectile(this, "player", damage, this->getX(), this->getY(), sight*shot_speed, 0, 1, r_p, g_p, 1e-5, 0.1, 0);
        proyectiles->push_back(p);
        p->setPos(p->getX(), getV_limit() - p->getY());
        scene->addItem(p);
    }
    else if(shooting_mode == "double"){
        p = new Proyectile(this, "player", damage, this->getX(), this->getY(), sight*shot_speed, shot_speed/3, 1, r_p, g_p, 1e-5, 0.1, 0);
        proyectiles->push_back(p);
        p->setPos(p->getX(), getV_limit() - p->getY());
        scene->addItem(p);

        p = new Proyectile(this, "player", damage, this->getX(), this->getY(), sight*shot_speed, shot_speed/2, 1, r_p, g_p, 1e-5, 0.1, 0);
        proyectiles->push_back(p);
        p->setPos(p->getX(), getV_limit() - p->getY());
        scene->addItem(p);
    }
    else if(shooting_mode == "triple"){
        p = new Proyectile(this, "player", damage, this->getX(), this->getY(), sight*shot_speed, shot_speed/5, 1, r_p, g_p, 1e-5, 0.1, 0);
        proyectiles->push_back(p);
        p->setPos(p->getX(), getV_limit() - p->getY());
        scene->addItem(p);

        p = new Proyectile(this, "player", damage, this->getX(), this->getY(), sight*shot_speed, shot_speed/3, 1, r_p, g_p, 1e-5, 0.1, 0);
        proyectiles->push_back(p);
        p->setPos(p->getX(), getV_limit() - p->getY());
        scene->addItem(p);

        p = new Proyectile(this, "player", damage, this->getX(), this->getY(), sight*shot_speed, shot_speed/2, 1, r_p, g_p, 1e-5, 0.1, 0);
        proyectiles->push_back(p);
        p->setPos(p->getX(), getV_limit() - p->getY());
        scene->addItem(p);
    }
    else if(shooting_mode == "orbiting"){
        p = new Proyectile(this, this, damage, this->getX() + sight*30, this->getY()+10, sight*(shot_speed/3), shot_speed/5, 1, r_p, g_p, 1e-5, 0.1, 0);
        proyectiles->push_back(p);
        p->setPos(p->getX(), getV_limit() - p->getY());
        scene->addItem(p);
    }
}

void Player::update_stat(std::string s) {

    std::string temp;

    if(s == "name"){

        name_label->setText(name.c_str());
    }
    else if(s == "max_health"){

        temp = "Max Health: " + std::to_string(int(max_health));
        max_health_label->setText(temp.c_str());
    }
    else if(s == "health"){

        health_bar->setValue(health);
        health_bar->update();
    }
    else if (s == "damage"){

        temp = "Damage: " + std::to_string(int(damage));
        damage_label->setText(temp.c_str());
    }
    else if (s == "shot_speed"){

        temp = "Shot Speed: " + std::to_string(int(shot_speed));
        shot_speed_label->setText(temp.c_str());
    }
    else if (s == "movement_speed"){

        temp = "Movement Speed: " + std::to_string(int(movement_speed));
        movement_speed_label->setText(temp.c_str());
    }
    else if (s == "jump_speed"){

        temp = "Jump Speed: " + std::to_string(int(jump_Speed));
        jump_speed_label->setText(temp.c_str());
    }
}
void Player::update_stats(Item *i) {

    health += max_health * i->getHealth();

    if(health > max_health)
        health = max_health;

    max_health *= i->getMax_health();
    damage *= i->getDamage();
    shot_speed *= i->getShot_speed();
    movement_speed *= i->getMovement_speed();
    jump_Speed *= i->getJump_Speed();
    g *= i->getG_player();
    g_p *= i->getG_proyectiles();
    r *= i->getR_player();
    r_p *= i->getR_proyectiles();
    e *= i->getE_player();
    if(shooting_mode != i->getShooting_mode())
        shooting_mode = i->getShooting_mode();

    update_stat("max_health");
    update_stat("health");
    update_stat("damage");
    update_stat("shot_speed");
    update_stat("movement_speed");
    update_stat("jump_speed");

    setG(g);
    setE(e);
    setRadio(r);
    //this->QGraphicsItem::update();
}
void Player::init_stats(int x_reference) {

    health_bar = new QProgressBar;
    health_bar->setRange(0, max_health);
    health_bar->setOrientation(Qt::Vertical);
    health_bar->setValue(max_health);
    health_bar->setTextVisible(false);
    health_bar->setGeometry(x_reference, -120, 20, 120);

    labels.push_back(name_label = new QLabel());
    labels.push_back(max_health_label = new QLabel());
    labels.push_back(damage_label = new QLabel());
    labels.push_back(shot_speed_label = new QLabel());
    labels.push_back(movement_speed_label = new QLabel());
    labels.push_back(jump_speed_label = new QLabel());

    update_stat("name");
    update_stat("max_health");
    update_stat("damage");
    update_stat("shot_speed");
    update_stat("movement_speed");
    update_stat("jump_speed");

    int y = -120;
    for (auto k = labels.begin(); k != labels.end(); k++) {

        (*k)->setFont(QFont("System"));
        (*k)->setGeometry(20 + x_reference, y, (*k)->text().length()*9, 20);
        (*k)->setStyleSheet("QLabel { background-color : white; color : black; }");
        y += 20;
    }

    scene->addWidget(health_bar);
    scene->addWidget(name_label);
    scene->addWidget(max_health_label);
    scene->addWidget(damage_label);
    scene->addWidget(shot_speed_label);
    scene->addWidget(movement_speed_label);
    scene->addWidget(jump_speed_label);
}

void Player::take_damage(int damage)
{
    health -= damage;

    if( health < 0)
        health = 0;

    update_stat("health");
}

void Player::update() {
    this->Entity::update();

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
short Player::getDirection() const {
    return direction;
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
