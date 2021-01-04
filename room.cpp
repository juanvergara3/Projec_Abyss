#include "room.h"

Room::Room(QObject *parent, QGraphicsScene *scene, std::list<Proyectile *> *p, std::string file_name_) : QObject(parent), scene(scene), v_limit(720), h_limit(1280) {
    //load_room(file_name_);

    cleared = false;

    if(file_name_ == "1"){

        walls.push_back(new Wall(this, 200, 620, 150, 40));
        walls.push_back(new Wall(this, 200,660, 40, 60));
        walls.push_back(new Wall(this,700, 720-80, 40, 80));

        enemies.push_back(new Enemy(this, this->scene, "x", p, 1, 700, 300, 0, 0, 10, 15, 5, 1e-5, 0.1, 0));

        doors.push_back(new Door(this, this, 900, 720-40, 20, 40));
        //door = new Door(this, this, 900, 720-40, 20, 40);
    }
    else if (file_name_ == "2"){

        walls.push_back(new Wall(this, 450, 620, 150, 40));
        walls.push_back(new Wall(this, 200,660, 40, 60));

        enemies.push_back(new Enemy(this, this->scene, "x", p, 4, 700, 300, 0, 0, 10, 15, 5, 1e-5, 0.1, 0));

        doors.push_back(new Door(this, this, 900, 720-40, 20, 40));
        //door = new Door(this, this, 950, 720-40, 20, 40);
    }
}
Room::~Room() {
    //should it delete the content of the lists?
}

void Room::load_room() {

    for(auto k = walls.begin(); k!=walls.end(); k++){
        scene->addItem(*k);
        (*k)->setPos((*k)->getPosx(), (*k)->getPosy());
    }

    for(auto k = enemies.begin(); k!=enemies.end(); k++){
        scene->addItem(*k);
        (*k)->setPos((*k)->getX(), (*k)->getY());
        (*k)->init();
    }

    for(auto k = doors.begin(); k!=doors.end(); k++){
        scene->addItem(*k);
        (*k)->setPos((*k)->getPosx(), (*k)->getPosy());
    }
    //scene->addItem(door);
    //door->setPos(door->getPosx(), door->getPosy());
}
void Room::deload_room() {

    for(auto k = walls.begin(); k!=walls.end(); k++){
        scene->removeItem(*k);
    }

    for(auto k = enemies.begin(); k!=enemies.end(); k++){
        scene->removeItem(*k);
        (*k)->stop();
    }

    for(auto k = doors.begin(); k!=doors.end(); k++){
        //scene->removeItem(*k);
        //delete(*k);
        //k = doors.erase(k);
    }
}

void Room::load_room(std::string file_name) {

    std::fstream file (file_name, std:: fstream::in | std::fstream::binary);

     if(file.is_open()){

         std::string x_, y_, w_, h_, temp;
         short counter = 1;

         while (file >> temp){

             if(counter == 1)
                 x_ = temp;

             else if (counter == 2)
                 y_ = temp;

             else if (counter == 3)
                 w_ = temp;

             else if (counter == 4){
                 h_ = temp;

                 walls.push_back(new Wall(nullptr, stoi(x_), stoi(y_), stoi(w_), stoi(h_)));

                 counter = 0;
             }
             counter++;
         }
     }
     file.close();
}

std::list<Enemy *> Room::getEnemies() const {
    return enemies;
}

void Room::clear_room() {
    for (auto k = enemies.begin(); k != enemies.end(); k++) { //checks for enemies' health

        //delete(*k);

    }
    cleared = true;
   enemies.clear();
}

bool Room::isClear() const {
    return cleared;
}
