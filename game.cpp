#include "game.h"

Game::Game(QGraphicsScene * scene, std::list<Proyectile *> *p, std::string seed, std::string type, std::string p1_name, std::string p2_name)
    : scene(scene), proyectiles(p), type(type)
{
    srand(unsigned(time(NULL)));

    floor1 = new Floor(scene, proyectiles, 1);
    floor2 = new Floor(scene, proyectiles, 2);
    floor3 = new Floor(scene, proyectiles, 3);

    floor1->boss->boss_door->setNext(floor2);
    floor2->boss->boss_door->setNext(floor3);

    current_floor = floor1;
    current_room = floor1->safe;

    if(!seed.empty()) {
        for(auto k = seed.begin(); k != seed.end(); k++)
            this->seed+= int(*k);
    }
    else
        this->seed = rand();

    srand(this->seed);

    load_items("items.txt");
    shuffle_items();

    if(type == "singleplayer"){
        p1 = new Player(nullptr, scene, p1_name, proyectiles, 0, 0, 0, 0, 0, 20, 8, 4, 1e-5, 0.1, 0);
        p2 = nullptr;
    }
    else if (type == "multiplayer") {
        p1 = new Player(nullptr, scene, p1_name, proyectiles, 0, 0, 0, 0, 0, 20, 8, 4, 1e-5, 0.1, 0);
        p2 = new Player(nullptr, scene, p2_name, proyectiles, 200, 50, 0, 0, 0, 20, 8, 4, 1e-5, 0.1, 0);
    }
}

Game::Game(std::string file_name, QGraphicsScene * scene, std::list<Proyectile *> *p)
    : scene(scene), proyectiles(p)
{

    srand(unsigned(time(NULL)));

    floor1 = new Floor(scene, proyectiles, 1);
    floor2 = new Floor(scene, proyectiles, 2);
    floor3 = new Floor(scene, proyectiles, 3);

    floor1->boss->boss_door->setNext(floor2); // might fail if the floor is alredy cleared
    floor2->boss->boss_door->setNext(floor3);

    std::fstream file (file_name, std:: fstream::in | std::fstream::binary);

    float x, y;
    int statPos;
    std::string name, temp, shooting_mode;
    float max_health, health, damage, shot_speed, movement_speed, jump_Speed, g, g_p, r, r_p, e;

    if(file.is_open()){

        file>>seed;

        file>>temp;
        if(temp == "1")
            current_floor = floor1;
        else if (temp == "2")
            current_floor = floor2;
        else if (temp == "3")
            current_floor = floor3;

        file>>temp;
        if(temp == "safe")
            current_room = current_floor->safe;
        else if (temp == "boss")
            current_room = current_floor->boss;
        else if (temp == "item")
            current_room = current_floor->treasure;
        else if (temp == "1")
            current_room = current_floor->r1;
        else if (temp == "2")
            current_room = current_floor->r2;
        else if (temp == "3")
            current_room = current_floor->r3;
        else if (temp == "4")
            current_room = current_floor->r4;

        file>>type;

        if(type == "singleplayer"){

            file>>temp;
            x = std::stof(temp);

            file>>temp;
            y = std::stof(temp);

            file>>temp;
            statPos = std::stoi(temp);

            file>>name;

            file>>temp;
            max_health = std::stof(temp);

            file>>temp;
            health = std::stof(temp);

            file>>temp;
            damage = std::stof(temp);

            file>>temp;
            shot_speed = std::stof(temp);

            file>>temp;
            movement_speed = std::stof(temp);

            file>>temp;
            jump_Speed = std::stof(temp);

            file>>temp;
            g = std::stof(temp);

            file>>temp;
            g_p = std::stof(temp);

            file>>temp;
            r = std::stof(temp);

            file>>temp;
            r_p = std::stof(temp);

            file>>temp;
            e = std::stof(temp);

            file>>temp;

            p1 = new Player(nullptr, scene, proyectiles, int(x), int(y), statPos, name, max_health, health, damage, shot_speed, movement_speed, jump_Speed, g, g_p, r, r_p, e, temp);
            p2 = nullptr;
        }
        else if(type == "multiplayer"){

            file>>temp;
            x = std::stof(temp);

            file>>temp;
            y = std::stof(temp);

            file>>temp;
            statPos = std::stoi(temp);

            file>>name;

            file>>temp;
            max_health = std::stof(temp);

            file>>temp;
            health = std::stof(temp);

            file>>temp;
            damage = std::stof(temp);

            file>>temp;
            shot_speed = std::stof(temp);

            file>>temp;
            movement_speed = std::stof(temp);

            file>>temp;
            jump_Speed = std::stof(temp);

            file>>temp;
            g = std::stof(temp);

            file>>temp;
            g_p = std::stof(temp);

            file>>temp;
            r = std::stof(temp);

            file>>temp;
            r_p = std::stof(temp);

            file>>temp;
            e = std::stof(temp);

            file>>temp;

            p1 = new Player(nullptr, scene, proyectiles, int(x), int(y), statPos, name, max_health, health, damage, shot_speed, movement_speed, jump_Speed, g, g_p, r, r_p, e, temp);

            file>>temp;
            x = std::stof(temp);

            file>>temp;
            y = std::stof(temp);

            file>>temp;
            statPos = std::stoi(temp);

            file>>name;

            file>>temp;
            max_health = std::stof(temp);

            file>>temp;
            health = std::stof(temp);

            file>>temp;
            damage = std::stof(temp);

            file>>temp;
            shot_speed = std::stof(temp);

            file>>temp;
            movement_speed = std::stof(temp);

            file>>temp;
            jump_Speed = std::stof(temp);

            file>>temp;
            g = std::stof(temp);

            file>>temp;
            g_p = std::stof(temp);

            file>>temp;
            r = std::stof(temp);

            file>>temp;
            r_p = std::stof(temp);

            file>>temp;
            e = std::stof(temp);

            file>>temp;

            p2 = new Player(nullptr, scene, proyectiles, int(x), int(y), statPos, name, max_health, health, damage, shot_speed, movement_speed, jump_Speed, g, g_p, r, r_p, e, temp);
        }

        for(int k = 0; k < 8; k++){ // floor 1

            file>>temp;

            switch (k) {

            case 0:{
                if(temp == "1")
                    floor1->setClear_state(true); // this might not be enough
                break;
            }
            case 1:{
                if(temp == "1")
                    floor1->safe->clear_room();
                break;
            }
            case 2:{
                if(temp == "1")
                    floor1->boss->clear_room();
                break;
            }
            case 3:{
                if(temp == "1")
                    floor1->treasure->clear_room();
                break;
            }
            case 4:{
                if(temp == "1")
                    floor1->r1->clear_room();
                break;
            }
            case 5:{
                if(temp == "1")
                    floor1->r2->clear_room();
                break;
            }
            case 6:{
                if(temp == "1")
                    floor1->r3->clear_room();
                break;
            }
            case 7:{
                if(temp == "1")
                    floor1->r4->clear_room();
                break;
            }
            }
        }
        for(int k = 0; k < 8; k++){ // floor 2

            file>>temp;

            switch (k) {

            case 0:{
                if(temp == "1")
                    floor2->setClear_state(true);
                break;
            }
            case 1:{
                if(temp == "1")
                    floor2->safe->clear_room();
                break;
            }
            case 2:{
                if(temp == "1")
                    floor2->boss->clear_room();
                break;
            }
            case 3:{
                if(temp == "1")
                    floor2->treasure->clear_room();
                break;
            }
            case 4:{
                if(temp == "1")
                    floor2->r1->clear_room();
                break;
            }
            case 5:{
                if(temp == "1")
                    floor2->r2->clear_room();
                break;
            }
            case 6:{
                if(temp == "1")
                    floor2->r3->clear_room();
                break;
            }
            case 7:{
                if(temp == "1")
                    floor2->r4->clear_room();
                break;
            }
            }
        }
        for(int k = 0; k < 8; k++){ // floor 3

            file>>temp;

            switch (k) {

            case 0:{
                if(temp == "1")
                    floor3->setClear_state(true); // this might not be enough
                break;
            }
            case 1:{
                if(temp == "1")
                    floor3->safe->clear_room();
                break;
            }
            case 2:{
                if(temp == "1")
                    floor3->boss->clear_room();
                break;
            }
            case 3:{
                if(temp == "1")
                    floor3->treasure->clear_room();
                break;
            }
            case 4:{
                if(temp == "1")
                    floor3->r1->clear_room();
                break;
            }
            case 5:{
                if(temp == "1")
                    floor3->r2->clear_room();
                break;
            }
            case 6:{
                if(temp == "1")
                    floor3->r3->clear_room();
                break;
            }
            case 7:{
                if(temp == "1")
                    floor3->r4->clear_room();
                break;
            }
            }
        }

        item_bank.clear();

        short counter = 1;
        while (file>>temp){

            if(counter == 1){
                std::replace( temp.begin(), temp.end(), '_', ' ');
                name = temp;
            }
            else if(counter == 2){
                max_health = std::stof(temp);
            }
            else if(counter == 3){
                health = std::stof(temp);
            }
            else if(counter == 4){
                damage = std::stof(temp);
            }
            else if(counter == 5){
                shot_speed = std::stof(temp);
            }
            else if(counter == 6){
                movement_speed = std::stof(temp);
            }
            else if(counter == 7){
                jump_Speed = std::stof(temp);
            }
            else if(counter == 8){
                g = std::stof(temp);
            }
            else if(counter == 9){
                g_p= std::stof(temp);
            }
            else if(counter == 10){
                r = std::stof(temp);
            }
            else if(counter == 11){
                r_p = std::stof(temp);
            }
            else if(counter == 12){
                e = std::stof(temp);
            }
            else if(counter == 13){
                shooting_mode = temp;
            }
            else if(counter == 14){
                item_bank.push_back(new Item(nullptr, name, max_health, health, damage, shot_speed, movement_speed, jump_Speed, g, g_p, r, r_p, e, shooting_mode, temp));
                counter = 0;
            }
            counter++;
        }

        file.close();
    }

    srand(seed);
}
Game::~Game() {
    delete floor1;
    delete floor2;
    delete floor3;

    item_bank.clear();

    scene = nullptr;
    proyectiles = nullptr;

    delete p1;
    delete p2;
}

void Game::reset() {
    delete floor1;
    delete floor2;
    delete floor3;

    floor1 = new Floor(scene, proyectiles, 1);
    floor2 = new Floor(scene, proyectiles, 2);
    floor3 = new Floor(scene, proyectiles, 3);

    current_floor = floor1;
    current_room = floor1->safe;

    srand(seed);

    item_bank.clear();
    load_items("items.txt");
    shuffle_items();

    if(type == "singleplayer"){

        std::string p1_name, p2_name;

        p1_name = p1->getName();

        delete p1;

        p1 = new Player(nullptr, scene, p1_name, proyectiles, 0, 0, 0, 0, 0, 20, 8, 4, 1e-5, 0.1, 0);
    }
    else if (type == "multiplayer") {

        std::string p1_name, p2_name;

        p1_name = p1->getName();
        p2_name = p2->getName();

        delete p1;
        delete p2;

        p1 = new Player(nullptr, scene, p1_name, proyectiles, 0, 0, 0, 0, 0, 20, 8, 4, 1e-5, 0.1, 0);
        p2 = new Player(nullptr, scene, p2_name, proyectiles, 200, 50, 0, 0, 0, 20, 8, 4, 1e-5, 0.1, 0);
    }
}

void Game::save_game(std::string file_name) {

    std::fstream file (file_name, std:: fstream::out | std::fstream::binary);
    if(file.is_open()){

        file<<seed<<"\r\n";
        file<<current_floor->getNum()<<'\t';
        file<<current_room->getName()<<"\r\n";

        if(type == "singleplayer"){

            //player data ***make new constructor***
            file<<"singleplayer"<<"\r\n";
            file<<p1->getX()<<'\t';
            file<<p1->getY()<<'\t';
            file<<p1->getStatPos()<<'\t';
            file<<p1->getName()<<'\t';
            file<<p1->getMax_health()<<'\t';
            file<<p1->getHealth()<<'\t'; // remember to check if the player is alive :p
            file<<p1->getDamage()<<'\t';
            file<<p1->getShot_speed()<<'\t';
            file<<p1->getMovement_speed()<<'\t';
            file<<p1->getJump_Speed()<<'\t';
            file<<p1->getG()<<'\t';
            file<<p1->getG_p()<<'\t';
            file<<p1->getRadio()<<'\t';
            file<<p1->getR_p()<<'\t';
            file<<p1->getE()<<'\t';
            file<<p1->getShooting_mode()<<"\r\n";
        }
        else if(type == "multiplayer"){

            file<<"multiplayer"<<"\r\n";

            file<<p1->getX()<<'\t';
            file<<p1->getY()<<'\t';
            file<<p1->getStatPos()<<'\t';
            file<<p1->getName()<<'\t';
            file<<p1->getMax_health()<<'\t';
            file<<p1->getHealth()<<'\t';
            file<<p1->getDamage()<<'\t';
            file<<p1->getShot_speed()<<'\t';
            file<<p1->getMovement_speed()<<'\t';
            file<<p1->getJump_Speed()<<'\t';
            file<<p1->getG()<<'\t';
            file<<p1->getG_p()<<'\t';
            file<<p1->getRadio()<<'\t';
            file<<p1->getR_p()<<'\t';
            file<<p1->getE()<<'\t';
            file<<p1->getShooting_mode()<<"\r\n";

            file<<p2->getX()<<'\t';
            file<<p2->getY()<<'\t';
            file<<p2->getStatPos()<<'\t';
            file<<p2->getName()<<'\t';
            file<<p2->getMax_health()<<'\t';
            file<<p2->getHealth()<<'\t';
            file<<p2->getDamage()<<'\t';
            file<<p2->getShot_speed()<<'\t';
            file<<p2->getMovement_speed()<<'\t';
            file<<p2->getJump_Speed()<<'\t';
            file<<p2->getG()<<'\t';
            file<<p2->getG_p()<<'\t';
            file<<p2->getRadio()<<'\t';
            file<<p2->getR_p()<<'\t';
            file<<p2->getE()<<'\t';
            file<<p2->getShooting_mode()<<"\r\n";
        }

        //floors and rooms
        file<<floor1->getClear_state()<<'\t';
        file<<floor1->safe->isClear()<<'\t';
        file<<floor1->boss->isClear()<<'\t';
        file<<floor1->treasure->isClear()<<'\t';
        file<<floor1->r1->isClear()<<'\t';
        file<<floor1->r2->isClear()<<'\t';
        file<<floor1->r3->isClear()<<'\t';
        file<<floor1->r4->isClear()<<"\r\n";

        file<<floor2->getClear_state()<<'\t';
        file<<floor2->safe->isClear()<<'\t';
        file<<floor2->boss->isClear()<<'\t';
        file<<floor2->treasure->isClear()<<'\t';
        file<<floor2->r1->isClear()<<'\t';
        file<<floor2->r2->isClear()<<'\t';
        file<<floor2->r3->isClear()<<'\t';
        file<<floor2->r4->isClear()<<"\r\n";

        file<<floor3->getClear_state()<<'\t';
        file<<floor3->safe->isClear()<<'\t';
        file<<floor3->boss->isClear()<<'\t';
        file<<floor3->treasure->isClear()<<'\t';
        file<<floor3->r1->isClear()<<'\t';
        file<<floor3->r2->isClear()<<'\t';
        file<<floor3->r3->isClear()<<'\t';
        file<<floor3->r4->isClear()<<"\r\n";

        //items
        std::string name, sprite;

        for(auto k = item_bank.begin(); k != item_bank.end(); k++){

            name = (*k)->getName();
            std::replace( name.begin(), name.end(), ' ', '_');

            file<<name<<'\t';
            file<<(*k)->getMax_health()<<'\t';
            file<<(*k)->getHealth()<<'\t';
            file<<(*k)->getDamage()<<'\t';
            file<<(*k)->getShot_speed()<<'\t';
            file<<(*k)->getMovement_speed()<<'\t';
            file<<(*k)->getJump_Speed()<<'\t';
            file<<(*k)->getG_player()<<'\t';
            file<<(*k)->getG_proyectiles()<<'\t';
            file<<(*k)->getR_player()<<'\t';
            file<<(*k)->getR_proyectiles()<<'\t';
            file<<(*k)->getE_player()<<'\t';
            file<<(*k)->getShooting_mode()<<'\t';
            file<<(*k)->getSprite_name()<<"\r\n";
        }
        file.close();
    }
}

Item *Game::get_random_item() {
    Item * i = item_bank.back();
    if(i != nullptr) {
        item_bank.pop_back();
        return i;
    }
    return nullptr;
}

Room *Game::getCurrent_room() const{
    return current_room;
}
void Game::setCurrent_room(Room *value){
    current_room = value;
}

Floor *Game::getCurrent_floor() const{
    return current_floor;
}
void Game::setCurrent_floor(Floor *value){
    current_floor = value;
}

void Game::shuffle_items() {
    std::vector<Item*> *temp = new std::vector<Item*>(item_bank.begin(), item_bank.end());
    std::random_shuffle(temp->begin(), temp->end());
    std::copy(temp->begin(), temp->end(), item_bank.begin());
    temp->clear();
    delete temp;
}

void Game::load_items(std::string file_name) {
    std::fstream file (file_name, std:: fstream::in | std::fstream::binary);

    if(file.is_open()){

        item_bank.clear();

        std::string temp, name;
        float max_health, health, damage, shot_speed, movement_speed, jump_Speed, g_player, g_proyectiles, r_player, r_proyectiles, e_player;
        std::string Shooting_mode;
        short counter = 1;

        while (file>>temp){

            if(counter == 1){
                std::replace( temp.begin(), temp.end(), '_', ' ');
                name = temp;
            }
            else if(counter == 2){
                max_health = std::stof(temp);
            }
            else if(counter == 3){
                health = std::stof(temp);
            }
             else if(counter == 4){
                damage = std::stof(temp);
            }
            else if(counter == 5){
               shot_speed = std::stof(temp);
           }
            else if(counter == 6){
               movement_speed = std::stof(temp);
           }
            else if(counter == 7){
               jump_Speed = std::stof(temp);
           }
            else if(counter == 8){
               g_player = std::stof(temp);
           }
            else if(counter == 9){
               g_proyectiles = std::stof(temp);
           }
            else if(counter == 10){
               r_player = std::stof(temp);
           }
            else if(counter == 11){
               r_proyectiles  = std::stof(temp);
           }
            else if(counter == 12){
               e_player = std::stof(temp);
           }
            else if(counter == 13){
               Shooting_mode = temp;
           }
            else if(counter == 14){
                item_bank.push_back(new Item(nullptr, name, max_health, health, damage, shot_speed, movement_speed, jump_Speed, g_player, g_proyectiles, r_player, r_proyectiles, e_player, Shooting_mode, temp));
                counter = 0;
           }
            counter++;
        }
        file.close();
    }
}

std::string Game::getType() const {
    return type;
}
Player *Game::getP1() const {
    return p1;
}
Player *Game::getP2() const {
    return p2;
}
Floor *Game::getFloor1() const {
    return floor1;
}
unsigned int Game::getSeed() const {
    return seed;
}
