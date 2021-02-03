#ifndef ENTITY_H
#define ENTITY_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPainter>
#include <math.h>
#include <cmath>

class Entity : public QObject, public QGraphicsItem {
    Q_OBJECT
public: //variables

private: //variables
    float x;
    float y;
    float Vx;
    float Vy;

    float Ax, Ay;
    float mass;
    int radio;
    float angle;
    float g; //gravedad
    float K; //resistencia del aire
    float e; //coeficiente de restitucion
    float V; //vector de velocidad
    float dt; //delta de tiempo

    int width, height;

    const int v_limit, h_limit;

    const float G;

public: //methods
    Entity(QObject *parent = nullptr, float x_ = 0, float y_ = 0, float vx_ = 0, float vy_ = 0, float mass_ = 0, int radio_ = 0, float g_ = 0, float K_ = 0, float e_ = 0, float V_ = 0);
    Entity(QObject *parent = nullptr, float x_ = 0, float y_ = 0, float vx_ = 0, float vy_ = 0, float mass_ = 0, int width_ = 0, int height = 0, float g_ = 0, float K_ = 0, float e_ = 0, float V_ = 0);
    ~Entity();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

    void update();
    void orbital_update(Entity *k);
    void set_vel(float px, float py, float vx, float vy);
    void set_velX(float px, float vx);
    void set_velY(float py, float vy);

    float getVx() const;
    float getVy() const;
    float getX() const;
    float getY() const;
    int getRadio() const;
    float getE() const;
    float getMass() const;

    void setK(float value);

    int getV_limit() const;
    int getH_limit() const;

    float getG() const;
    void setG(float value);
    void setE(float value);
    void setRadio(int value);

    int getWidth() const;

    int getHeight() const;

    void setWidth(int value);

    void setHeight(int value);

private: //methods

};

#endif // ENTITY_H
