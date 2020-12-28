#include "player.h"

Player::Player(QObject *parent, QGraphicsScene *s, float x_, float y_, float vx_, float vy_, float mass_, int radio_, float g_, float K_, float e_, float V_) :
    Entity(parent, x_, y_, vx_, vy_, mass_, radio_, g_, K_, e_, V_) , v_limit(720), scene(s), h_limit(1280)
{
    health = 100;
    damage = 20;
    shot_speed = 30;
    movement_speed = 1;
    jump_Speed = 40;
    sight = 1;
    direction = 0;

    name = "P1"; //constructor

    init_stats();
}

Proyectile *Player::shoot() {
    Proyectile *p = new Proyectile(this, damage, this->getX(), this->getY(), sight*shot_speed, 0, 1, 4, 1, 1e-5, 0.1, 0);

    scene->addItem(p);
    //p->setPos(p->getX(), 720 - p->getY());

    return p;
}

void Player::update_stat(std::string s) {

    std::string temp;

    if(s == "name"){

        name_label->setText(name.c_str());
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
void Player::init_stats() {

    health_bar = new QProgressBar;
    health_bar->setRange(0, health);
    health_bar->setOrientation(Qt::Vertical);
    health_bar->setGeometry(0, 0,20, health);
    health_bar->setValue(health);
    health_bar->setTextVisible(false);

    labels.push_back(name_label = new QLabel());
    labels.push_back(damage_label = new QLabel());
    labels.push_back(shot_speed_label = new QLabel());
    labels.push_back(movement_speed_label = new QLabel());
    labels.push_back(jump_speed_label = new QLabel());

    update_stat("name");
    update_stat("damage");
    update_stat("shot_speed");
    update_stat("movement_speed");
    update_stat("jump_speed");

    int y = 0;
    for (auto k = labels.begin(); k != labels.end(); k++) {

        (*k)->setFont(QFont("System"));
        (*k)->setGeometry(20, y, (*k)->text().length()*8, 20);
        y += 20;
    }

    scene->addWidget(health_bar);
    scene->addWidget(name_label);
    scene->addWidget(damage_label);
    scene->addWidget(shot_speed_label);
    scene->addWidget(movement_speed_label);
    scene->addWidget(jump_speed_label);
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
