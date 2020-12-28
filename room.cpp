#include "room.h"

Room::Room(QObject *parent, QGraphicsScene *scene, std::string file_name_) : QObject(parent), scene(scene), v_limit(720), h_limit(1280) {
    //load_room(file_name_);

    walls.push_back(new Wall(this, 200, 620, 150, 40));
    walls.push_back(new Wall(this, 200,660, 40, 60));

    enemies.push_back(new Enemy(this, 1, 700, 10, 0, 0, 10, 15, 5, 1e-5, 0.1, 0));
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

void Room::check_collitions() {

    for(auto k = enemies.begin(); k!=enemies.end(); k++){

        /*------EDGES------*/
        if((*k)->getX() < (*k)->getRadio()) { //colicion en x por la izquierda
            (*k)->set_velX((*k)->getRadio(), -1*(*k)->getE()*(*k)->getVx());
        }
        if((*k)->getX() > h_limit - (*k)->getRadio()) { //colicion en x por la derecha
            (*k)->set_velX(h_limit - (*k)->getRadio(), -1*(*k)->getE()*(*k)->getVx());
        }
        if((*k)->getY() < (*k)->getRadio()) { //colicion en y por arriba (callendo)
            (*k)->set_velY((*k)->getRadio(), -1*(*k)->getE()*(*k)->getVy());
            //(*k)->setJumping(false);
        }

        if((*k)->getY() > v_limit - (*k)->getRadio()) { //colicion en y por abajo (saltando)
            (*k)->set_velY(v_limit - (*k)->getRadio(), -1*(*k)->getE()*(*k)->getVy());
        }


        for(int i = 0; i < (*k)->collidingItems().size(); i++){
              /*------WALLS------*/
//            if(typeid( *((*k)->collidingItems()[i]) )== typeid(Wall)){

//                if((*k)->getX() < (*k)->collidingItems().at(i)->x()) { //colicion en x por la izquierda

//                    //p->set_velX(p->collidingItems().at(k)->x() - p->getRadio(), -1*p->getE()*p->getVx());
//                    //(*k)->set_velX((*k)->collidingItems().at(i)->x() - (*k)->getRadio() + ((*k)->getDirection() * (*k)->getMovement_speed()), (*k)->getVx()); //fails ******

//                }
//                if((*k)->getX() > (*k)->collidingItems().at(i)->x() + (*k)->collidingItems().at(i)->boundingRect().width()) { //colicion en x por la derecha

//                    //p->set_velX(p->collidingItems().at(k)->x() + p->collidingItems().at(k)->boundingRect().width() + p->getRadio(), -1*p->getE()*p->getVx());
//                    //(*k)->set_velX((*k)->collidingItems().at(i)->x() + (*k)->collidingItems().at(i)->boundingRect().width() + (*k)->getRadio() + ((*k)->getDirection() * (*k)->getMovement_speed()), (*k)->getVx()); //fails ******
//                }
//                if((*k)->getY() > v_limit - (*k)->collidingItems().at(i)->y()) { //colicion en y por arriba (callendo)

//                    (*k)->set_velY(v_limit - (*k)->collidingItems().at(i)->y() + (*k)->getRadio(), -1*(*k)->getE()*(*k)->getVy());
//                    //(*k)->setJumping(false);

//                }
//                if((*k)->getY() < v_limit - ((*k)->collidingItems().at(i)->y() + (*k)->collidingItems().at(i)->boundingRect().height())) { //colicion en y por abajo (saltando)

//                    (*k)->set_velY(v_limit - ((*k)->collidingItems().at(i)->y() + (*k)->collidingItems().at(i)->boundingRect().height() + (*k)->getRadio()), -1*(*k)->getE()*(*k)->getVy());

//                }
//            }

            if(typeid( *((*k)->collidingItems()[i]) ) == typeid(Proyectile)){
                (*k)->take_damage(20);

                //delete proyectile ****** get proyectile damage

                //((*k)->collidingItems()[i])->
            }


        } //colliding items for


    } //enemies for
}

void Room::update() {

    for(auto k = enemies.begin(); k!=enemies.end(); ){
        (*k)->update();

        if((*k)->getHealth() <= 0){
            scene->removeItem(*k);
            k = enemies.erase(k);
        }
        else
            ++k;
    }

    check_collitions();
}
