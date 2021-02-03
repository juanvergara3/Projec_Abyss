#include "entity.h"

Entity::Entity(QObject *parent, float x_, float y_, float vx_, float vy_, float mass_, int radio_, float g_, float K_, float e_, float V_)
    : QObject(parent), v_limit(720), h_limit(1280), G(6.67384e-11)
{
    // for square entities with width == height

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

    width = radio*2;
    height = radio*2;
}

Entity::Entity(QObject *parent, float x_, float y_, float vx_, float vy_, float mass_, int width_, int height_, float g_, float K_, float e_, float V_)
    : QObject(parent), v_limit(720), h_limit(1280), G(6.67384e-11)
{
    // for rectangular entities with width != height

    x = x_;
    y = y_;
    Vx = vx_;
    Vy = vy_;

    Ax = 0;
    Ay = 0;

    width = width_;
    height = height_;

    mass = mass_;
    radio = 0;
    g = g_;
    K = K_;
    e = e_;
    V = V_;
    dt = 0.1;
}
Entity::~Entity() {

}

QRectF Entity::boundingRect() const {
        return QRectF(-width/2, -height/2, width, height);
}
void Entity::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) { // any entity without an overloaded paint method will be white
    painter->setBrush(Qt::white);
    painter->drawRect(boundingRect());
}

void Entity::update() { // updates parabolic entities

    V = sqrt( pow(Vx ,2) + pow(Vy ,2) );

    angle = atan2(Vy, Vx); //arc_tan

    Ax = -1*((K*pow(V, 2) * pow(width/2, 2))/mass) * cos(angle);
    Ay = (-1*((K*pow(V, 2) * pow(height/2, 2))/mass) * sin(angle)) - g;

    x = x + Vx*dt + Ax*pow(dt, 2)/2;
    y = y + Vy*dt + Ay*pow(dt, 2)/2;

    Vx = Vx + Ax*dt;
    Vy = Vy + Ay*dt;

    setPos(x, v_limit - y);
}
void Entity::orbital_update(Entity *k) { // updates orbital entities
    float aux = 0;
    float dis;

    dis = sqrt(pow((k->getX() - x), 2)+pow((k->getY() - y),2));

    Ax = 0;
    //aux += (G*((k->getMass()*100)*(k->getX() - x))/(pow(dis, 3)));
    aux += (1*((k->getMass()*100)*(k->getX() - x))/(pow(dis, 3)));
    Ax = aux;

    aux = 0;
    Ay = 0;
    //aux += (G*((k->getMass()*100)*(k->getY() - y)) / (pow(dis, 3)));
    aux += (1*((k->getMass()*100)*(k->getY() - y)) / (pow(dis, 3)));
    Ay = aux;

    Vx = Vx + (Ax*dt);
    Vy = Vy + (Ay*dt);
    x = x + (Vx*dt);
    y = y + (Vy*dt);

    setPos(x, v_limit - y);
}

void Entity::set_vel(float px, float py, float vx, float vy) { // changes x and y speed on entities
    x = px;
    y = py;
    Vx = vx;
    Vy = vy;
}
void Entity::set_velX(float px, float vx) { // changes x speed on entities
    x = px;
    Vx = vx;
}
void Entity::set_velY(float py, float vy) { // changes y speed on entities
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
void Entity::setG(float value) {
    g = value;
}
void Entity::setE(float value) {
    e = value;
}
void Entity::setRadio(int value) {
    radio = value;
}

int Entity::getV_limit() const {
    return v_limit;
}
int Entity::getH_limit() const {
    return h_limit;
}

float Entity::getMass() const {
    return mass;
}

int Entity::getWidth() const {
    return width;
}
int Entity::getHeight() const {
    return height;
}

float Entity::getG() const
{
    return g;
}

void Entity::setWidth(int value) {
    width = value;
}
void Entity::setHeight(int value) {
    height = value;
}
