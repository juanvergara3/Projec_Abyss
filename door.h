#ifndef DOOR_H
#define DOOR_H

#include <QObject>
#include <QPainter>
#include <QGraphicsPixmapItem>

class Room;

class Door : public QObject, public QGraphicsItem {
    Q_OBJECT
private: //variables
    int posx, posy;
    int width, height;

    Room *self;
    Room *link;

public: //variables

private: //methods

public: //methods
    explicit Door(QObject *parent = nullptr, Room *self = nullptr, Room *link = nullptr, int x = 0, int y = 0, int w = 0, int h = 0);
    explicit Door(QObject *parent = nullptr, Room *self = nullptr, int x = 0, int y = 0, int w = 0, int h = 0);
    ~Door();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget);

    int getPosx() const;
    int getPosy() const;
    int getWidth() const;
    int getHeight() const;

    Room *getLink() const;
    void setLink(Room *value);

    Room *getSelf() const;

signals:

};

#endif // DOOR_H
