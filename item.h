#ifndef ITEM_H
#define ITEM_H

#include <QObject>
#include <QPainter>
#include <QGraphicsPixmapItem>
#include <QLabel>

class Item : public QObject, public QGraphicsItem {
    Q_OBJECT
private: //variables
    int posx, posy;
    int width, height;

    QLabel *name_label;

    std::string name;
    float max_health;
    float health;
    float damage;
    float shot_speed;
    float movement_speed;
    float jump_Speed;
    float g_player;
    float g_proyectiles;
    float r_player;
    float r_proyectiles;
    float e_player;
    std::string Shooting_mode;

public: //variables

private: //methods

public: //methods
    explicit Item(QWidget *parent = nullptr, std::string name = "",
                  float m_health = 1,
                  float health_ = 1,
                  float damage_ = 1,
                  float s_speed = 1,
                  float m_speed = 1,
                  float j_speed = 1,
                  float g_player_ = 1,
                  float g_proyectile_ = 1,
                  float r_player_ = 1,
                  float r_proyectiles_ = 1,
                  float e = 1,
                  std::string s_mode = "single");
    ~Item();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget);

    int getPosx() const;
    int getPosy() const;
    int getWidth() const;
    int getHeight() const;

    void updateLabel(int x, int y);

    std::string getName() const;
    float getMax_health() const;
    float getHealth() const;
    float getDamage() const;
    float getShot_speed() const;
    float getMovement_speed() const;
    float getJump_Speed() const;
    float getG_player() const;
    float getG_proyectiles() const;
    float getR_player() const;
    float getR_proyectiles() const;
    float getE_player() const;
    std::string getShooting_mode() const;
    QLabel *getName_label() const;
};

#endif // ITEM_H
