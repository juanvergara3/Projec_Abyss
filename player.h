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
#include <QTimer>
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
    float r_p;
    float e;
    std::string shooting_mode;

    const int statPos;

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

    QPixmap *sprite;
    int i, j;
    QTimer *sprite_timer;

    bool jumping;

    bool alive;

    std::string name;

    QGraphicsScene *scene;

public: // Methods
    Player(QObject *parent = nullptr, QGraphicsScene *s = nullptr, std::string name = "", std::list<Proyectile *> *p = nullptr,
                    int statPos = 0, float x_ = 0, float y_ = 0, int player = 1);

    Player (QObject *parent = nullptr, QGraphicsScene *s = nullptr, std::list<Proyectile *> *p = nullptr, int player = 1, int x = 0, int y = 0,
            int statPos = 0, std::string name = "", float max_health = 100, float health = 100, float damage = 20,
            float shot_speed = 30,  float movement_speed = 1.5, float jump_Speed = 40,
            float g = 4, float g_p = 1, float w = 12, float h = 15, float r_p = 4, float e = 0.1,
            std::string shooting_mode = "single");

    ~Player();

    void shoot();

    void update_stat(std::string s);
    void update_stats(Item *i);

    void take_damage(int damage);

    void update();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

    float getMovement_speed() const;
    float getJump_Speed() const;

    void addDirection(int d);

    bool getJumping() const;
    void setJumping(bool value);
    void setSight(short value);

    short getDirection() const;

    std::string getName() const;
    float getHealth() const;
    bool getAlive() const;

    void die();

    float getMax_health() const;
    float getDamage() const;
    float getShot_speed() const;
    float getG_p() const;
    float getR_p() const;

    std::string getShooting_mode() const;

    int getStatPos() const;

private: // Methods
    void init_stats(int x_reference);

private slots:
    void update_sprite();

};

#endif // PLAYER_H
