#include "spring.h"

Spring::Spring(QObject *parent, int x, int y, int target_height, int width, float tension, float dampening) :
    width(width), height(target_height),
    x(x), y(y),
    v_limit(720), h_limit(1280),
    TargetHeight(target_height), Tension(tension), Dampening(dampening)
{
    setPos(x, v_limit - y);
}
Spring::~Spring() {

}

QRectF Spring::boundingRect() const {
    return QRectF(0, -height, width, height);
}
void Spring::paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget) { // gives the spring it's apperance
    QBrush b(QColor(200, 200, 200));
    b.setStyle(Qt::HorPattern);

    painter->setBrush(b);
    painter->drawRect(boundingRect());
}

void Spring::update() { //  updates the spring

    // target height is the defaul spring height. the height changes based on "Speed". speed changes when a player collides with the spring

    float x = TargetHeight - height;
    Speed += (Tension * x) - (Speed * Dampening);
    height += Speed;

    QGraphicsItem::update();
}

void Spring::setSpeed(int value)
{
    Speed = value;
}
int Spring::getSpeed() { // weird physics formula i found
    return -1*Tension/20*(TargetHeight - height);
}
int Spring::getHeight() const
{
    return height;
}
