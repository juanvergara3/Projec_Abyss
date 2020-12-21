#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPainter>
#include <math.h>
#include <cmath>

class Player : public QObject, public QGraphicsItem {
    Q_OBJECT

public: // Variables

private: // Variables
    float health;
    float damage;
    float shot_speed;
    float fire_rate;

    float x;
    float y;
    float Vx; // movement speed
    float Vy; // jump speed

    float Ax, Ay;
    float mass;
    float radio;
    float angle;
    float g; //gravedad
    float K; //resistencia del aire
    float e; //coeficiente de restitucion
    float V; //vector de velocidad
    float dt; //delta de tiempo

    std::string dir;

public: // Methods
    explicit Player(QObject *parent = nullptr);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

    void update(int y_max);
    void set_vel(float px, float py, float vx, float vy);

    float getVx() const;
    float getVy() const;
    float getX() const;
    float getY() const;
    float getRadio() const;
    float getE() const;

    std::string getDir() const;
    void setDir(const std::string &value);

private: // Methods

};

#endif // PLAYER_H
