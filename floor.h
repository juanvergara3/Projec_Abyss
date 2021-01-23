#ifndef FLOOR_H
#define FLOOR_H
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include "room.h"

class Floor {
private: // variables
    QGraphicsScene *scene;
    std::list<Proyectile *> *proyectiles;

    QMediaPlayer *floor_music;
    QMediaPlayer *boss_music;

    QMediaPlaylist *floor_playlist;
    QMediaPlaylist *boss_playlist;

    bool clear_state;

    int  const num;

public: // variables
    Room *safe,*boss, *treasure;
    Room *r1,*r2, *r3, *r4;

private: // methods
    void load_floor(short num);
    void load_links(short num);

public: // methods
    Floor(QGraphicsScene *scene = nullptr, std::list<Proyectile *> *p = nullptr, short num = 0);
    ~Floor();

    void start_floor_music();
    void stop_floor_music();
    void start_boss_music();
    void stop_boss_music();

    bool is_playing(std::string type);

    bool getClear_state() const;
    void setClear_state(bool value);
    int getNum() const;
};

#endif // FLOOR_H
