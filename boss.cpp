#include "boss.h"

Boss::Boss(QObject *parent, QGraphicsScene *s, std::string boss, std::list<Proyectile *> *p, float x_, float y_, float vx_, float vy_, float mass_, int width_, int height_, float g_, float K_, float e_, float V_) :
    Entity(parent, x_, y_, vx_, vy_, mass_, width_, height_, g_, K_, e_, V_)
{
    shooting_timer = new QTimer;
    movement_timer = new QTimer;

    health_bar = new QProgressBar;

    name_label = new QLabel;
    description_label = new QLabel;

    sprite = nullptr;

    scene = s;
    proyectiles = p;
    sight = 1;

    if(boss == "lamprey"){
        connect(shooting_timer, SIGNAL(timeout()), this, SLOT(lamprey_shoot()));
        connect(movement_timer, SIGNAL(timeout()), this, SLOT(lamprey_move()));

        name_label->setText("Insatiable Lamprey");
        description_label->setText("~Lurking Beast~");

        health = 800;
        damage = 20;
        shot_speed = 25;
        fire_rate = 500;
        movement_speed = 20;
        jump_Speed = 30;
    }
    else if (boss == "priest") {
        connect(shooting_timer, SIGNAL(timeout()), this, SLOT(priest_shoot()));

        sprite = new QPixmap(":/Assets/Sprites/entities/priest_sprite.png");

        name_label->setText("Tainted High Priest");
        description_label->setText("~Corrupted by Malice~");

        health = 800;
        damage = 40;
        shot_speed = 25;
        fire_rate = 1000; // 300 worked fine before adding the music
        movement_speed = 0;
        jump_Speed = 0;
    }
    else if (boss == "expelled") {
        connect(shooting_timer, SIGNAL(timeout()), this, SLOT(expelled_shoot()));
        connect(movement_timer, SIGNAL(timeout()), this, SLOT(expelled_move()));

        name_label->setText("The Expelled One");
        description_label->setText("~Hatred Incarnated~");

        health = 400;
        damage = 20;
        shot_speed = 15;
        fire_rate = 1200;
        movement_speed = 20;
        jump_Speed = 0;
    }

    health_bar->setRange(0, health);
    health_bar->setValue(health);
    health_bar->setTextVisible(false);
    health_bar->setGeometry(20, 770, 300, 20);
    health_bar->update();
    health_bar->setStyleSheet("QProgressBar { border: rgba(255, 255, 255, 0); border-radius: 0px; background-color: #212121;} QProgressBar::chunk { background-color: #fa3434;}");

    name_label->setFont(QFont("System"));
    name_label->setGeometry(20, 730, name_label->text().length()*8, 20);
    name_label->setStyleSheet("QLabel { background-color : rgba(255, 255, 255, 0); color : white; }");

    description_label->setFont(QFont("System"));
    description_label->setGeometry(20, 750, description_label->text().length()*8, 20);
    description_label->setStyleSheet("QLabel { background-color : rgba(255, 255, 255, 0); color : white; }");

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
    delete sprite;
}

QRectF Boss::boundingRect() const {
        return QRectF(-this->getWidth()/2, -this->getHeight()/2, this->getWidth(), this->getHeight());
}
void Boss::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    if(sprite != nullptr)
        painter->drawPixmap(-this->getWidth()/2, -this->getHeight()/2, sprite->scaledToHeight(this->getHeight()), 0, 0, this->getWidth(), this->getHeight());
    else{
        painter->setBrush(Qt::white);
        painter->drawRect(boundingRect());
    }
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

void Boss::lamprey_shoot() {
    Proyectile *p;

    int s1, s2, s3;

    s1 = -6 + (rand() % static_cast<int>(6 - (-6) + 1));
    s2 = -6 + (rand() % static_cast<int>(6 - (-6)  + 1));
    s3 = -6 + (rand() % static_cast<int>(6 - (-6)  + 1));

    p = new Proyectile(nullptr, "boss", damage, this->getX(), this->getY(), -1*shot_speed, shot_speed/s1, 1, 4, 0.5, 1e-5, 0.1, 0);
    proyectiles->push_back(p);
    p->setPos(p->getX(), getV_limit() - p->getY());
    scene->addItem(p);

    p = new Proyectile(nullptr, "boss", damage, this->getX(), this->getY(), -1*shot_speed, shot_speed/s2, 1, 4, 0.5, 1e-5, 0.1, 0);
    proyectiles->push_back(p);
    p->setPos(p->getX(), getV_limit() - p->getY());
    scene->addItem(p);

    p = new Proyectile(nullptr, "boss", damage, this->getX(), this->getY(), -1*shot_speed, shot_speed/s3, 1, 4, 0.5, 1e-5, 0.1, 0);
    proyectiles->push_back(p);
    p->setPos(p->getX(), getV_limit() - p->getY());
    scene->addItem(p);
}
void Boss::priest_shoot() {
    Proyectile *p;
    int randX, randY;

    randX = rand() % 8;
    randY = -8 + (rand() % static_cast<int>(8 - (-8) + 1));
    p = new Proyectile(nullptr, this, damage, this->getX()+sight*80, this->getY(), sight*(shot_speed/randX), shot_speed/randY, 0.5, 6, 1, 1e-6, 0.1, 0);
    proyectiles->push_back(p);
    p->setPos(p->getX(), getV_limit() - p->getY());
    scene->addItem(p);

    randX = rand() % 8;
    randY = -8 + (rand() % static_cast<int>(8 - (-8) + 1));
    p = new Proyectile(nullptr, this, damage, this->getX()+sight*80, this->getY(), sight*(shot_speed/randX), shot_speed/randY, 0.5, 6, 1, 1e-6, 0.1, 0);
    proyectiles->push_back(p);
    p->setPos(p->getX(), getV_limit() - p->getY());
    scene->addItem(p);

    randX = rand() % 8;
    randY = -8 + (rand() % static_cast<int>(8 - (-8) + 1));
    p = new Proyectile(nullptr, this, damage, this->getX()+sight*80, this->getY(), sight*(shot_speed/randX), shot_speed/randY, 0.5, 6, 1, 1e-6, 0.1, 0);
    proyectiles->push_back(p);
    p->setPos(p->getX(), getV_limit() - p->getY());
    scene->addItem(p);

    sight *= -1;
}
void Boss::expelled_shoot() {

    int g, r;

    g = -4 + (rand() % static_cast<int>(4 - (-4) + 1));
    r = 3 + (rand() % static_cast<int>(6 - 3 + 1));

    damage = 5 + (rand() % static_cast<int>(50 - 5 + 1));
    shot_speed = 10 + (rand() % static_cast<int>(20 - 10 + 1));

    int mode = 1 + (rand() % static_cast<int>(9 - 1 + 1)); //min + (rand() % static_cast<int>(max - min + 1))
    Proyectile *p;

    if(mode == 1){ // x
        p = new Proyectile(nullptr, "boss", damage, this->getX(), this->getY(), shot_speed, shot_speed, 1, 4, 1, 1e-5, 0.1, 0);
        proyectiles->push_back(p);
        p->setPos(p->getX(), getV_limit() - p->getY());
        scene->addItem(p);

        p = new Proyectile(nullptr, "boss", damage, this->getX(), this->getY(), -1*(shot_speed), -1*(shot_speed), 1, 4, 1, 1e-5, 0.1, 0);
        proyectiles->push_back(p);
        p->setPos(p->getX(), getV_limit() - p->getY());
        scene->addItem(p);

        p = new Proyectile(nullptr, "boss", damage, this->getX(), this->getY(), -1*shot_speed, shot_speed, 1, 4, 1, 1e-5, 0.1, 0);
        proyectiles->push_back(p);
        p->setPos(p->getX(), getV_limit() - p->getY());
        scene->addItem(p);

        p = new Proyectile(this, "enemy", damage, this->getX(), this->getY(), shot_speed, -1*shot_speed, 1, 4, 1, 1e-5, 0.1, 0);
        proyectiles->push_back(p);
        p->setPos(p->getX(), getV_limit() - p->getY());
        scene->addItem(p);
    }
    else if (mode == 2) { // triple orbital
        p = new Proyectile(nullptr, this, damage, this->getX(), this->getY(), sight*shot_speed/3, shot_speed/15, 1, r, g, 1e-5, 0.1, 0);
        proyectiles->push_back(p);
        p->setPos(p->getX(), getV_limit() - p->getY());
        scene->addItem(p);

        p = new Proyectile(nullptr, this, damage, this->getX(), this->getY(), -sight*shot_speed/3, shot_speed/9, 1, r, g, 1e-5, 0.1, 0);
        proyectiles->push_back(p);
        p->setPos(p->getX(), getV_limit() - p->getY());
        scene->addItem(p);

        p = new Proyectile(nullptr, this, damage, this->getX(), this->getY(), sight*shot_speed/3, shot_speed/6, 1, r, g, 1e-5, 0.1, 0);
        proyectiles->push_back(p);
        p->setPos(p->getX(), getV_limit() - p->getY());
        scene->addItem(p);
    }
    else if (mode == 3) { // triple double orbital
        p = new Proyectile(nullptr, this, damage, this->getX()+80, this->getY(), shot_speed/3, shot_speed/15, 1, r, g, 1e-5, 0.1, 0);
        proyectiles->push_back(p);
        p->setPos(p->getX(), getV_limit() - p->getY());
        scene->addItem(p);

        p = new Proyectile(nullptr, this, damage, this->getX()+80, this->getY(), shot_speed/3, shot_speed/9, 1, r, g, 1e-5, 0.1, 0);
        proyectiles->push_back(p);
        p->setPos(p->getX(), getV_limit() - p->getY());
        scene->addItem(p);

        p = new Proyectile(nullptr, this, damage, this->getX()+80, this->getY(), shot_speed/3, shot_speed/6, 1, r, g, 1e-5, 0.1, 0);
        proyectiles->push_back(p);
        p->setPos(p->getX(), getV_limit() - p->getY());

        scene->addItem(p);
        p = new Proyectile(nullptr, this, damage, this->getX()-80, this->getY(), -1*shot_speed/3, shot_speed/15, 1, r, g, 1e-5, 0.1, 0);
        proyectiles->push_back(p);
        p->setPos(p->getX(), getV_limit() - p->getY());
        scene->addItem(p);

        p = new Proyectile(nullptr, this, damage, this->getX()-80, this->getY(), -1*shot_speed/3, shot_speed/9, 1, r, g, 1e-5, 0.1, 0);
        proyectiles->push_back(p);
        p->setPos(p->getX(), getV_limit() - p->getY());
        scene->addItem(p);

        p = new Proyectile(nullptr, this, damage, this->getX()-80, this->getY(), -1*shot_speed/3, shot_speed/6, 1, r, g, 1e-5, 0.1, 0);
        proyectiles->push_back(p);
        p->setPos(p->getX(), getV_limit() - p->getY());
        scene->addItem(p);
    }
    else if (mode == 4) { // cross
        p = new Proyectile(nullptr, "boss", damage, this->getX(), this->getY(), 0, shot_speed, 1, 4, 1, 1e-5, 0.1, 0);
        proyectiles->push_back(p);
        p->setPos(p->getX(), getV_limit() - p->getY());
        scene->addItem(p); //up

        p = new Proyectile(nullptr, "boss", damage, this->getX(), this->getY(), 0, -1*shot_speed, 1, 4, 1, 1e-5, 0.1, 0);
        proyectiles->push_back(p);
        p->setPos(p->getX(), getV_limit() - p->getY());
        scene->addItem(p); //down

        p = new Proyectile(nullptr, "boss", damage, this->getX(), this->getY(), shot_speed, 0, 1, 4, 1, 1e-5, 0.1, 0);
        proyectiles->push_back(p);
        p->setPos(p->getX(), getV_limit() - p->getY());
        scene->addItem(p); //right

        p = new Proyectile(nullptr, "boss", damage, this->getX(), this->getY(),-1*shot_speed, 0, 1, 4, 1, 1e-5, 0.1, 0);
        proyectiles->push_back(p);
        p->setPos(p->getX(), getV_limit() - p->getY());
        scene->addItem(p); //left
    }
    else if (mode == 5) { // all
        p = new Proyectile(nullptr, "boss", damage, this->getX(), this->getY(), shot_speed, shot_speed, 1, 4, 1, 1e-5, 0.1, 0);
        proyectiles->push_back(p);
        p->setPos(p->getX(), getV_limit() - p->getY());
        scene->addItem(p);

        p = new Proyectile(nullptr, "boss", damage, this->getX(), this->getY(), -1*(shot_speed), -1*(shot_speed), 1, 4, 1, 1e-5, 0.1, 0);
        proyectiles->push_back(p);
        p->setPos(p->getX(), getV_limit() - p->getY());
        scene->addItem(p);

        p = new Proyectile(nullptr, "boss", damage, this->getX(), this->getY(), -1*shot_speed, shot_speed, 1, 4, 1, 1e-5, 0.1, 0);
        proyectiles->push_back(p);
        p->setPos(p->getX(), getV_limit() - p->getY());
        scene->addItem(p);

        p = new Proyectile(this, "enemy", damage, this->getX(), this->getY(), shot_speed, -1*shot_speed, 1, 4, 1, 1e-5, 0.1, 0);
        proyectiles->push_back(p);
        p->setPos(p->getX(), getV_limit() - p->getY());
        scene->addItem(p);

        p = new Proyectile(nullptr, "boss", damage, this->getX(), this->getY(), shot_speed, shot_speed/5, 1, r, g, 1e-5, 0.1, 0);
        proyectiles->push_back(p);
        p->setPos(p->getX(), getV_limit() - p->getY());
        scene->addItem(p);

        p = new Proyectile(nullptr, "boss", damage, this->getX(), this->getY(), shot_speed, shot_speed/3, 1, r, g, 1e-5, 0.1, 0);
        proyectiles->push_back(p);
        p->setPos(p->getX(), getV_limit() - p->getY());
        scene->addItem(p);

        p = new Proyectile(nullptr, "boss", damage, this->getX(), this->getY(), shot_speed, shot_speed/2, 1, r, g, 1e-5, 0.1, 0);
        proyectiles->push_back(p);
        p->setPos(p->getX(), getV_limit() - p->getY());

        scene->addItem(p);
        p = new Proyectile(nullptr, "boss", damage, this->getX(), this->getY(), -1*shot_speed, shot_speed/5, 1, r, g, 1e-5, 0.1, 0);
        proyectiles->push_back(p);
        p->setPos(p->getX(), getV_limit() - p->getY());
        scene->addItem(p);

        p = new Proyectile(nullptr, "boss", damage, this->getX(), this->getY(), -1*shot_speed, shot_speed/3, 1, r, g, 1e-5, 0.1, 0);
        proyectiles->push_back(p);
        p->setPos(p->getX(), getV_limit() - p->getY());
        scene->addItem(p);

        p = new Proyectile(nullptr, "boss", damage, this->getX(), this->getY(), -1*shot_speed, shot_speed/2, 1, r, g, 1e-5, 0.1, 0);
        proyectiles->push_back(p);
        p->setPos(p->getX(), getV_limit() - p->getY());
        scene->addItem(p);
    }
    else if (mode == 6) { // orbital bomb
        //int randX, randY;

        p = new Proyectile(nullptr, this, damage, this->getX()+80, this->getY(), shot_speed/3, shot_speed/3, 1, 4, 1, 1e-5, 0.1, 0);
        proyectiles->push_back(p);
        p->setPos(p->getX(), getV_limit() - p->getY());
        scene->addItem(p);

        p = new Proyectile(nullptr, this, damage, this->getX()-80, this->getY(), -1*(shot_speed)/3, -1*(shot_speed)/3, 1, 4, 1, 1e-5, 0.1, 0);
        proyectiles->push_back(p);
        p->setPos(p->getX(), getV_limit() - p->getY());
        scene->addItem(p);

        p = new Proyectile(nullptr, this, damage, this->getX()-80, this->getY(), -1*shot_speed/3, 1*shot_speed/3, 1, 4, 1, 1e-5, 0.1, 0);
        proyectiles->push_back(p);
        p->setPos(p->getX(), getV_limit() - p->getY());
        scene->addItem(p);

        p = new Proyectile(this, this, damage, this->getX()+80, this->getY(), 1*shot_speed/3, -1*shot_speed/3, 1, 4, 1, 1e-5, 0.1, 0);
        proyectiles->push_back(p);
        p->setPos(p->getX(), getV_limit() - p->getY());
        scene->addItem(p);

        p = new Proyectile(nullptr, this, damage, this->getX()+80, this->getY(), shot_speed/3, shot_speed/15, 1, r, g, 1e-5, 0.1, 0);
        proyectiles->push_back(p);
        p->setPos(p->getX(), getV_limit() - p->getY());
        scene->addItem(p);

        p = new Proyectile(nullptr, this, damage, this->getX()+80, this->getY(), shot_speed/3, shot_speed/9, 1, r, g, 1e-5, 0.1, 0);
        proyectiles->push_back(p);
        p->setPos(p->getX(), getV_limit() - p->getY());
        scene->addItem(p);

        p = new Proyectile(nullptr, this, damage, this->getX()+80, this->getY(), shot_speed/3, shot_speed/6, 1, r, g, 1e-5, 0.1, 0);
        proyectiles->push_back(p);
        p->setPos(p->getX(), getV_limit() - p->getY());

        scene->addItem(p);
        p = new Proyectile(nullptr, this, damage, this->getX()-80, this->getY(), -1*shot_speed/3, shot_speed/15, 1, r, g, 1e-5, 0.1, 0);
        proyectiles->push_back(p);
        p->setPos(p->getX(), getV_limit() - p->getY());
        scene->addItem(p);

        p = new Proyectile(nullptr, this, damage, this->getX()-80, this->getY(), -1*shot_speed/3, shot_speed/9, 1, r, g, 1e-5, 0.1, 0);
        proyectiles->push_back(p);
        p->setPos(p->getX(), getV_limit() - p->getY());
        scene->addItem(p);

        p = new Proyectile(nullptr, this, damage, this->getX()-80, this->getY(), -1*shot_speed/3, shot_speed/6, 1, r, g, 1e-5, 0.1, 0);
        proyectiles->push_back(p);
        p->setPos(p->getX(), getV_limit() - p->getY());
        scene->addItem(p);
    }
    else if (mode == 7) { //none
        // Nothing here but chickens !!
    }
    else if (mode == 8) { //none
        // They should be somewhere around here :thinking:
    }
    else if (mode == 9) { //none
        //        COT   cot COOOT!
        //    cot
        // COT
        //        ,~.
        //     ,-'__ `-,
        //    {,-'  `. }              ,')
        //   ,( a )   `-.__         ,',')~,
        //  <=.) (         `-.__,==' ' ' '}
        //    (   )                      /)
        //     `-'\   ,                    )
        //         |  \        `~.        /
        //         \   `._        \      /
        //          \     `._____,'    ,'
        //           `-.             ,'
        //              `-._     _,-'
        //                  77jj'
        //                 //_||
        //              __//--'/`
        //            ,--'/`  '
        //
        //see? here's one . . . coOT COOT!
    }
}

void Boss::lamprey_move() {

    int val = 1 + (rand() % static_cast<int>(2 - 1 + 1));
    if(val == 1)
        sight = 1;
    else if(val == 2)
        sight = -1;

    set_velY(getY(), jump_Speed*sight);
}
void Boss::expelled_move() {
    //------MOVEMENT------//

    int move = 1 + (rand() % static_cast<int>(6 - 1 + 1)); //min + (rand() % static_cast<int>(max - min + 1))

    if(move == 1){ //does a jump
        set_velY(getY(), jump_Speed);
    }
    else if (move == 2) { // moves to the side
        set_velX(getX(), sight*movement_speed);
    }
    else if (move == 3) { // jumps and moves to the side
        set_vel(getX(), getY(), sight*movement_speed, jump_Speed);
    }
    else if (move == 4) { // slams against the floor
        set_velY(getY(), -1*jump_Speed);
    }
    else if (move == 5) { // stays still
        // i do nothing :p
    }
    else if (move == 5) { // stays still
        //lmao same :ppppp
    }

    //------STATS------//
    movement_speed = 20 + (rand() % static_cast<int>(60 - 20 + 1));
    jump_Speed = 60 + (rand() % static_cast<int>(100 - 60 + 1));

    sight = -1 + (rand() % static_cast<int>(1 - (-1) + 1));
    if(sight == 0)
        sight = 1;

    setG(static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/5)));
    if(1 + (rand() % static_cast<int>(4 - (1) + 1)) == 1)
        setG(getG()*-1);

    setE(0.1 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(1.0-0.1))));
}
