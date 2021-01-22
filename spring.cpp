#include "spring.h"

void Spring::setSpeed(int value)
{
    Speed = value;
}

int Spring::getSpeed() {
    return -1*Tension/20*(TargetHeight - height);
}

int Spring::getHeight() const
{
    return height;
}

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
void Spring::paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget) {
    painter->setBrush(Qt::magenta);
    painter->drawRect(boundingRect());
}

void Spring::update() {
    float x = TargetHeight - height;
    Speed += (Tension * x) - (Speed * Dampening);
    height += Speed;

    QGraphicsItem::update();
}
