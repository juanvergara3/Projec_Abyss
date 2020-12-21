#include "player.h"

Player::Player(QObject *parent) : QObject(parent) {

    health = 0;
    damage = 0;
    shot_speed = 0;
    fire_rate = 0;
    movement_speed = 15;
    jump_Speed = 40;

    x = 0;
    y = 0;
    Vx = 0;
    Vy = 0;

    Ax = 0;
    Ay = 0;
    mass = 20;
    radio = 8;
    g = 4;  // ******gravity******
    //K = 1e-3;
    K = 1e-5;
    e = 0.1;
    V = 0;
    dt = 0.1;

}

QRectF Player::boundingRect() const {
        return QRectF(-8, -8, 16, 16);
}
void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setBrush(Qt::black);
    painter->drawRect(boundingRect());
}

void Player::update(int y_max) {

    V = sqrt( pow(Vx ,2) + pow(Vy ,2) );

    angle = atan2(Vy, Vx); //arc_tan

    Ax = -1*((K*pow(V, 2) * pow(radio, 2))/mass) * cos(angle);
    Ay = (-1*((K*pow(V, 2) * pow(radio, 2))/mass) * sin(angle)) - g;

    x = x + Vx*dt + Ax*pow(dt, 2)/2;
    y = y + Vy*dt + Ay*pow(dt, 2)/2;

    Vx = Vx + Ax*dt;
    Vy = Vy + Ay*dt;

    setPos(x, y_max - y); 
}
void Player::set_vel(float px, float py, float vx, float vy) {
    x = px;
    y = py;
    Vx = vx;
    Vy = vy;
}
void Player::set_velX(float px, float vx) {
    x = px;
    Vx = vx;
}
void Player::set_velY(float py, float vy) {
    y = py;
    Vy = vy;
}

float Player::getVx() const{
    return Vx;
}
float Player::getVy() const{
    return Vy;
}
float Player::getX() const{
    return x;
}
float Player::getY() const{
    return y;
}
float Player::getRadio() const {
    return radio;
}
float Player::getE() const {
    return e;
}

float Player::getMovement_speed() const{
    return movement_speed;
}
float Player::getJump_Speed() const{
    return jump_Speed;
}

