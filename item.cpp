#include "item.h"

Item::Item(QObject *parent, std::string stat, int value) : QObject(parent) {
    this->stat = stat;
    this->value = value;
}
Item::~Item(){

}

QRectF Item::boundingRect() const{
    return QRectF(0, 0, width, height);
}
void Item::paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget) {
    painter->setBrush(Qt::red);
    //painter->setPen(Qt::NoPen);
    painter->drawRect(boundingRect());
}

int Item::getPosx() const {
    return posx;
}
int Item::getPosy() const {
    return posy;
}
int Item::getWidth() const {
    return width;
}
int Item::getHeight() const {
    return height;
}

std::string Item::getStat() const {
    return stat;
}
int Item::getValue() const {
    return value;
}
