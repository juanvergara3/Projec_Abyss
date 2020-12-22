#ifndef PROYECTILE_H
#define PROYECTILE_H
#include "entity.h"


class Proyectile: public Entity {
    Q_OBJECT

public: // Variables

private: // Variables
    float damage;
    float shot_speed;

public: // Methods
    explicit Proyectile(QObject *parent = nullptr, float damage_ = 0, float x_ = 0, float y_ = 0, float vx_ = 0, float vy_ = 0, float mass_ = 0, int radio_ = 0, float g_ = 0, float K_ = 0, float e_ = 0, float V_ = 0);
    ~Proyectile();

private: // Methods

};

#endif // PROYECTILE_H
