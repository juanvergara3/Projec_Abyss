#ifndef ITEM_H
#define ITEM_H

#include <QObject>
#include <QPainter>
#include <QGraphicsPixmapItem>

class Item : public QObject, public QGraphicsItem {
    Q_OBJECT
private: //variables
    int posx, posy;
    int width, height;

    std::string stat;
    int value;

public: //variables

private: //methods

public: //methods
    explicit Item(QObject *parent = nullptr, std::string stat = "", int value = 0);
    ~Item();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget);

    int getPosx() const;
    int getPosy() const;
    int getWidth() const;
    int getHeight() const;

    std::string getStat() const;
    int getValue() const;

};

#endif // ITEM_H
