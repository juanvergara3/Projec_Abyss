#ifndef ITEM_H
#define ITEM_H

#include <QObject>
#include <QPainter>
#include <QGraphicsPixmapItem>
#include <QLabel>

class Item : public QObject, public QGraphicsItem {
    Q_OBJECT
private: //variables
    int posx, posy;
    int width, height;

    std::string stat;
    int value;

    QLabel *name;

public: //variables

private: //methods

public: //methods
    explicit Item(QObject *parent = nullptr, std::string name = "", std::string stat = "", int value = 0);
    ~Item();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget);

    int getPosx() const;
    int getPosy() const;
    int getWidth() const;
    int getHeight() const;

    std::string getStat() const;
    int getValue() const;

    QLabel *getName() const;

    void updateLabel(int x, int y);
};

#endif // ITEM_H
