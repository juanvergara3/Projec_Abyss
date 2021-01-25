#include "player.h"

int Player::getStatPos() const
{
    return statPos;
}

Player::Player(QObject *parent, QGraphicsScene *s, std::string name, std::list<Proyectile *> *p, int statPos, float x_, float y_, int player) :
    Entity(parent, x_, y_, 0, 0, 20, 12, 16, 4, 1e-5, 0.1, 0), statPos(statPos)
{

    health = 100;
    max_health = 100;
    damage = 20;
    shot_speed = 30;
    movement_speed = 1.5;
    jump_Speed = 40;
    g = 4;
    g_p = 1;
    r_p = 4;
    e = 0.1;
    shooting_mode = "single";

    sight = 1;
    direction = 0;

    this->name = name;

    alive = true;

    proyectiles = p;

    scene = s;

    i = 0;
    j = 0;

    if(player == 1)
        sprite = new QPixmap(":/Assets/Sprites/entities/p1-sprite.png");
    else if(player == 2)
        sprite = new QPixmap(":/Assets/Sprites/entities/p2-sprite.png");

    sprite_timer = new QTimer();
    connect(sprite_timer, SIGNAL(timeout()), this, SLOT(update_sprite()));
   sprite_timer->start(80);

    init_stats(statPos);
}

Player::Player(QObject *parent, QGraphicsScene *s, std::list<Proyectile *> *p, int x, int y, int statPos, std::string name, float max_health, float health, float damage, float shot_speed, float movement_speed, float jump_Speed, float g, float g_p, float w, float h, float r_p, float e, std::string shooting_mode)
    :Entity(parent, x, y, 0, 0, 20, w, h, g, 1e-5, e, 0), statPos(statPos)
{
    this->health = health;
    this->max_health = max_health;
    this->damage = damage;
    this->shot_speed = shot_speed;
    this->movement_speed = movement_speed;
    this->jump_Speed = jump_Speed;
    this->g = g;
    this->g_p = g_p;
    this->r_p = r_p;
    this->e = e;
    this->shooting_mode = shooting_mode;

    sight = 1;
    direction = 0;

    this->name = name;

    if(health <= 0)
        alive = false;
    else
        alive = true;

    proyectiles = p;
    scene = s;

    i = 0;
    j = 0;
    sprite = new QPixmap(":/Assets/Sprites/entities/p2-sprite.png");

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
    delete sprite;
    delete sprite_timer;
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

    max_health += max_health*i->getMax_health();
    damage += damage*i->getDamage();
    shot_speed += shot_speed*i->getShot_speed();

    if(i->getMovement_speed() == -1)
        movement_speed *= -1;
    else
        movement_speed += movement_speed*i->getMovement_speed();

    jump_Speed += jump_Speed*i->getJump_Speed();

    if(i->getG_player() == -1)
        g *= -1;
    else if(i->getG_player() == 0)
        g = 0;
    else if(i->getG_player() != 1)
        g += g*i->getG_player();

    if(i->getG_proyectiles() == -1)
        g_p *= -1;
    else if(i->getG_proyectiles() == 0)
        g_p = 0;
    else if(i->getG_proyectiles() != 1)
        g_p += g_p*i->getG_proyectiles();

    setWidth(getWidth()+(getWidth()*i->getR_player()));
    setHeight(getHeight()+(getHeight()*i->getR_player()));

    r_p += r_p*i->getR_proyectiles();
    e += e*i->getE_player();

    if(i->getShooting_mode() != "single")
        shooting_mode = i->getShooting_mode();

    update_stat("max_health");
    update_stat("health");
    update_stat("damage");
    update_stat("shot_speed");
    update_stat("movement_speed");
    update_stat("jump_speed");

    setG(g);
    setE(e);
    this->QGraphicsItem::update();
}
void Player::init_stats(int x_reference) {

    health_bar = new QProgressBar;
    health_bar->setRange(0, max_health);
    health_bar->setOrientation(Qt::Vertical);
    health_bar->setValue(health);
    health_bar->setTextVisible(false);
    health_bar->setGeometry(x_reference, -120, 20, 120);
    health_bar->setStyleSheet("QProgressBar { border: rgba(255, 255, 255, 0); border-radius: 0px; background-color: #212121; } QProgressBar::chunk { background-color: #34fa4b; height: 10px; margin: 0.5px;}");

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
        (*k)->setStyleSheet("QLabel { background-color : rgba(255, 255, 255, 0); color : white; }");
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

void Player::update_sprite() {

    if(direction != 0)
        if(i == 96)
            i = 12;
        else
            i += 12;
    else
        i = 0;

    this->QGraphicsItem::update(-this->getWidth()/2, -this->getHeight()/2, this->getWidth(), this->getHeight());

}
float Player::getMovement_speed() const{
    return movement_speed;
}
float Player::getJump_Speed() const{
    return jump_Speed;
}

QRectF Player::boundingRect() const {
        return QRectF(-this->getWidth()/2, -this->getHeight()/2, this->getWidth(), this->getHeight());
}
void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawPixmap(-this->getWidth()/2, -this->getHeight()/2, sprite->scaledToHeight(this->getHeight()), i, j, 12, 15);
    //painter->drawRect(boundingRect());
}

void Player::addDirection(int d) {

    if (d == direction)
        return;

    direction += d;

    if (0 != direction) {
        if (-1 == direction)
            setTransform(QTransform().scale(-1, 1));
        else
            setTransform(QTransform());
    }
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

float Player::getMax_health() const
{
    return max_health;
}

float Player::getDamage() const
{
    return damage;
}

float Player::getShot_speed() const
{
    return shot_speed;
}

float Player::getG_p() const
{
    return g_p;
}

float Player::getR_p() const
{
    return r_p;
}

std::string Player::getShooting_mode() const
{
    return shooting_mode;
}
