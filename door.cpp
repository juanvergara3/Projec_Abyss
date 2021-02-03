#include "door.h"
#include "room.h"
#include "floor.h"

Door::Door(QObject *parent, Room *self, int x, int y, int w, int h) { // constructor for normal room to room doors
    posx = x;
    posy = y;
    width = w;
    height = h;

    this->self = self;
    this->link = nullptr;

    setPos(posx, posy);

    next = nullptr;
    sprite = nullptr;

    type = "normal";
}

Door::Door(QObject *parent, Floor *next, std::string type_, int playerX, int playerY, int x, int y, int w, int h, std::string sprite) { // constructor for floor to floor doors
    posx = x;
    posy = y;
    width = w;
    height = h;

    setPos(posx, posy);

    self  = nullptr;
    link = nullptr;

    this->playerX = playerX;
    this->playerY = playerY;

    this->next = next;

    this->sprite = new QPixmap(sprite.c_str());

    type = type_;
}
Door::~Door(){
    if(sprite != nullptr)
        delete sprite;
}

QRectF Door::boundingRect() const{
    return QRectF(0, 0, width, height);
}
void Door::paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget) { // if the door object has a sprite it gets used if not it'll be transparent

    if(sprite != nullptr)
        painter->drawPixmap(0, 0, *sprite, 0 , 0, width, height);
    else{
        //painter->setBrush(Qt::blue);
        painter->setPen(Qt::NoPen);
        painter->drawRect(boundingRect());
    }
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

void Door::setLink(Door *value) { // sets the door to which this is linked
    link = value;
}
Door *Door::getLink() const {
    return link;
}
Room *Door::getSelf() const {
    return self;
}

void Door::setNext(Floor *value) { // sets the floor to which this is linked
    next = value;
}
Floor *Door::getNext() const {
    return next;
}

int Door::getPlayerX() const {
    return playerX;
}
int Door::getPlayerY() const {
    return playerY;
}

std::string Door::getType() const {
    return type;
}
