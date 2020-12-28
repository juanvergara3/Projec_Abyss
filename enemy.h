#ifndef ENEMY_H
#define ENEMY_H

#include <QTimer>
#include <QGraphicsScene>
#include "entity.h"
#include "proyectile.h"

class Enemy : public Entity {
    Q_OBJECT

public: // Variables

private: // Variables
    float health;
    float damage;
    float shot_speed;
    float movement_speed;
    float jump_Speed;

    short sight;
    bool jumping;

    QTimer *shooting_timer;

public: // Methods
    //Enemy(QObject *parent, int dificulty, float x_, float y_, float vx_, float vy_, float mass_, int radio_, float g_, float K_, float e_, float V_);
    explicit Enemy(QObject *parent = nullptr, int dificulty = 1, float x_ = 0, float y_ = 0, float vx_ = 0, float vy_ = 0, float mass_ = 0, int radio_ = 0, float g_ = 0, float K_ = 0, float e_ = 0, float V_ = 0);
    ~Enemy();

    Proyectile *shoot(QGraphicsScene *scene);

    float getHealth() const;

    void take_damage(int damage);

private: // Methods


};

#endif // ENEMY_H
