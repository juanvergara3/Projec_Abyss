#ifndef ENEMY_H
#define ENEMY_H

#include <QTimer>
#include <QGraphicsScene>
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include "entity.h"
#include "proyectile.h"

class Enemy : public Entity {
    Q_OBJECT
public: // Variables

private: // Variables
    int health;
    int damage;
    float shot_speed;
    int fire_rate;
    int movement_rate;
    float movement_speed;
    float jump_Speed;

    short sight;
    bool jumping;
    short direction;

    QTimer *shooting_timer;
    QTimer *movement_timer;

    QGraphicsScene *scene;

    std::list<Proyectile *> *proyectiles;

public: // Methods
    Enemy(QObject *parent = nullptr, QGraphicsScene *s = nullptr, std::string shooting_type = "single", std::string movement_type = "none", std::list<Proyectile *> *p = nullptr, int fire_rate = 1000, int movement_rate = 1000, float movement_speed = 1, float jump_speed = 20,int dificulty = 3, float x = 0, float y = 0, int w = 30, int h = 30, float g = 4);
    ~Enemy();

    int getHealth() const;
    int getDamage() const;

    void take_damage(int damage);

    void init();
    void stop();

private: // Methods

public slots:
    void shoot_single();
    void shoot_double();
    void shoot_cross();
    void shoot_x();
    void shoot_orbit();

    void jump();
    void left_right();
    void left_right_jump();

};

#endif // ENEMY_H
