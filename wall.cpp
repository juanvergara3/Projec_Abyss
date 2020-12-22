#include "wall.h"

Wall::Wall(QObject *parent, int x, int y, int w, int h) {
    posx = x;
    posy = y;
    width = w;
    height = h;

    setPos(posx, posy);
}
Wall::~Wall(){

}

QRectF Wall::boundingRect() const{
    return QRectF(0, 0, width, height);
}
void Wall::paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget) {
    painter->setBrush(Qt::green);
    //painter->setPen(Qt::NoPen);
    painter->drawRect(boundingRect());
}

int Wall::getPosx() const {
    return posx;
}
int Wall::getPosy() const {
    return posy;
}
int Wall::getWidth() const {
    return width;
}
int Wall::getHeight() const {
    return height;
}
