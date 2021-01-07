#include "player.h"

Player::Player(QObject *parent, QGraphicsScene *s, std::string name, int statPos, float x_, float y_, float vx_, float vy_, float mass_, int radio_, float g_, float K_, float e_, float V_) :
    Entity(parent, x_, y_, vx_, vy_, mass_, radio_, g_, K_, e_, V_)
{
    health = 100;
    max_health = 100;
    damage = 20;
    shot_speed = 30;
    movement_speed = 1;
    jump_Speed = 40;
    sight = 1;
    direction = 0;

    this->name = name;

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

Proyectile *Player::shoot() {
    Proyectile *p = new Proyectile(this, "player",damage, this->getX(), this->getY(), sight*shot_speed, 0, 1, 4, 1, 1e-5, 0.1, 0);

    p->setPos(p->getX(), getV_limit() - p->getY());
    scene->addItem(p);

    return p;
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
void Player::update_stat(std::string s, int value) {

    if(s == "max_health"){

        max_health += value;
    }
    else if(s == "health"){

        health += value;

        if(health > max_health)
            health = max_health;
    }
    else if (s == "damage"){

        damage += value;
    }
    else if (s == "shot_speed"){

        shot_speed += value;
    }
    else if (s == "movement_speed"){

        movement_speed += value;
    }
    else if (s == "jump_speed"){

        jump_Speed += value;
    }

    update_stat(s);
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
        (*k)->setGeometry(20 + x_reference, y, (*k)->text().length()*8, 20);
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
