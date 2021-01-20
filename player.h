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
#include "item.h"

class Player : public Entity {
    Q_OBJECT
public: // Variables

private: // Variables
    float max_health;
    float health;
    float damage;
    float shot_speed;
    float movement_speed;
    float jump_Speed;
    float g;
    float g_p;
    float r;
    float r_p;
    float e;
    std::string shooting_mode;

    QProgressBar * health_bar;
    QLabel *name_label;
    QLabel *max_health_label;
    QLabel *damage_label;
    QLabel *shot_speed_label;
    QLabel *movement_speed_label;
    QLabel *jump_speed_label;

    std::list<QLabel *> labels;

    std::list<Proyectile *> *proyectiles;

    short sight;
    short direction;

    bool jumping;

    std::string name;

    QGraphicsScene *scene;

public: // Methods
    explicit Player(QObject *parent = nullptr, QGraphicsScene *s = nullptr, std::string name = "", std::list<Proyectile *> *p = nullptr, int statPos = 0, float x_ = 0, float y_ = 0, float vx_ = 0, float vy_ = 0, float mass_ = 0, int radio_ = 0, float g_ = 0, float K_ = 0, float e_ = 0, float V_ = 0);
    ~Player();

    void shoot();

    void update_stat(std::string s);
    void update_stats(Item *i);

    void take_damage(int damage);

    void update();

    float getMovement_speed() const;
    float getJump_Speed() const;

    void addDirection(int d);

    bool getJumping() const;
    void setJumping(bool value);
    void setSight(short value);

    short getDirection() const;

    std::string getName() const;

private: // Methods
    void init_stats(int x_reference);

};

#endif // PLAYER_H
