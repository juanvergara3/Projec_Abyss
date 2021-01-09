#include "room.h"

Room::Room(QObject *parent, QGraphicsScene *scene, std::list<Proyectile *> *p, std::string file_name_) : QObject(parent), scene(scene), v_limit(720), h_limit(1280) {
    //load_room(file_name_);

    cleared = false;

    itemX =  250;
    itemY = 720 - 16;
    item = nullptr;

    if(file_name_ == "1"){

        walls.push_back(new Wall(this, 200, 620, 150, 40));
        walls.push_back(new Wall(this, 200,660, 40, 60));
        walls.push_back(new Wall(this,700, 720-80, 40, 80));

        //enemies.push_back(new Enemy(this, this->scene, "x", p, 1, 700, 300, 0, 0, 10, 15, 5, 1e-5, 0.1, 0));

        doors.push_back(new Door(this, this, 900, 720-40, 20, 40));

        boss = new Boss(this, scene, "priest", p, 640, 360, 0, 0, 100, 40, 5, 1e-5, 0.1, 0);
        //boss = nullptr;

        type = "boss";
        //type = "normal";
    }
    else if (file_name_ == "2"){

        walls.push_back(new Wall(this, 450, 620, 150, 40));
        walls.push_back(new Wall(this, 200,660, 40, 60));

        enemies.push_back(new Enemy(this, this->scene, "x", p, 4, 700, 300, 0, 0, 10, 15, 5, 1e-5, 0.1, 0));

        doors.push_back(new Door(this, this, 30, 720-40, 20, 40));

        boss = nullptr;

        type = "normal";
    }
}
Room::~Room() {
    //should it delete the content of the lists?
    delete item;
    delete boss;
}

void Room::load_room() {

    for(auto k = walls.begin(); k!=walls.end(); k++){
        scene->addItem(*k);
        (*k)->setPos((*k)->getPosx(), (*k)->getPosy());
    }

    if(type == "normal")
        for(auto k = enemies.begin(); k!=enemies.end(); k++){
            scene->addItem(*k);
            (*k)->setPos((*k)->getX(), (*k)->getY());
            (*k)->init();
        }

    for(auto k = doors.begin(); k!=doors.end(); k++){
        scene->addItem(*k);
        (*k)->setPos((*k)->getPosx(), (*k)->getPosy());
    }

    if(item != nullptr){
        scene->addItem(item);
        item->setPos(itemX, itemY);
        item->getName()->setVisible(true);
    }

    if(type == "boss"){
        if(boss != nullptr){
            scene->addItem(boss);
            boss->setPos(boss->getX(), boss->getY());
            boss->init(); //if you exit the room and then come back it tries to add the widgets again
        }
    }
}
void Room::deload_room() {

    for(auto k = walls.begin(); k!=walls.end(); k++){
        scene->removeItem(*k);
    }

    if(type == "normal")
        for(auto k = enemies.begin(); k!=enemies.end(); k++){
            scene->removeItem(*k);
            (*k)->stop();
        }

    if(item != nullptr){
        scene->removeItem(item);
        item->getName()->setVisible(false);
    }

    if(type == "boss")
        if(boss != nullptr){
            scene->removeItem(boss);
            boss->stop();
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
    cleared = true;

    if(type == "normal")
        enemies.clear();

    else  if(type == "boss") {
        delete boss;
        boss = nullptr;
    }
}

bool Room::isClear() const {
    return cleared;
}

std::string Room::getType() const {
    return type;
}

Boss *Room::getBoss() const {
    return boss;
}

int Room::getItemX() const {
    return itemX;
}
int Room::getItemY() const {
    return itemY;
}

void Room::remove_item() {
    scene->removeItem(item);
    delete item;
    item = nullptr;
}

void Room::spawn_heart() {
    item = new Item(this, "Heart", "health", 25);
    item->setPos(itemX, itemY);
    scene->addItem(item);
    item->updateLabel(itemX, itemY);
    scene->addWidget(item->getName());
    item->getName()->setVisible(true);
}
void Room::spawn_item(Item *i) {

    if(i != nullptr) {
        item = i;
        item->setPos(itemX, itemY);
        scene->addItem(item);
        item->updateLabel(itemX, itemY);
        scene->addWidget(item->getName());
        item->getName()->setVisible(true);
    }
}
