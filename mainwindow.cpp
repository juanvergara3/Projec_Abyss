#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), h_limit(1280), v_limit(720) {
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0 ,1280, 720);
    ui->graphicsView->setScene(scene);
    ui->centralwidget->adjustSize();
    scene->addRect(scene->sceneRect());
    ui->graphicsView->resize(scene->width(), scene->height());
    this->resize(ui->graphicsView->width()+100, ui->graphicsView->height()+100);

    p1 = new Player(this, scene, 0, 0, 0, 0, 20, 8, 4, 1e-5, 0.1, 0);

    r1 = new Room(this, scene, &proyectiles, "1");
    r2 = new Room(this, scene, &proyectiles, "2");

    r1->doors.back()->setLink(r2);
    r2->doors.back()->setLink(r1);

    current_room = r2;
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

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update_bodies()));
    timer->start(3);

    //srand(unsigned(time(0)));
    srand(time(NULL));

    load_items(""); // ***NOTHING IS BEING LOADED YET***

    std::vector<Item*> temp (item_bank.begin(), item_bank.end());
    std::random_shuffle(temp.begin(), temp.end());
    std::copy(temp.begin(), temp.end(), item_bank.begin());
}
MainWindow::~MainWindow() {

    current_room = nullptr;
    boss = nullptr;

    delete current_room;
    delete timer;
    delete r1;
    delete r2;
    delete p1;
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
        Proyectile * p = p1->shoot();
        proyectiles.push_back(p);
    }
    if(event->key() == Qt::Key_E){

        for(int k = 0; k < p1->collidingItems().size(); k++){

            if(typeid( *(p1->collidingItems()[k]) ) == typeid(Door)){

                Door *d = dynamic_cast<Door*>(p1->collidingItems()[k]);

                current_room->deload_room();
                current_room = d->getLink();
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

                scene->removeItem(d);
            }
            if(typeid( *(p1->collidingItems()[k]) ) == typeid(Item)){

                Item *i = dynamic_cast<Item*>(p1->collidingItems()[k]);

                p1->update_stat(i->getStat(), i->getValue());

                current_room->remove_item();

            }
        }
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
    default:
        break;
    }
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

                //p->set_velX(p->collidingItems().at(k)->x() - p->getRadio(), -1*p->getE()*p->getVx());
                //e->set_velX(e->collidingItems().at(k)->x() - e->getRadio() + (e->getDirection() * e->getMovement_speed()), e->getVx()); //fails ******

            }
            if(e->getX() > e->collidingItems().at(k)->x() + e->collidingItems().at(k)->boundingRect().width()) { //colicion en x por la derecha

                //p->set_velX(p->collidingItems().at(k)->x() + p->collidingItems().at(k)->boundingRect().width() + p->getRadio(), -1*p->getE()*p->getVx());
                //e->set_velX(e->collidingItems().at(k)->x() + e->collidingItems().at(k)->boundingRect().width() + e->getRadio() + (e->getDirection() * e->getMovement_speed()), e->getVx()); //fails ******
            }
            if(e->getY() > v_limit - e->collidingItems().at(k)->y()) { //colicion en y por arriba (callendo)

                e->set_velY(v_limit - e->collidingItems().at(k)->y() + e->getRadio(), -1*e->getE()*e->getVy());
                //e->setJumping(false);

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
    if(b->getX() < b->getRadio()) { //colicion en x por la izquierda
        b->set_velX(b->getRadio(), -1*b->getE()*b->getVx());
    }
    if(b->getX() > h_limit - b->getRadio()) { //colicion en x por la derecha
        b->set_velX(h_limit - b->getRadio(), -1*b->getE()*b->getVx());
    }
    if(b->getY() < b->getRadio()) { //colicion en y por arriba (callendo)
        b->set_velY(b->getRadio(), -1*b->getE()*b->getVy());
        //(*k)->setJumping(false);
    }

    if(b->getY() > v_limit - b->getRadio()) { //colicion en y por abajo (saltando)
        b->set_velY(v_limit - b->getRadio(), -1*b->getE()*b->getVy());
    }

    for(int k = 0; k < b->collidingItems().size(); k++){

        /*------WALLS------*/
        if(typeid( *(b->collidingItems()[k]) )== typeid(Wall)){

            if(b->getX() < b->collidingItems().at(k)->x()) { //colicion en x por la izquierda

                //p->set_velX(p->collidingItems().at(k)->x() - p->getRadio(), -1*p->getE()*p->getVx());
                //e->set_velX(e->collidingItems().at(k)->x() - e->getRadio() + (e->getDirection() * e->getMovement_speed()), e->getVx()); //fails ******

            }
            if(b->getX() > b->collidingItems().at(k)->x() + b->collidingItems().at(k)->boundingRect().width()) { //colicion en x por la derecha

                //p->set_velX(p->collidingItems().at(k)->x() + p->collidingItems().at(k)->boundingRect().width() + p->getRadio(), -1*p->getE()*p->getVx());
                //e->set_velX(e->collidingItems().at(k)->x() + e->collidingItems().at(k)->boundingRect().width() + e->getRadio() + (e->getDirection() * e->getMovement_speed()), e->getVx()); //fails ******
            }
            if(b->getY() > v_limit - b->collidingItems().at(k)->y()) { //colicion en y por arriba (callendo)

                b->set_velY(v_limit - b->collidingItems().at(k)->y() + b->getRadio(), -1*b->getE()*b->getVy());
                //e->setJumping(false);

            }
            if(b->getY() < v_limit - (b->collidingItems().at(k)->y() + b->collidingItems().at(k)->boundingRect().height())) { //colicion en y por abajo (saltando)

                b->set_velY(v_limit - (b->collidingItems().at(k)->y() + b->collidingItems().at(k)->boundingRect().height() + b->getRadio()), -1*b->getE()*b->getVy());

            }
        }
        else if(typeid ( *(b->collidingItems()[k]) ) == typeid(Player)){

            //dynamic_cast<Player *>((e->collidingItems()[k]))->take_damage(e->getDamage()); //too brutal
        }
    }
}

Item * MainWindow::get_random_item() {

    Item * i = item_bank.back();
    item_bank.pop_back();
    return i;
}
void MainWindow::load_items(std::string file_name) {
    //loads items from the item bank file
}

void MainWindow::update_bodies(){

    p1->Player::update();
    check_collitions(p1);

    if(boss != nullptr && current_room_type == "boss"){

        boss->update();
        check_collitions(boss);

        if (boss->getHealth() <= 0){
            //scene->removeItem(boss);
            boss = nullptr;

            current_room->clear_room();

            scene->removeItem(p1);
            //current_room->spawn_item(get_random_item());
            current_room->spawn_heart();
            scene->addItem(p1);

        }
    }

    for (auto k = proyectiles.begin(); k != proyectiles.end(); ) { //checks for proyectiles' collitions

        (*k)->update();

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
            current_room->spawn_heart();

            int r = rand() % 101;

            if(r <= 66 && r >= 0){

                scene->removeItem(p1);

                if(r <= 22 && r >= 0){

                    //current_room->spawn_item(get_random_item());
                }
                else if (r > 22){

                    //current_room->spawn_heart();
                }

                scene->addItem(p1);
            }
        }
    }
}











