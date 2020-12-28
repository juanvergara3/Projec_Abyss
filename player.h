#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QPainter>
#include <math.h>
#include <cmath>
#include <QProgressBar>
#include <QLabel>
#include <list>
#include "entity.h"
#include "proyectile.h"

class Player : public Entity {
    Q_OBJECT

public: // Variables

private: // Variables
    float health;
    float damage;
    float shot_speed;
    float movement_speed;
    float jump_Speed;

    QLabel *name_label;
    QProgressBar * health_bar;
    QLabel *damage_label;
    QLabel *shot_speed_label;
    QLabel *movement_speed_label;
    QLabel *jump_speed_label;

    std::list<QLabel *> labels;

    short sight;
    short direction;

    bool jumping;

    std::string name;

    const int v_limit, h_limit;

    QGraphicsScene *scene;

public: // Methods
    explicit Player(QObject *parent = nullptr, QGraphicsScene *s = nullptr, float x_ = 0, float y_ = 0, float vx_ = 0, float vy_ = 0, float mass_ = 0, int radio_ = 0, float g_ = 0, float K_ = 0, float e_ = 0, float V_ = 0);

    Proyectile* shoot();

    void update_stat(std::string s);
    void init_stats();

    void update();

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
