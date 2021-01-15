#include "boss.h"

Boss::Boss(QObject *parent, QGraphicsScene *s, std::string boss, std::list<Proyectile *> *p, float x_, float y_, float vx_, float vy_, float mass_, int width_, int height_, float g_, float K_, float e_, float V_) :
    Entity(parent, x_, y_, vx_, vy_, mass_, width_, height_, g_, K_, e_, V_)
{
    shooting_timer = new QTimer;
    movement_timer = new QTimer;

    health_bar = new QProgressBar;

    name_label = new QLabel;
    description_label = new QLabel;

    scene = s;
    proyectiles = p;
    sight = 1;

    if(boss == "lamprey"){
        connect(shooting_timer, SIGNAL(timeout()), this, SLOT(lamprey_shoot()));
        connect(movement_timer, SIGNAL(timeout()), this, SLOT(lamprey_move()));

        name_label->setText("Insatiable Lamprey");
        description_label->setText("~Lurking Beast~");

        health = 400;
        damage = 20;
        shot_speed = 25;
        fire_rate = 500;
        movement_speed = 20;
        jump_Speed = 30;
    }
    else if (boss == "priest") {
        connect(shooting_timer, SIGNAL(timeout()), this, SLOT(priest_shoot()));
        connect(movement_timer, SIGNAL(timeout()), this, SLOT(priest_move()));

        name_label->setText("Tainted High Priest");
        description_label->setText("~Corrupted by Malice~");

        health = 200;
        damage = 20;
        shot_speed = 15;
        fire_rate = 2500;
        movement_speed = 20;
        jump_Speed = 0;
    }
    else if (boss == "angel") {
        connect(shooting_timer, SIGNAL(timeout()), this, SLOT(angel_shoot()));
        connect(movement_timer, SIGNAL(timeout()), this, SLOT(angel_move()));

        name_label->setText("Rotting Angel");
        description_label->setText("~Fallen and Devoured~");

        health = 200;
        damage = 20;
        shot_speed = 15;
        fire_rate = 2500;
        movement_speed = 20;
        jump_Speed = 0;
    }
    else if (boss == "expelled") {
        connect(shooting_timer, SIGNAL(timeout()), this, SLOT(expelled_shoot()));
        connect(movement_timer, SIGNAL(timeout()), this, SLOT(expelled_move()));

        name_label->setText("The Expelled One");
        description_label->setText("~Hatred Incarnation~");

        health = 200;
        damage = 20;
        shot_speed = 15;
        fire_rate = 2500;
        movement_speed = 20;
        jump_Speed = 0;
    }

    health_bar->setRange(0, health);
    health_bar->setValue(health);
    health_bar->setTextVisible(false);
    health_bar->setGeometry(20, 770, 300, 20);
    health_bar->update();

    name_label->setFont(QFont("System"));
    name_label->setGeometry(20, 730, name_label->text().length()*8, 20);
    name_label->setStyleSheet("QLabel { background-color : white; color : black; }");

    description_label->setFont(QFont("System"));
    description_label->setGeometry(20, 750, description_label->text().length()*8, 20);
    description_label->setStyleSheet("QLabel { background-color : white; color : black; }");

    name_label->setVisible(false);
    description_label->setVisible(false);
    health_bar->setVisible(false);

    scene->addWidget(name_label);
    scene->addWidget(description_label);
    scene->addWidget(health_bar);

}
Boss::~Boss() {
    shooting_timer->stop();
    movement_timer->stop();

    disconnect(movement_timer,0,0,0);
    disconnect(shooting_timer,0,0,0);

    proyectiles = nullptr;
    scene = nullptr;

    delete shooting_timer;
    delete movement_timer;
    delete name_label;
    delete description_label;
    delete health_bar;
}

int Boss::getDamage() const {
    return damage;
}
int Boss::getHealth() const {
    return health;
}

void Boss::take_damage(int damage) {
    health -= damage;

    if(health < 0)
        health = 0;

    health_bar->setValue(health);
    health_bar->update();
}

void Boss::init() {
    shooting_timer->start(fire_rate);
    movement_timer->start(1500);

    name_label->setVisible(true);
    description_label->setVisible(true);
    health_bar->setVisible(true);
}
void Boss::stop() {
    shooting_timer->stop();
    movement_timer->stop(); 

    name_label->setVisible(false);
    description_label->setVisible(false);
    health_bar->setVisible(false);
}

void Boss::lamprey_shoot()
{
    Proyectile *p;

    p = new Proyectile(nullptr, "boss", damage, this->getX(), this->getY(), -1*shot_speed, shot_speed/5, 1, 4, 0.5, 1e-5, 0.1, 0);
    proyectiles->push_back(p);
    p->setPos(p->getX(), getV_limit() - p->getY());
    scene->addItem(p);

    p = new Proyectile(nullptr, "boss", damage, this->getX(), this->getY(), -1*shot_speed, shot_speed/3, 1, 4, 0.5, 1e-5, 0.1, 0);
    proyectiles->push_back(p);
    p->setPos(p->getX(), getV_limit() - p->getY());
    scene->addItem(p);

    p = new Proyectile(nullptr, "boss", damage, this->getX(), this->getY(), -1*shot_speed, shot_speed/2, 1, 4, 0.5, 1e-5, 0.1, 0);
    proyectiles->push_back(p);
    p->setPos(p->getX(), getV_limit() - p->getY());
    scene->addItem(p);
}
void Boss::priest_shoot()
{

}
void Boss::angel_shoot()
{

}
void Boss::expelled_shoot()
{

}

void Boss::lamprey_move()
{
    sight *= -1;
    set_velY(getY(), jump_Speed*sight);
}
void Boss::priest_move()
{

}
void Boss::angel_move()
{

}
void Boss::expelled_move()
{

}
