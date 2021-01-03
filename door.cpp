#include "door.h"
#include "room.h"

Door::Door(QObject *parent, Room *self, Room *link, int x, int y, int w, int h) {
    posx = x;
    posy = y;
    width = w;
    height = h;

    this->self = self;
    this->link = link;

    setPos(posx, posy);
}
Door::Door(QObject *parent, Room *self, int x, int y, int w, int h) {
    posx = x;
    posy = y;
    width = w;
    height = h;

    this->self = self;
    this->link = nullptr;

    setPos(posx, posy);
}
Door::~Door(){

}

QRectF Door::boundingRect() const{
    return QRectF(0, 0, width, height);
}
void Door::paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget) {
    painter->setBrush(Qt::blue);
    //painter->setPen(Qt::NoPen);
    painter->drawRect(boundingRect());
}

int Door::getPosx() const {
    return posx;
}
int Door::getPosy() const {
    return posy;
}
int Door::getWidth() const {
    return width;
}
int Door::getHeight() const {
    return height;
}

Room *Door::getLink() const {
    return link;
}
void Door::setLink(Room *value) {
    link = value;
}

Room *Door::getSelf() const {
    return self;
}


