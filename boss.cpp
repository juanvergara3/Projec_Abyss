#include "boss.h"

Boss::Boss(QObject *parent, QGraphicsScene *s, std::string boss, std::list<Proyectile *> *p, float x_, float y_, float vx_, float vy_, float mass_, int radio_, float g_, float K_, float e_, float V_) :
    Entity(parent, x_, y_, vx_, vy_, mass_, radio_, g_, K_, e_, V_)
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

        health = 200;
        damage = 20;
        shot_speed = 15;
        fire_rate = 2500;
        movement_speed = 20;
        jump_Speed = 0;
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
    else if (boss == "beheaded") {
        connect(shooting_timer, SIGNAL(timeout()), this, SLOT(beheaded_shoot()));
        connect(movement_timer, SIGNAL(timeout()), this, SLOT(beheaded_move()));

        name_label->setText("Beheaded Entity");
        description_label->setText("~seeking vengance~");

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

}
Boss::~Boss() {
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
    movement_timer->start(2000);

    scene->addWidget(name_label);
    scene->addWidget(description_label);
    scene->addWidget(health_bar);
}
void Boss::stop() {
    shooting_timer->stop();
    movement_timer->stop(); 
}

void Boss::lamprey_shoot()
{

}
void Boss::priest_shoot()
{

}
void Boss::angel_shoot()
{

}
void Boss::beheaded_shoot()
{

}
void Boss::expelled_shoot()
{

}

void Boss::lamprey_move()
{

}
void Boss::priest_move()
{

}
void Boss::angel_move()
{

}
void Boss::beheaded_move()
{

}
void Boss::expelled_move()
{

}
