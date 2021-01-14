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
    explicit Enemy(QObject *parent = nullptr, QGraphicsScene *s = nullptr, std::string shooting_type = "single", std::string movement_type = "", std::list<Proyectile *> *p = nullptr, int dificulty = 1, float x_ = 0, float y_ = 0, float vx_ = 0, float vy_ = 0, float mass_ = 0, int radio_ = 0, float g_ = 0, float K_ = 0, float e_ = 0, float V_ = 0);
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
    void zig_zag();

};

#endif // ENEMY_H
