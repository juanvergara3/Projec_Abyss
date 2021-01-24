#ifndef DOOR_H
#define DOOR_H
#include <QObject>
#include <QPainter>
#include <QGraphicsPixmapItem>

class Room;
class Floor;

class Door : public QObject, public QGraphicsItem {
    Q_OBJECT
private: //variables
    int posx, posy;
    int playerX, playerY;
    int width, height;

    Room *self;
    Door *link;

    Floor *next;

    std::string type;

    QPixmap *sprite;

public: //variables

private: //methods

public: //methods
    explicit Door(QObject *parent = nullptr, Room *self = nullptr, int x = 0, int y = 0, int w = 0, int h = 0);
    explicit Door(QObject *parent =  nullptr, Floor *next = nullptr, std::string type_ = "", int playerX = 0, int playerY = 0,int x = 0, int y = 0, int w = 0, int h = 0);
    ~Door();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget);

    int getPosx() const;
    int getPosy() const;
    int getWidth() const;
    int getHeight() const;

    void setLink(Door *value);
    Door *getLink() const;
    Room *getSelf() const;

    void setNext(Floor *value);
    Floor *getNext() const;

    int getPlayerX() const;
    int getPlayerY() const;

    std::string getType() const;
};

#endif // DOOR_H
