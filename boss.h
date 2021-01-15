#ifndef BOSS_H
#define BOSS_H

#include <QObject>
#include <QLabel>
#include <QProgressBar>
#include <QGraphicsScene>
#include <QTimer>
#include "proyectile.h"

class Boss : public Entity {
    Q_OBJECT
public: // Variables

private: // Variables
    int health;
    int damage;
    float shot_speed;
    int fire_rate;
    float movement_speed;
    float jump_Speed;

    QProgressBar * health_bar;
    QLabel *name_label;
    QLabel *description_label;

    short sight;
    bool jumping;

    QTimer *shooting_timer;
    QTimer *movement_timer;

    QGraphicsScene *scene;

    std::list<Proyectile *> *proyectiles;

public: // Methods
    explicit Boss(QObject *parent = nullptr, QGraphicsScene *s = nullptr, std::string boss = "", std::list<Proyectile *> *p = nullptr, float x_ = 0, float y_ = 0, float vx_ = 0, float vy_ = 0, float mass_ = 0, int width_ = 0, int height_ = 0, float g_ = 0, float K_ = 0, float e_ = 0, float V_ = 0);
    ~Boss();

    int getHealth() const;
    int getDamage() const;

    void take_damage(int damage);

    void init();
    void stop();

private: // Methods

public slots:
    void lamprey_shoot();
    void priest_shoot();
    void expelled_shoot();

    void lamprey_move();
    void expelled_move();
};

#endif // BOSS_H
