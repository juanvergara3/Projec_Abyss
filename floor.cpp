#include "floor.h"

Floor::Floor(QGraphicsScene *scene, std::list<Proyectile *> *p, short num)
    :scene(scene), proyectiles(p), num(num)
{
    load_floor(num);

    clear_state = false;
}
Floor::~Floor() {
    delete safe;
    delete treasure;
    delete boss;
    delete r1;
    delete r2;
    delete r3;
    delete r4;
}

void Floor::start_floor_music() {
    floor_music->play();
}
void Floor::stop_floor_music() {
    floor_music->stop();
}
void Floor::start_boss_music() {
    boss_music->play();
}
void Floor::stop_boss_music() {
    boss_music->stop();
}

bool Floor::is_playing(std::string type) {

    if(type == "boss"){
        if(boss_music->state() == QMediaPlayer::PlayingState)
            return true;
        else
            return false;
    }
    else if (type == "floor") {
        if(floor_music->state() == QMediaPlayer::PlayingState)
            return true;
        else
            return false;
    }

    return false;
}


bool Floor::getClear_state() const
{
    return clear_state;
}

void Floor::setClear_state(bool value)
{
    clear_state = value;
}

int Floor::getNum() const
{
    return num;
}

void Floor::load_floor(short num) {
    
    if(num == 1){
        safe = new Room(nullptr, scene, proyectiles, "f1-safe");
        treasure = new Room(nullptr, scene, proyectiles, "f1-item");
        boss = new Room(nullptr, scene, proyectiles, "lamprey");
        r1 = new Room(nullptr, scene, proyectiles, "f1-1");
        r2 = new Room(nullptr, scene, proyectiles, "f1-2");
        r3 = new Room(nullptr, scene, proyectiles, "f1-3");
        r4 = new Room(nullptr, scene, proyectiles, "f1-4");

        floor_playlist = new QMediaPlaylist();
        floor_playlist->addMedia(QUrl("qrc:/Assets/OST/The Binding of Isaac Antibirth OST Descent (Title).mp3"));
        floor_playlist->setPlaybackMode(QMediaPlaylist::Loop);
        floor_music = new QMediaPlayer;
        floor_music->setPlaylist(floor_playlist);
        floor_music->setVolume(10);

//        floor_music= new QMediaPlayer();
//        floor_music->setMedia(QUrl("qrc:/Assets/OST/The Binding of Isaac Antibirth OST Descent (Title).mp3"));

//        connect(floor_music, &QMediaPlayer::stateChanged, [this](QMediaPlayer::State state) {
//                if (state == QMediaPlayer::State::StoppedState)
//                    floor_music->play();
//            });

        boss_playlist = new QMediaPlaylist();
        boss_playlist->addMedia(QUrl("qrc:/Assets/OST/Epic Dark Battle Music - Escape [Powerful Fantasy Horror by Ebunny].mp3"));
        boss_playlist->setPlaybackMode(QMediaPlaylist::Loop);
        boss_music = new QMediaPlayer;
        boss_music->setPlaylist(boss_playlist);
        boss_music->setVolume(10);
    }
    else if (num == 2) {
        safe = new Room(nullptr, scene, proyectiles, "f2-safe");
        treasure = new Room(nullptr, scene, proyectiles, "f2-item");
        boss = new Room(nullptr, scene, proyectiles, "priest");
        r1 = new Room(nullptr, scene, proyectiles, "f2-1");
        r2 = new Room(nullptr, scene, proyectiles, "f2-2");
        r3 = new Room(nullptr, scene, proyectiles, "f2-3");
        r4 = new Room(nullptr, scene, proyectiles, "f2-4");

        floor_playlist = new QMediaPlaylist();
        floor_playlist->addMedia(QUrl("qrc:/Assets/OST/The Binding of Isaac Antibirth OST Machine in the Walls (Mausoleum).mp3"));
        floor_playlist->setPlaybackMode(QMediaPlaylist::Loop);
        floor_music = new QMediaPlayer;
        floor_music->setPlaylist(floor_playlist);
        floor_music->setVolume(10);

        boss_playlist = new QMediaPlaylist();
        boss_playlist->addMedia(QUrl("qrc:/Assets/OST/The Binding of Isaac Antibirth OST The Hammer of Pompeii (Necropolis).mp3"));
        boss_playlist->setPlaybackMode(QMediaPlaylist::Loop);
        boss_music = new QMediaPlayer;
        boss_music->setPlaylist(boss_playlist);
        boss_music->setVolume(10);
    }
    else if (num == 3) {
        safe = new Room(nullptr, scene, proyectiles, "f3-safe");
        treasure = new Room(nullptr, scene, proyectiles, "f3-item");
        boss = new Room(nullptr, scene, proyectiles, "expelled");
        r1 = new Room(nullptr, scene, proyectiles, "f3-1");
        r2 = new Room(nullptr, scene, proyectiles, "f3-2");
        r3 = new Room(nullptr, scene, proyectiles, "f3-3");
        r4 = new Room(nullptr, scene, proyectiles, "f3-4");

        floor_playlist = new QMediaPlaylist();
        floor_playlist->addMedia(QUrl("qrc:/Assets/OST/Innocence Glitched (Basement).mp3"));
        floor_playlist->setPlaybackMode(QMediaPlaylist::Loop);
        floor_music = new QMediaPlayer;
        floor_music->setPlaylist(floor_playlist);
        floor_music->setVolume(10);

        boss_playlist = new QMediaPlaylist();
        boss_playlist->addMedia(QUrl("qrc:/Assets/OST/Mittsies - Epitomize.mp3"));
        boss_playlist->setPlaybackMode(QMediaPlaylist::Loop);
        boss_music = new QMediaPlayer;
        boss_music->setPlaylist(boss_playlist);
        boss_music->setVolume(10);
    }
    else{
        safe = nullptr;
        treasure = nullptr;
        boss = nullptr;
        r1 = nullptr;
        r2 = nullptr;
        r3 = nullptr;
        r4 = nullptr;
    }

    load_links(num);
}

void Floor::load_links(short num)
{
    if(num == 1){
        safe->right_door->setLink(r1->left_door);
        r1->left_door->setLink(safe->right_door);

        r1->right_door->setLink(r2->left_door);
        r2->left_door->setLink(r1->right_door);

        r2->up_door->setLink(treasure->down_door);
        treasure->down_door->setLink((r2->up_door));

        r1->down_door->setLink(r3->up_door);
        r3->up_door->setLink(r1->down_door);

        r3->down_door->setLink(r4->up_door);
        r4->up_door->setLink(r3->down_door);

        r4->right_door->setLink(boss->left_door);
        boss->left_door->setLink(r4->right_door);
    }
    else if (num == 2) {
        safe->down_door->setLink(r1->up_door);
        r1->up_door->setLink(safe->down_door);

        r1->left_door->setLink(r2->right_door);
        r2->right_door->setLink(r1->left_door);

        r2->left_door->setLink(treasure->right_door);
        treasure->right_door->setLink(r2->left_door);

        r1->right_door->setLink(r3->left_door);
        r3->left_door->setLink(r1->right_door);

        r3->right_door->setLink(r4->left_door);
        r4->left_door->setLink(r3->right_door);

        r4->up_door->setLink(boss->down_door);
        boss->down_door->setLink(r4->up_door);
    }
    else if (num == 3) {
        safe->up_door->setLink(r1->right_door);
        r1->right_door->setLink(safe->up_door);

        r1->left_door->setLink(treasure->right_door);
        treasure->right_door->setLink(r1->left_door);

        safe->right_door->setLink(r2->left_door);
        r2->left_door->setLink(safe->right_door);

        r2->right_door->setLink(r3->up_door);
        r3->up_door->setLink(r2->right_door);

        r2->up_door->setLink(r4->left_door);
        r4->left_door->setLink(r2->up_door);

        r4->right_door->setLink(boss->left_door);
        boss->left_door->setLink(r4->right_door);
    }
}
