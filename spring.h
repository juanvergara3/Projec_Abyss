#ifndef SPRING_H
#define SPRING_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>

class Spring : public QObject, public QGraphicsItem {
    Q_OBJECT    
private: // variables
    int width, height;
    int x, y;

    const int v_limit, h_limit;

    int TargetHeight;
    int Speed;

    float Tension;
    float Dampening;

public: // variables

private: //methods

public: // methods
    explicit Spring(QObject *parent = nullptr, int x = 0, int y = 0, int target_height = 0, int width = 0, float tension = 0, float dampening = 0);
    ~Spring();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget);

    void setSpeed(int value);

    int getSpeed();

    int getHeight() const;

public slots:
    void update();

};

#endif // SPRING_H
