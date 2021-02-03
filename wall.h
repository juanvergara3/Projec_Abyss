#ifndef WALL_H
#define WALL_H

#include <QObject>
#include <QPainter>
#include <QGraphicsPixmapItem>

class Wall : public QObject, public QGraphicsItem  {
    Q_OBJECT
private: //variables
    int posx, posy;
    int width, height;

public: //variables

private: //methods

public: //methods
    Wall(QObject *parent = nullptr, int x = 0, int y = 0, int w = 0, int h = 0);
    ~Wall();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget);

    int getPosx() const;
    int getPosy() const;
    int getWidth() const;
    int getHeight() const;
};

#endif // WALL_H
