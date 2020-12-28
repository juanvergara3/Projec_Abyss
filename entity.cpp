#include "entity.h"

Entity::Entity(QObject *parent, float x_, float y_, float vx_, float vy_, float mass_, int radio_, float g_, float K_, float e_, float V_) : QObject(parent), v_limit(720), h_limit(1280) {

    x = x_;
    y = y_;
    Vx = vx_;
    Vy = vy_;

    Ax = 0;
    Ay = 0;

    mass = mass_;
    radio = radio_;
    g = g_;
    K = K_;
    e = e_;
    V = V_;
    dt = 0.1;
}

Entity::~Entity() {

}

QRectF Entity::boundingRect() const {
        return QRectF(-radio, -radio, radio*2, radio*2);
}
void Entity::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setBrush(Qt::black);
    painter->drawRect(boundingRect());
}

void Entity::update() {

    V = sqrt( pow(Vx ,2) + pow(Vy ,2) );

    angle = atan2(Vy, Vx); //arc_tan

    Ax = -1*((K*pow(V, 2) * pow(radio, 2))/mass) * cos(angle);
    Ay = (-1*((K*pow(V, 2) * pow(radio, 2))/mass) * sin(angle)) - g;

    x = x + Vx*dt + Ax*pow(dt, 2)/2;
    y = y + Vy*dt + Ay*pow(dt, 2)/2;

    Vx = Vx + Ax*dt;
    Vy = Vy + Ay*dt;

    setPos(x, v_limit - y);
}
void Entity::set_vel(float px, float py, float vx, float vy) {
    x = px;
    y = py;
    Vx = vx;
    Vy = vy;
}
void Entity::set_velX(float px, float vx) {
    x = px;
    Vx = vx;
}
void Entity::set_velY(float py, float vy) {
    y = py;
    Vy = vy;
}

float Entity::getVx() const{
    return Vx;
}
float Entity::getVy() const{
    return Vy;
}
float Entity::getX() const{
    return x;
}
float Entity::getY() const{
    return y;
}
int Entity::getRadio() const {
    return radio;
}
float Entity::getE() const {
    return e;
}

void Entity::setK(float value) {
    K = value;
}
