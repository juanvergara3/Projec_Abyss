#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pausemenu.h"

MainWindow::MainWindow(QWidget *parent, PauseMenu *p) : QMainWindow(parent), ui(new Ui::MainWindow), h_limit(1280), v_limit(720), pause_menu(p) {
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0 ,1280, 720);
    ui->graphicsView->setScene(scene);
    ui->centralwidget->adjustSize();
    scene->addRect(scene->sceneRect());
    ui->graphicsView->resize(scene->width(), scene->height());
    ui->graphicsView->setFocus();
    this->resize(ui->graphicsView->width()+100, ui->graphicsView->height()+100);

    p1 = new Player(this, scene, "P1", &proyectiles, 0, 0, 0, 0, 0, 20, 8, 4, 1e-5, 0.1, 0);
    p2 = new Player(this, scene, "P2", &proyectiles, 200, 1000, 0, 0, 0, 20, 8, 4, 1e-5, 0.1, 0);
    //p2 = nullptr;

    current_floor = new Floor(scene, &proyectiles, 2);

    current_room = current_floor->safe;
    current_room->load_room();
    enemies = current_room->getEnemies();

    current_room_type = current_room->getType();

    if(current_room_type == "boss") {
        boss = current_room->getBoss();
        enemies.clear();
    }
    else if(current_room_type == "normal") {
        enemies = current_room->getEnemies();
        boss = nullptr;
    }

    scene->addItem(p1);
    if(p2 != nullptr)
        scene->addItem(p2);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update_bodies()));
    timer->start(3);

    unsigned int i = 4294967295;
    srand(i);

    load_items("items.txt");

    std::vector<Item*> *temp = new std::vector<Item*>(item_bank.begin(), item_bank.end());
    std::random_shuffle(temp->begin(), temp->end());
    std::copy(temp->begin(), temp->end(), item_bank.begin());
    temp->clear();
    delete temp;
}
MainWindow::~MainWindow() {

    current_room = nullptr;
    boss = nullptr;

    enemies.clear();
    item_bank.clear();

    delete current_room;
    delete timer;
    delete current_floor;
    delete p1;
    delete p2;
    delete scene;
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event) {

    if (event->isAutoRepeat())
        return;

    if(event->key() == Qt::Key_D){
        //p1->set_velX(p1->getX(), p1->getMovement_speed());
        p1->addDirection(1);
        p1->setSight(1);
    }
    if(event->key() == Qt::Key_A){
        //p1->set_velX(p1->getX(), -p1->getMovement_speed());
        p1->addDirection(-1);
        p1->setSight(-1);
    }
    if(event->key() == Qt::Key_W){
        if(!p1->getJumping())
            p1->set_velY(p1->getY(), p1->getJump_Speed());
        p1->setJumping(true);
    }
    if(event->key() == Qt::Key_S){
        p1->set_velY(p1->getY(), -p1->getJump_Speed());
    }
    if(event->key() == Qt::Key_Space){
        p1->shoot();
    }
    if(event->key() == Qt::Key_E){

        for(int k = 0; k < p1->collidingItems().size(); k++){

            if(typeid( *(p1->collidingItems()[k]) ) == typeid(Door)){

                Door *d = dynamic_cast<Door*>(p1->collidingItems()[k]);

                for (auto k = proyectiles.begin(); k != proyectiles.end(); ) { //clears the screen from proyectiles
                    scene->removeItem(*k);
                    delete (*k);
                    k = proyectiles.erase(k);
                }

                p1->set_vel(d->getLink()->getPosx(), v_limit - d->getLink()->getPosy(), 0, 0);
                if(p2 != nullptr)
                    p2->set_vel(d->getLink()->getPosx(), v_limit - d->getLink()->getPosy(), 0, 0);

                current_room->deload_room();
                current_room = d->getLink()->getSelf();
                current_room->load_room();

                current_room_type = current_room->getType();

                if(current_room_type == "boss") {
                    boss = current_room->getBoss();
                    enemies.clear();
                }
                else if(current_room_type == "normal") {
                    enemies = current_room->getEnemies();
                    boss = nullptr;
                }

                scene->removeItem(p1);
                scene->addItem(p1);
                if(p2 != nullptr){
                    scene->removeItem(p2);
                    scene->addItem(p2);
                }

                //scene->removeItem(d);
            }
            if(typeid( *(p1->collidingItems()[k]) ) == typeid(Item)){

                Item *i = dynamic_cast<Item*>(p1->collidingItems()[k]);

                p1->update_stats(i);

                current_room->remove_item();

            }
        }
    }

    if(p2 != nullptr){
        if(event->key() == Qt::Key_L){
            //p2->set_velX(p1->getX(), p2->getMovement_speed());
            p2->addDirection(1);
            p2->setSight(1);
        }
        if(event->key() == Qt::Key_J){
            //p2->set_velX(p1->getX(), -p2->getMovement_speed());
            p2->addDirection(-1);
            p2->setSight(-1);
        }
        if(event->key() == Qt::Key_I){
            if(!p2->getJumping())
                p2->set_velY(p2->getY(), p2->getJump_Speed());
            p2->setJumping(true);
        }
        if(event->key() == Qt::Key_K){
            p2->set_velY(p2->getY(), -p2->getJump_Speed());
        }
        if(event->key() == Qt::Key_O){

            for(int k = 0; k < p2->collidingItems().size(); k++){

                if(typeid( *(p2->collidingItems()[k]) ) == typeid(Door)){

                    Door *d = dynamic_cast<Door*>(p2->collidingItems()[k]);

                    for (auto k = proyectiles.begin(); k != proyectiles.end(); ) { //clears the screen from proyectiles
                        scene->removeItem(*k);
                        delete (*k);
                        k = proyectiles.erase(k);
                    }

                    p1->set_vel(d->getLink()->getPosx(), v_limit - d->getLink()->getPosy(), 0, 0);
                    p2->set_vel(d->getLink()->getPosx(), v_limit - d->getLink()->getPosy(), 0, 0);

                    current_room->deload_room();
                    current_room = d->getLink()->getSelf();
                    current_room->load_room();

                    current_room_type = current_room->getType();

                    if(current_room_type == "boss") {
                        boss = current_room->getBoss();
                        enemies.clear();
                    }
                    else if(current_room_type == "normal") {
                        enemies = current_room->getEnemies();
                        boss = nullptr;
                    }

                    scene->removeItem(p1);
                    scene->addItem(p1);
                    scene->removeItem(p2);
                    scene->addItem(p2);

                    //scene->removeItem(d);
                }
                if(typeid( *(p2->collidingItems()[k]) ) == typeid(Item)){

                    Item *i = dynamic_cast<Item*>(p2->collidingItems()[k]);

                    p2->update_stats(i);

                    current_room->remove_item();

                }
            }
        }
    }

    if(event->key() == Qt::Key_Escape){
        pause();
        this->hide();
        pause_menu->showMaximized();
    }
}
void MainWindow::keyReleaseEvent(QKeyEvent *event) {

    if (event->isAutoRepeat()) //this allows multiple keypresses :D
        return;

    switch (event->key()) {
    case Qt::Key_D:
        p1->addDirection(-1);
        break;
    case Qt::Key_A:
        p1->addDirection(1);
        break;

    case Qt::Key_L:
        if(p2!= nullptr)
            p2->addDirection(-1);
        break;
    case Qt::Key_J:
        if(p2!= nullptr)
            p2->addDirection(1);
        break;

    default:
        break;
    }
}
void MainWindow::mousePressEvent(QMouseEvent *event) {

    if(p2 != nullptr){

        if(event->button() == Qt::MouseButton::LeftButton){
            p2->shoot();
        }

    }
}

void MainWindow::pause() {
    timer->stop();
    if(boss != nullptr && current_room_type == "boss")
        boss->stop();
    else if(current_room_type == "normal")
        for (auto k = enemies.begin(); k != enemies.end(); k++)  //checks for enemies' health
            (*k)->stop();
}
void MainWindow::resume() {
    timer->start(3);
    if(boss != nullptr && current_room_type == "boss")
        boss->init();
    else if(current_room_type == "normal")
        for (auto k = enemies.begin(); k != enemies.end(); k++)  //checks for enemies' health
            (*k)->init();
}

void MainWindow::check_collitions(Player *p) {

    /*------EDGES------*/
    if(p->getX() < p->getRadio()) { //colicion en x por la izquierda
        p->set_velX(p->getRadio(), -1*p->getE()*p->getVx());
    }
    if(p->getX() > h_limit - p->getRadio()) { //colicion en x por la derecha
        p->set_velX(h_limit - p->getRadio(), -1*p->getE()*p->getVx());
    }
    if(p->getY() < p->getRadio()) { //colicion en y por arriba (callendo)
        p->set_velY(p->getRadio(), -1*p->getE()*p->getVy());
        p->setJumping(false);
    }
    if(p->getY() > v_limit - p->getRadio()) { //colicion en y por abajo (saltando)
        p->set_velY(v_limit - p->getRadio(), -1*p->getE()*p->getVy());
    }

    /*------WALLS------*/
    for(int k = 0; k < p->collidingItems().size(); k++){

        if(typeid( *(p->collidingItems()[k]) )== typeid(Wall)){

            if(p->getX() < p->collidingItems().at(k)->x()) { //colicion en x por la izquierda

                //p->set_velX(p->collidingItems().at(k)->x() - p->getRadio(), -1*p->getE()*p->getVx());
                p->set_velX(p->collidingItems().at(k)->x() - p->getRadio() + (p->getDirection() * p->getMovement_speed()), p->getVx()); //fails ******

            }
            if(p->getX() > p->collidingItems().at(k)->x() + p->collidingItems().at(k)->boundingRect().width()) { //colicion en x por la derecha

                //p->set_velX(p->collidingItems().at(k)->x() + p->collidingItems().at(k)->boundingRect().width() + p->getRadio(), -1*p->getE()*p->getVx());
                p->set_velX(p->collidingItems().at(k)->x() + p->collidingItems().at(k)->boundingRect().width() + p->getRadio() + (p->getDirection() * p->getMovement_speed()), p->getVx()); //fails ******
            }
            if(p->getY() > v_limit - p->collidingItems().at(k)->y()) { //colicion en y por arriba (callendo)

                p->set_velY(v_limit - p->collidingItems().at(k)->y() + p->getRadio(), -1*p->getE()*p->getVy());
                p->setJumping(false);

            }
            if(p->getY() < v_limit - (p->collidingItems().at(k)->y() + p->collidingItems().at(k)->boundingRect().height())) { //colicion en y por abajo (saltando)

                p->set_velY(v_limit - (p->collidingItems().at(k)->y() + p->collidingItems().at(k)->boundingRect().height() + p->getRadio()), -1*p->getE()*p->getVy());

            }
        }
    }
}
bool MainWindow::check_collitions(Proyectile *p) {
    /*------EDGES------*/
    if(p->getX() < p->getRadio()) {
        return true;
    }
    if(p->getX() > h_limit - p->getRadio()) {
        return true;
    }
    if(p->getY() < p->getRadio()) {
        return true;
    }
    if(p->getY() > v_limit - p->getRadio()) {
        return true;
    }

    for(int k = 0; k < p->collidingItems().size(); k++){

         /*------WALLS------*/
        if(typeid ( *(p->collidingItems()[k]) ) == typeid(Wall)){

            return true;

        }
         /*------ENEMIES------*/
        else if(typeid ( *(p->collidingItems()[k]) ) == typeid(Enemy)){

            if(p->getType() != "enemy"){
                dynamic_cast<Enemy *>((p->collidingItems()[k]))->take_damage(p->getDamage());
                return true;
            }
        }
        else if(typeid ( *(p->collidingItems()[k]) ) == typeid(Player)){

            if(p->getType() != "player"){
                dynamic_cast<Player *>((p->collidingItems()[k]))->take_damage(p->getDamage());
                return true;
            }
        }
        else if(typeid ( *(p->collidingItems()[k]) ) == typeid(Boss)){

            if(p->getType() != "boss" && p->getType() != "enemy"){
                dynamic_cast<Boss *>((p->collidingItems()[k]))->take_damage(p->getDamage());
                return true;
            }
        }

    }
    return false;
}
void MainWindow::check_collitions(Enemy *e) {

    /*------EDGES------*/
    if(e->getX() < e->getRadio()) { //colicion en x por la izquierda
        e->set_velX(e->getRadio(), -1*e->getE()*e->getVx());
    }
    if(e->getX() > h_limit - e->getRadio()) { //colicion en x por la derecha
        e->set_velX(h_limit - e->getRadio(), -1*e->getE()*e->getVx());
    }
    if(e->getY() < e->getRadio()) { //colicion en y por arriba (callendo)
        e->set_velY(e->getRadio(), -1*e->getE()*e->getVy());
        //(*k)->setJumping(false);
    }
    if(e->getY() > v_limit - e->getRadio()) { //colicion en y por abajo (saltando)
        e->set_velY(v_limit - e->getRadio(), -1*e->getE()*e->getVy());
    }

    for(int k = 0; k < e->collidingItems().size(); k++){

        /*------WALLS------*/
        if(typeid( *(e->collidingItems()[k]) )== typeid(Wall)){

            if(e->getX() < e->collidingItems().at(k)->x()) { //colicion en x por la izquierda

                e->set_velX(e->collidingItems().at(k)->x() - e->getRadio(), -1*e->getE()*e->getVx());
            }
            if(e->getX() > e->collidingItems().at(k)->x() + e->collidingItems().at(k)->boundingRect().width()) { //colicion en x por la derecha

                e->set_velX(e->collidingItems().at(k)->x() + e->collidingItems().at(k)->boundingRect().width() + e->getRadio(), -1*e->getE()*e->getVx());
            }
            if(e->getY() > v_limit - e->collidingItems().at(k)->y()) { //colicion en y por arriba (callendo)

                e->set_velY(v_limit - e->collidingItems().at(k)->y() + e->getRadio(), -1*e->getE()*e->getVy());
            }
            if(e->getY() < v_limit - (e->collidingItems().at(k)->y() + e->collidingItems().at(k)->boundingRect().height())) { //colicion en y por abajo (saltando)

                e->set_velY(v_limit - (e->collidingItems().at(k)->y() + e->collidingItems().at(k)->boundingRect().height() + e->getRadio()), -1*e->getE()*e->getVy());
            }
        }
        else if(typeid ( *(e->collidingItems()[k]) ) == typeid(Player)){

            //dynamic_cast<Player *>((e->collidingItems()[k]))->take_damage(e->getDamage()); //too brutal
        }
    }
}
void MainWindow::check_collitions(Boss *b) {
    /*------EDGES------*/
    if(b->getX() < b->getWidth()/2) { //colicion en x por la izquierda
        b->set_velX(b->getWidth()/2, -1*b->getE()*b->getVx());
    }
    if(b->getX() > h_limit - b->getWidth()/2) { //colicion en x por la derecha
        b->set_velX(h_limit - b->getWidth()/2, -1*b->getE()*b->getVx());
    }
    if(b->getY() < b->getHeight()/2) { //colicion en y por arriba (callendo)
        b->set_velY(b->getHeight()/2, -1*b->getE()*b->getVy());
        //(*k)->setJumping(false);
    }
    if(b->getY() > v_limit - (b->getHeight()/2)) { //colicion en y por abajo (saltando)
        b->set_velY(v_limit - (b->getHeight()/2), -1*b->getE()*b->getVy());
    }

    for(int k = 0; k < b->collidingItems().size(); k++){

        /*------WALLS------*/
        if(typeid( *(b->collidingItems()[k]) )== typeid(Wall)){

            if(b->getX() < b->collidingItems().at(k)->x()) { //colicion en x por la izquierda

               b->set_velX(b->collidingItems().at(k)->x() - b->getWidth()/2, -1*b->getE()*b->getVx());
            }
            if(b->getX() > b->collidingItems().at(k)->x() + b->collidingItems().at(k)->boundingRect().width()) { //colicion en x por la derecha

                b->set_velX(b->collidingItems().at(k)->x() + b->collidingItems().at(k)->boundingRect().width() + b->getWidth()/2, -1*b->getE()*b->getVx());
            }
            if(b->getY() > v_limit - b->collidingItems().at(k)->y()) { //colicion en y por arriba (callendo)

                b->set_velY(v_limit - b->collidingItems().at(k)->y() + b->getHeight()/2, -1*b->getE()*b->getVy());
            }
            if(b->getY() < v_limit - (b->collidingItems().at(k)->y() + b->collidingItems().at(k)->boundingRect().height())) { //colicion en y por abajo (saltando)

                b->set_velY(v_limit - (b->collidingItems().at(k)->y() + b->collidingItems().at(k)->boundingRect().height() + b->getHeight()/2), -1*b->getE()*b->getVy());
            }
        }
        else if(typeid ( *(b->collidingItems()[k]) ) == typeid(Player)){

            //dynamic_cast<Player *>((e->collidingItems()[k]))->take_damage(e->getDamage()); //too brutal
        }
    }
}

Item * MainWindow::get_random_item() {

    Item * i = item_bank.back();
    if(i != nullptr) {
        item_bank.pop_back();
        return i;
    }
    return nullptr;
}
void MainWindow::load_items(std::string file_name) {
    std::fstream file (file_name, std:: fstream::in | std::fstream::binary);

    if(file.is_open()){

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
                item_bank.push_back(new Item(nullptr, name, max_health, health, damage, shot_speed, movement_speed, jump_Speed, g_player, g_proyectiles, r_player, r_proyectiles, e_player, temp));
                counter = 0;
           }
            counter++;
        }

        file.close();

    }
}

void MainWindow::update_bodies(){

    p1->Player::update();
    check_collitions(p1);

    if(p2 != nullptr){
        p2->Player::update();
        check_collitions(p2);
    }

    if(boss != nullptr && current_room_type == "boss"){

        boss->update();
        check_collitions(boss);

        if (boss->getHealth() <= 0){
            //scene->removeItem(boss);
            boss = nullptr;

            current_room->clear_room();

            scene->removeItem(p1);
            if(p2 != nullptr)
                scene->removeItem(p2);

            current_room->spawn_item(get_random_item());

            scene->addItem(p1);
            if(p2 != nullptr)
                scene->addItem(p2);  

        }
    }

    for (auto k = proyectiles.begin(); k != proyectiles.end(); ) { //checks for proyectiles' collitions

        (*k)->Proyectile::update();

        if (check_collitions(*k)){
            scene->removeItem(*k);
            delete (*k);
            k = proyectiles.erase(k);
        }

        else
            k++;
    }

    if(current_room_type == "normal"){
        for (auto k = enemies.begin(); k != enemies.end(); ) { //checks for enemies' health

            (*k)->update();
            check_collitions(*k);

            if ((*k)->getHealth() <= 0){
                scene->removeItem(*k);
                //delete(*k);
                (*k)->stop();
                k = enemies.erase(k);
            }
            else
                k++;
        }

        if(enemies.empty() && !current_room->isClear()) {
            current_room->clear_room();

            int r = rand() % 101;

            if(r <= 66 && r >= 0){

                scene->removeItem(p1);
                if(p2 != nullptr)
                    scene->removeItem(p2);

                if(r <= 22 && r >= 0){

                    current_room->spawn_item(get_random_item());
                }
                else if (r > 22){

                    current_room->spawn_heart();
                }

                scene->addItem(p1);
                if(p2 != nullptr)
                    scene->addItem(p2);

            }
        }
    }

    if(current_room_type == "treasure" && !current_room->isClear()){
        current_room->clear_room();
        current_room->spawn_item(get_random_item());

        scene->removeItem(p1);
        if(p2 != nullptr)
            scene->removeItem(p2);

            scene->addItem(p1);
            if(p2 != nullptr)
                scene->addItem(p2);
    }
}

void MainWindow::setPause_menu(PauseMenu *value) {
    pause_menu = value;
}









