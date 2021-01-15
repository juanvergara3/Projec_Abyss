#include "room.h"

Room::Room(QObject *parent, QGraphicsScene *scene, std::list<Proyectile *> *p, std::string file_name_) : QObject(parent), scene(scene), v_limit(720), h_limit(1280) {
    //load_room(file_name_);

    cleared = false;
    item = nullptr;
    if(file_name_ == "1"){
        walls.push_back(new Wall(this, 1280 - 300, 720 - 300, 300, 300));
        walls.push_back(new Wall(this, 1280-400, 720-200, 100, 200));
        walls.push_back(new Wall(this, 1280-500, 720-100, 100, 100));

        doors.push_back(new Door(this, this, 1280-160, 720-300-40, 20, 40));

        itemX = 0;
        itemY = 0;

        boss = nullptr;

        type = "safe";
    }
    else if(file_name_ == "2"){
        walls.push_back(new Wall(this, 0, 720 - 300, 100, 300));
        walls.push_back(new Wall(this, 100, 720-200, 100, 200));
        walls.push_back(new Wall(this, 200, 720-100, 100, 100));
        walls.push_back(new Wall(this, 1280 - 100, 720 - 300, 100, 300));
        walls.push_back(new Wall(this, 250, 720 - 400, 300, 40));
        walls.push_back(new Wall(this, 700, 720 - 300, 300, 40));
        walls.push_back(new Wall(this, 650, 720 - 550, 300, 40));

        //enemies.push_back(new Enemy(this, this->scene, "x", p, 4, 850, 20, 0, 0, 10, 15, 5, 1e-5, 0.1, 0));
        //enemies.push_back(new Enemy(this, this->scene, "x", p, 4, 400, 420, 0, 0, 10, 15, 5, 1e-5, 0.1, 0));
        //enemies.push_back(new Enemy(this, this->scene, "x", p, 4, 850, 320, 0, 0, 10, 15, 5, 1e-5, 0.1, 0));
        //enemies.push_back(new Enemy(this, this->scene, "x", p, 4, 850, 570, 0, 0, 10, 15, 5, 1e-5, 0.1, 0));

        doors.push_back(new Door(this, this, 1280-60, 720-300-40, 20, 40));
        doors.push_back(new Door(this, this, 40, 720-300-40, 20, 40));
        doors.push_back(new Door(this, this, 1280/2 - 10, 720-40, 20, 40));

        itemX = 840;
        itemY = 720 - 550 - 16;

        boss = nullptr;

        type = "normal";
    }
    else if(file_name_ == "3"){
        walls.push_back(new Wall(this, 0, 720 - 300, 200, 40));
        walls.push_back(new Wall(this, 300, 720 - 200, 200, 40));
        walls.push_back(new Wall(this, 500, 720-60, 500, 60));
        walls.push_back(new Wall(this, 1280-200, 720 - 200, 200, 40));
        walls.push_back(new Wall(this, 800, 720 - 350, 200, 40));
        walls.push_back(new Wall(this, 500, 720 - 450, 200, 40));
        walls.push_back(new Wall(this, 200, 720 - 550, 200, 40));
        walls.push_back(new Wall(this, 500, 720 - 650, 200, 40));

//        enemies.push_back(new Enemy(this, this->scene, "x", p, 4, 780, 80, 0, 0, 10, 15, 5, 1e-5, 0.1, 0));
//        enemies.push_back(new Enemy(this, this->scene, "x", p, 4, 290, 560, 0, 0, 10, 15, 5, 1e-5, 0.1, 0));
//        enemies.push_back(new Enemy(this, this->scene, "x", p, 4, 200, 20, 0, 0, 10, 15, 5, 1e-5, 0.1, 0));

        doors.push_back(new Door(this, this, 590, 720-650-40, 20, 40));
        doors.push_back(new Door(this, this, 40, 720-300-40, 20, 40));

        itemX = 300 - 16;
        itemY = 720 - 550 - 16;

        boss = nullptr;

        type = "normal";
    }
    else if(file_name_ == "4"){
        walls.push_back(new Wall(this, 1280 - 200, 720 - 300, 200, 300));
        walls.push_back(new Wall(this, 1280-300, 720-200, 100, 200));
        walls.push_back(new Wall(this, 1280-400, 720-100, 100, 100));
        walls.push_back(new Wall(this, 0, 720 - 300, 200, 300));
        walls.push_back(new Wall(this, 200, 720-200, 100, 200));
        walls.push_back(new Wall(this, 300, 720-100, 100, 100));

        walls.push_back(new Wall(this, 300, 720 - 400, 680, 50));
        walls.push_back(new Wall(this, 400, 720 - 460, 480, 60));
        walls.push_back(new Wall(this, 1280/2 -30, 720 - 500, 60, 40));

        doors.push_back(new Door(this, this, 1280/2 -10, 720-40, 20, 40));

        itemX = 1280/2 - 8;
        itemY = 720 - 500 - 16;

        boss = nullptr;

        type = "treasure";
    }
    else if(file_name_ == "5"){

        walls.push_back(new Wall(this, 1280 - 300, 720 - 150, 300, 150));
        walls.push_back(new Wall(this, 0, 720 - 150, 300, 150));
        walls.push_back(new Wall(this, 200, 720 - 300, 300, 40));

        walls.push_back(new Wall(this, 1280 - 500, 720 - 300, 300, 40));

        walls.push_back(new Wall(this, 500, 720 - 450, 280, 40));
        walls.push_back(new Wall(this, 500, 720 - 120, 280, 40));

        doors.push_back(new Door(this, this, 1280/2 -10, 720-40, 20, 40));
        doors.push_back(new Door(this, this, 1280/2 -10, 720-450-40, 20, 40));

//        enemies.push_back(new Enemy(this, this->scene, "x", p, 4, 140, 170, 0, 0, 10, 15, 5, 1e-5, 0.1, 0));
//        enemies.push_back(new Enemy(this, this->scene, "x", p, 4, 1280-140, 170, 0, 0, 10, 15, 5, 1e-5, 0.1, 0));
//        enemies.push_back(new Enemy(this, this->scene, "x", p, 4, 1280/2, 140, 0, 0, 10, 15, 5, 1e-5, 0.1, 0));

        itemX = 1280/2 - 8;
        itemY = 720 - 120 - 16;

        boss = nullptr;

        type = "normal";
    }
    else if(file_name_ == "6"){

        walls.push_back(new Wall(this, 1280 - 200, 720 - 300, 200, 300));
        walls.push_back(new Wall(this, 1280-300, 720-200, 100, 200));
        walls.push_back(new Wall(this, 1280-400, 720-100, 100, 100));
        walls.push_back(new Wall(this, 1280 - 200, 0, 200, 300));
        walls.push_back(new Wall(this, 1280-300, 0, 100, 200));
        walls.push_back(new Wall(this, 1280-400, 0, 100, 100));
        walls.push_back(new Wall(this, 400, 720-650, 180, 40));
        walls.push_back(new Wall(this, 580, 0, 40, 110));
        walls.push_back(new Wall(this, 200, 720-550, 150, 20));
        walls.push_back(new Wall(this, 50, 720-450, 150, 20));
        walls.push_back(new Wall(this, 200, 720-350, 150, 20));
        walls.push_back(new Wall(this, 50, 720-250, 150, 20));
        walls.push_back(new Wall(this, 200, 720-150, 150, 20));
        walls.push_back(new Wall(this, 50, 720-50, 150, 50));
        walls.push_back(new Wall(this, 200, 720-25, 150, 25));

//        enemies.push_back(new Enemy(this, this->scene, "x", p, 4, 1280-250, 220, 0, 0, 10, 15, 5, 1e-5, 0.1, 0));
//        enemies.push_back(new Enemy(this, this->scene, "x", p, 4, 1280-350, 120, 0, 0, 10, 15, 5, 1e-5, 0.1, 0));
//        enemies.push_back(new Enemy(this, this->scene, "x", p, 4, 1280-450, 20, 0, 0, 10, 15, 5, 1e-5, 0.1, 0));

        doors.push_back(new Door(this, this, 500, 720-650-40, 20, 40));
        doors.push_back(new Door(this, this, 1280 - 100 - 20, 720-300-80, 40, 80));

        itemX = 125 - 8;
        itemY = 720 - 50 - 16;

        boss = nullptr;

        type = "normal";
    }
    else if(file_name_ == "7"){
        walls.push_back(new Wall(this, 1280-500, 720-300, 500, 300));
        walls.push_back(new Wall(this, 1280-550, 720-200, 50, 200));
        walls.push_back(new Wall(this, 1280-600, 720-100, 50, 100));
        walls.push_back(new Wall(this, 1280-700, 720-400, 100, 40));
        walls.push_back(new Wall(this, 1280-900, 720-500, 100, 40));
        walls.push_back(new Wall(this, 0, 720-600, 300, 40));

        doors.push_back(new Door(this, this, 1180, 720-300-40, 20, 40));

        itemX = 150 - 8;
        itemY = 720 - 600 - 16;

        boss = nullptr;

        type = "treasure";
    }
    else if(file_name_ == "8"){

        walls.push_back(new Wall(this, 0, 720 - 300, 150, 300));

        walls.push_back(new Wall(this, 250, 720 - 250, 300, 40));
        walls.push_back(new Wall(this, 1280 - 450, 720 - 250, 300, 40));
        walls.push_back(new Wall(this, 550, 720 - 380, 280, 40));
        walls.push_back(new Wall(this, 550, 720 - 120, 280, 40));

        doors.push_back(new Door(this, this, 150/2 -10, 720-300-40, 20, 40));
        doors.push_back(new Door(this, this, 1280-280, 720-40, 20, 40));

//        enemies.push_back(new Enemy(this, this->scene, "x", p, 4, 130, 320, 0, 0, 10, 15, 5, 1e-5, 0.1, 0));
//        enemies.push_back(new Enemy(this, this->scene, "x", p, 4, 300, 20, 0, 0, 10, 15, 5, 1e-5, 0.1, 0));
//        enemies.push_back(new Enemy(this, this->scene, "x", p, 4, 690, 400, 0, 0, 10, 15, 5, 1e-5, 0.1, 0));

        itemX = 1280/2 - 8;
        itemY = 720 - 120 - 16;

        boss = nullptr;

        type = "normal";
    }
    else if(file_name_ == "9"){
        walls.push_back(new Wall(this, 1280 - 300, 720 - 300, 300, 100));
        walls.push_back(new Wall(this, 1280-400, 720-200, 400, 100));
        walls.push_back(new Wall(this, 1280-500, 720-100, 500, 100));
        walls.push_back(new Wall(this, 400, 720 - 290, 150, 40));
        walls.push_back(new Wall(this, 400, 720 - 250, 350, 40));
        walls.push_back(new Wall(this, 100, 720 - 400, 250, 40));
        walls.push_back(new Wall(this, 420, 720 - 500, 80, 40));
        walls.push_back(new Wall(this, 550, 720 - 600, 500, 40));

        doors.push_back(new Door(this, this, 900, 720-600-40, 20, 40));
        doors.push_back(new Door(this, this, 1280 - 100 - 10, 720-300-40, 20, 40));

        itemX = 0;
        itemY = 0;

        boss = nullptr;

        type = "safe";
    }
    else if(file_name_ == "10"){

        walls.push_back(new Wall(this, 0, 720 - 600, 300, 40));

        walls.push_back(new Wall(this, 250, 720 - 450, 400, 40));
        walls.push_back(new Wall(this, 150, 720 - 200, 50, 20));
        walls.push_back(new Wall(this, 150, 720 - 100, 50, 20));

        walls.push_back(new Wall(this, 0, 720 - 300, 150, 300));

        walls.push_back(new Wall(this, 800, 720-450, 50, 450));
        walls.push_back(new Wall(this, 850, 720-350, 50, 350));
        walls.push_back(new Wall(this, 900, 720-250, 50, 250));
        walls.push_back(new Wall(this, 950, 720-150, 50, 150));
        walls.push_back(new Wall(this, 1000, 720-50, 50, 50));

        doors.push_back(new Door(this, this, 150/2 -10, 720-300-40, 20, 40));
        doors.push_back(new Door(this, this, 150 -10, 720-600-40, 20, 40));
        doors.push_back(new Door(this, this, 1280-120, 720-40, 20, 40));

//        enemies.push_back(new Enemy(this, this->scene, "x", p, 4, 480, 20, 0, 0, 10, 15, 5, 1e-5, 0.1, 0));
//        enemies.push_back(new Enemy(this, this->scene, "x", p, 4, 825, 470, 0, 0, 10, 15, 5, 1e-5, 0.1, 0));

        itemX = 450 - 8;
        itemY = 720 - 450 - 16;

        boss = nullptr;

        type = "normal";
    }
    else if(file_name_ == "11"){

        walls.push_back(new Wall(this, 0, 720 - 200, 300, 200));
        walls.push_back(new Wall(this, 300, 720 - 200, 50, 20));
        walls.push_back(new Wall(this, 300, 720 - 100, 50, 20));

        walls.push_back(new Wall(this, 800, 720 - 200, 300, 200));
        walls.push_back(new Wall(this, 1100, 720 - 100, 50, 100));

        walls.push_back(new Wall(this, 350, 720 - 350, 200, 40));
        walls.push_back(new Wall(this, 650, 720 - 450, 100, 40));
        walls.push_back(new Wall(this, 850, 720 - 550, 100, 40));
        walls.push_back(new Wall(this, 1050, 720 - 650, 150, 40));

        doors.push_back(new Door(this, this, 1200, 720-650-40, 20, 40));

        enemies.push_back(new Enemy(this, this->scene, "cross", "left_right_jump", p, 4, 150-10, 320, 0, 0, 10, 15, 5, 1e-5, 0.1, 0));
//        enemies.push_back(new Enemy(this, this->scene, "double", p, 4, 1065, 650+20, 0, 0, 10, 15, 5, 1e-5, 0.1, 0));
//        enemies.push_back(new Enemy(this, this->scene, "x", p, 4, 550, 20, 0, 0, 10, 15, 5, 1e-5, 0.1, 0));

        itemX = 450 - 8;
        itemY = 720 - 350 - 16;

        boss = nullptr;

        type = "normal";
    }
    else if(file_name_ == "12"){
        walls.push_back(new Wall(this, 1280 - 200, 720 - 300, 200, 300));
        walls.push_back(new Wall(this, 1280-300, 720-200, 100, 200));
        walls.push_back(new Wall(this, 1280-500, 720-100, 200, 100));
        walls.push_back(new Wall(this, 1280-600, 720-200, 100, 200));
        walls.push_back(new Wall(this, 1280 - 800, 720 - 300, 200, 300));
        walls.push_back(new Wall(this, 1280-900, 720-200, 100, 200));
        walls.push_back(new Wall(this, 1280-1000, 720-100, 100, 100));

        walls.push_back(new Wall(this, 1280 - 200, 0, 200, 300));
        walls.push_back(new Wall(this, 1280-300, 0, 100, 200));
        walls.push_back(new Wall(this, 1280-400, 0, 100, 100));

//        enemies.push_back(new Enemy(this, this->scene, "x", p, 4, 1280-700, 320, 0, 0, 10, 15, 5, 1e-5, 0.1, 0));
//        enemies.push_back(new Enemy(this, this->scene, "x", p, 4, 1280-400, 120, 0, 0, 10, 15, 5, 1e-5, 0.1, 0));

        doors.push_back(new Door(this, this, 50, 720-40, 20, 40));
        doors.push_back(new Door(this, this, 1280 - 100 - 20, 720-300-80, 40, 80));

        itemX = 1280-700 - 8;
        itemY = 720 - 300 - 16;

        boss = nullptr;

        type = "normal";
    }
    else if(file_name_ == "lamprey"){

        walls.push_back(new Wall(this, 50, 720-100, 150, 20));
        walls.push_back(new Wall(this, 300, 720-100, 150, 20));
        walls.push_back(new Wall(this, 550, 720-100, 150, 20));
        walls.push_back(new Wall(this, 800, 720-100, 150, 20));

        walls.push_back(new Wall(this, 0, 720-250, 50, 20));
        walls.push_back(new Wall(this, 150, 720-250, 150, 20));
        walls.push_back(new Wall(this, 400, 720-250, 150, 20));
        walls.push_back(new Wall(this, 650, 720-250, 150, 20));

        walls.push_back(new Wall(this, 50, 720-400, 150, 20));
        walls.push_back(new Wall(this, 300, 720-400, 150, 20));
        walls.push_back(new Wall(this, 550, 720-400, 150, 20));

        walls.push_back(new Wall(this, 0, 720-550, 50, 20));
        walls.push_back(new Wall(this, 150, 720-550, 150, 20));
        walls.push_back(new Wall(this, 400, 720-550, 150, 20));

        doors.push_back(new Door(this, this, 0, 720-40, 20, 40));

        boss = new Boss(this, scene, "lamprey", p, 1280-150, 720/2, 0, 0, 50, 300, 200, 0, 1e-5, 0.1, 0);

        itemX =  475 - 8;
        itemY = 720 - 550 -16;

        type = "boss";
    }
    else if (file_name_ == "priest"){

        walls.push_back(new Wall(this, 450, 620, 150, 40));
        walls.push_back(new Wall(this, 200,660, 40, 60));

        doors.push_back(new Door(this, this, 0, 720-40, 20, 40));

        boss = new Boss(this, scene, "priest", p, 640, 360, 0, 0, 100, 100, 200, 5, 1e-5, 0.1, 0);

        itemX =  250;
        itemY = 720 - 16;

        type = "boss";
    }
    else if(file_name_ == "angel"){
        walls.push_back(new Wall(this, 450, 620, 150, 40));
        walls.push_back(new Wall(this, 200,660, 40, 60));

        doors.push_back(new Door(this, this, 0, 720-40, 20, 40));

        boss = new Boss(this, scene, "angel", p, 640, 360, 0, 0, 100, 40, 5, 1e-5, 0.1, 0);

        itemX =  250;
        itemY = 720 - 16;

        type = "boss";
    }
    else if(file_name_ == "expelled"){
        walls.push_back(new Wall(this, 450, 620, 150, 40));
        walls.push_back(new Wall(this, 200,660, 40, 60));

        doors.push_back(new Door(this, this, 0, 720-40, 20, 40));

        boss = new Boss(this, scene, "expelled", p, 640, 360, 0, 0, 100, 40, 5, 1e-5, 0.1, 0);

        itemX =  250;
        itemY = 720 - 16;

        type = "boss";
    }
}
Room::~Room() {
    //should it delete the content of the lists?

    walls.clear();
    enemies.clear();
    doors.clear();

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

    for(auto k = doors.begin(); k!=doors.end(); k++){
        scene->removeItem(*k);
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
    item = new Item(this, "Heart", 1, 0.2);
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
