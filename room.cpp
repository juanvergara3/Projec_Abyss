#include "room.h"

Room::Room(QObject *parent, std::string file_name_) : QObject(parent) {
    load_walls(file_name_);

    walls.push_back(new Wall(this, 200, 620, 150, 40));
    walls.push_back(new Wall(this, 200,660, 40, 60));
}
Room::~Room() {

}

void Room::load_walls(QGraphicsScene *scene) {
//    for(int k = 0; k<walls.size(); k++){
//        scene->addItem(walls.at(k));
//        walls.at(k)->setPos(walls.at(k)->getPosx(), walls.at(k)->getPosy());
//    }

    for(auto k = walls.begin(); k!=walls.end(); k++){
        scene->addItem(*k);
        (*k)->setPos((*k)->getPosx(), (*k)->getPosy());

    }
}

void Room::load_walls(std::string file_name) {

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
