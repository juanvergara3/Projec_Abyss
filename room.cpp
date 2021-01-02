#include "room.h"

std::list<Enemy *> Room::getEnemies() const
{
    return enemies;
}

Room::Room(QObject *parent, QGraphicsScene *scene, std::list<Proyectile *> *p, std::string file_name_) : QObject(parent), scene(scene), v_limit(720), h_limit(1280) {
    //load_room(file_name_);

    walls.push_back(new Wall(this, 200, 620, 150, 40));
    walls.push_back(new Wall(this, 200,660, 40, 60));
    walls.push_back(new Wall(this, 700, 720-80, 40, 80));

    enemies.push_back(new Enemy(this, this->scene, "x", p, 1, 700, 300, 0, 0, 10, 15, 5, 1e-5, 0.1, 0));
}
Room::~Room() {

}

void Room::load_room() {
//    for(int k = 0; k<walls.size(); k++){
//        scene->addItem(walls.at(k));
//        walls.at(k)->setPos(walls.at(k)->getPosx(), walls.at(k)->getPosy());
//    }

    for(auto k = walls.begin(); k!=walls.end(); k++){
        scene->addItem(*k);
        (*k)->setPos((*k)->getPosx(), (*k)->getPosy());
    }

    for(auto k = enemies.begin(); k!=enemies.end(); k++){
        scene->addItem(*k);
        (*k)->setPos((*k)->getX(), (*k)->getY());
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

//void Room::check_collitions() {

//    for(auto k = enemies.begin(); k!=enemies.end(); k++){

//        /*------EDGES------*/
//        if((*k)->getX() < (*k)->getRadio()) { //colicion en x por la izquierda
//            (*k)->set_velX((*k)->getRadio(), -1*(*k)->getE()*(*k)->getVx());
//        }
//        if((*k)->getX() > h_limit - (*k)->getRadio()) { //colicion en x por la derecha
//            (*k)->set_velX(h_limit - (*k)->getRadio(), -1*(*k)->getE()*(*k)->getVx());
//        }
//        if((*k)->getY() < (*k)->getRadio()) { //colicion en y por arriba (callendo)
//            (*k)->set_velY((*k)->getRadio(), -1*(*k)->getE()*(*k)->getVy());
//            //(*k)->setJumping(false);
//        }

//        if((*k)->getY() > v_limit - (*k)->getRadio()) { //colicion en y por abajo (saltando)
//            (*k)->set_velY(v_limit - (*k)->getRadio(), -1*(*k)->getE()*(*k)->getVy());
//        }


//        for(int i = 0; i < (*k)->collidingItems().size(); i++){


//            if(typeid( *((*k)->collidingItems()[i]) ) == typeid(Proyectile)){
//                (*k)->take_damage(20);

//                //delete proyectile ****** get proyectile damage

//                //((*k)->collidingItems()[i])->
//            }


//        } //colliding items for


//    } //enemies for
//}
