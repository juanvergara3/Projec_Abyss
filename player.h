#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QPainter>
#include <math.h>
#include <cmath>
#include "entity.h"
#include "proyectile.h"

class Player : public Entity {
    Q_OBJECT

public: // Variables

private: // Variables
    float health;
    float damage;
    float shot_speed;
    float fire_rate;
    float movement_speed;
    float jump_Speed;

    short sight;
    short direction;

    bool jumping;

public: // Methods
    explicit Player(QObject *parent = nullptr, float x_ = 0, float y_ = 0, float vx_ = 0, float vy_ = 0, float mass_ = 0, int radio_ = 0, float g_ = 0, float K_ = 0, float e_ = 0, float V_ = 0);

    Proyectile* shoot(QGraphicsScene *scene);

    void update(int y_max);

    float getMovement_speed() const;
    float getJump_Speed() const;

    void addDirection(int d);

    bool getJumping() const;
    void setJumping(bool value);
    void setSight(short value);

    short getDirection() const;

private: // Methods

};

#endif // PLAYER_H
