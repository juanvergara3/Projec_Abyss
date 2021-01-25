#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pausemenu.h"
#include "mainmenu.h"

Room *MainWindow::getCurrent_room() const
{
    return current_room;
}

Floor *MainWindow::getCurrent_floor() const
{
    return current_floor;
}

MainWindow::MainWindow(QWidget *parent, PauseMenu *p) : QMainWindow(parent), ui(new Ui::MainWindow), pause_menu(p), main_menu(nullptr), h_limit(1280), v_limit(720) {
    ui->setupUi(this);

    gameover_window = nullptr;
    victory_window = nullptr;

    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0 ,1280, 720);
    ui->graphicsView->setScene(scene);
    ui->centralwidget->adjustSize();
    scene->addRect(scene->sceneRect());
    ui->graphicsView->resize(scene->width(), scene->height());
    ui->graphicsView->setFocus();
    this->resize(ui->graphicsView->width()+100, ui->graphicsView->height()+100);

    p1 = nullptr;
    p2 = nullptr;

    current_floor = nullptr;

    current_room = nullptr;

    boss = nullptr;

    game = nullptr;

    spring = nullptr;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update_bodies()));
}
MainWindow::~MainWindow() {

    current_floor = nullptr;
    current_room = nullptr;
    boss = nullptr;

    enemies.clear();
    proyectiles.clear();

    pause_menu = nullptr;
    main_menu = nullptr;

    delete timer;
    delete scene;
    delete game;
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event) {

    if (event->isAutoRepeat())
        return;

    if(p1->getAlive()){

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

                    if(d->getType() == "normal"){

                        p1->set_vel(d->getLink()->getPosx(), v_limit - d->getLink()->getPosy(), 0, 0);
                        if(p2 != nullptr)
                            p2->set_vel(d->getLink()->getPosx(), v_limit - d->getLink()->getPosy(), 0, 0);

                        current_room->deload_room();
                        current_room = d->getLink()->getSelf();
                        current_room->load_room();
                        current_room_type = current_room->getType();

                        spring = current_room->getSpring();

                        if(current_room_type == "boss" || current_room_type == "final_boss"){
                            current_floor->start_boss_music();
                            current_floor->stop_floor_music();
                        }
                        else{
                            if(!current_floor->is_playing("floor"))
                                current_floor->start_floor_music();
                            if(current_floor->is_playing("boss"))
                                current_floor->stop_boss_music();
                        }

                        if(current_room_type == "boss" || current_room_type == "final_boss") {
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
                    }
                    else if(d->getType() == "boss"){

                        current_floor->stop_boss_music();
                        current_floor->stop_floor_music();

                        current_floor->setClear_state(true);
                        current_room->deload_room();
                        current_room = d->getNext()->safe;
                        current_floor = d->getNext();
                        current_room->load_room();
                        current_room_type = current_room->getType();

                        spring = current_room->getSpring();

                        current_floor->start_floor_music();

                        boss = current_room->getBoss();
                        enemies.clear();

                        p1->set_vel(d->getPlayerX(),  d->getPlayerY(), 0, 0);
                        if(p2 != nullptr)
                            p2->set_vel(d->getPlayerX(),  d->getPlayerY(), 0, 0);

                        scene->removeItem(p1);
                        scene->addItem(p1);
                        if(p2 != nullptr){
                            scene->removeItem(p2);
                            scene->addItem(p2);
                        }
                    }
                    else if (d->getType() == "final_boss"){
                        victory();
                    }
                }
                if(typeid( *(p1->collidingItems()[k]) ) == typeid(Item)){

                    Item *i = dynamic_cast<Item*>(p1->collidingItems()[k]);

                    p1->update_stats(i);

                    current_room->remove_item();

                }
            }
        }
    }

    if(p2 != nullptr){

        if(p2->getAlive()){

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

                        if(d->getType() == "normal"){

                            p1->set_vel(d->getLink()->getPosx(), v_limit - d->getLink()->getPosy(), 0, 0);
                            p2->set_vel(d->getLink()->getPosx(), v_limit - d->getLink()->getPosy(), 0, 0);

                            current_room->deload_room();
                            current_room = d->getLink()->getSelf();
                            current_room->load_room();
                            current_room_type = current_room->getType();

                            spring = current_room->getSpring();

                            if(current_room_type == "boss" || current_room_type == "final_boss"){
                                current_floor->start_boss_music();
                                current_floor->stop_floor_music();
                            }
                            else{
                                if(!current_floor->is_playing("floor"))
                                    current_floor->start_floor_music();
                                if(current_floor->is_playing("boss"))
                                    current_floor->stop_boss_music();
                            }

                            if(current_room_type == "boss" || current_room_type == "final_boss") {
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
                        }
                        else if(d->getType() == "boss"){

                            current_floor->stop_boss_music();
                            current_floor->stop_floor_music();

                            current_floor->setClear_state(true);
                            current_room->deload_room();
                            current_room = d->getNext()->safe;
                            current_floor = d->getNext();
                            current_room->load_room();
                            current_room_type = current_room->getType();

                            spring = current_room->getSpring();

                            current_floor->start_floor_music();

                            boss = current_room->getBoss();
                            enemies.clear();

                            p1->set_vel(d->getPlayerX(),  d->getPlayerY(), 0, 0);
                            p2->set_vel(d->getPlayerX(),  d->getPlayerY(), 0, 0);

                            scene->removeItem(p1);
                            scene->addItem(p1);
                            scene->removeItem(p2);
                            scene->addItem(p2);
                        }
                        else if (d->getType() == "final_boss"){
                            victory();
                        }
                    }
                    if(typeid( *(p2->collidingItems()[k]) ) == typeid(Item)){

                        Item *i = dynamic_cast<Item*>(p2->collidingItems()[k]);

                        p2->update_stats(i);

                        current_room->remove_item();

                    }
                }
            }
        }
    }

    if(event->key() == Qt::Key_Escape){
        pause();
        this->close();
        pause_menu->showMaximized();
    }
}
void MainWindow::keyReleaseEvent(QKeyEvent *event) {

    if (event->isAutoRepeat()) //this allows multiple keypresses :D
        return;

    switch (event->key()) {
    case Qt::Key_D:
        if(p1->getAlive())
            p1->addDirection(-1);
        break;
    case Qt::Key_A:
        if(p1->getAlive())
            p1->addDirection(1);
        break;

    case Qt::Key_L:
        if(p2!= nullptr)
            if(p2->getAlive())
                p2->addDirection(-1);
        break;
    case Qt::Key_J:
        if(p2!= nullptr)
            if(p2->getAlive())
                p2->addDirection(1);
        break;

    default:
        break;
    }
}
void MainWindow::mousePressEvent(QMouseEvent *event) {

    if(p2 != nullptr){

        if(p2->getAlive()){

            if(event->button() == Qt::MouseButton::LeftButton){
                p2->shoot();
            }
        }
    }
    else{
        if(p1->getAlive()){

            if(event->button() == Qt::MouseButton::LeftButton){
                p1->shoot();
            }
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
void MainWindow::reset_game() {

    current_room->deload_room();

    for (auto k = proyectiles.begin(); k != proyectiles.end(); ) { //clears the screen from proyectiles
        scene->removeItem(*k);
        delete (*k);
        k = proyectiles.erase(k);
    }

    pause();

    current_floor->stop_boss_music();
    current_floor->stop_floor_music();

    //scene->clear();

    enemies.clear();

    p1 = nullptr;
    p2 = nullptr;

    current_floor = nullptr;

    current_room = nullptr;

    boss = nullptr;

    game->reset();

    setGame(game);
}
void MainWindow::close_game() {

    if(game != nullptr){

        current_floor->stop_boss_music();
        current_floor->stop_floor_music();

        current_room->deload_room();

        for (auto k = proyectiles.begin(); k != proyectiles.end(); ) { //clears the screen from proyectiles
            scene->removeItem(*k);
            delete (*k);
            k = proyectiles.erase(k);
        }

        pause();

        //scene->clear();

        enemies.clear();

        p1 = nullptr;
        p2 = nullptr;

        current_floor = nullptr;
        current_room = nullptr;

        boss = nullptr;

        delete game;

        game = nullptr;
    }
}
void MainWindow::game_over() {
    this->close();
    pause();

    current_floor->stop_boss_music();
    current_floor->stop_floor_music();

    gameover_window->showMaximized();
}
void MainWindow::victory() {
    this->close();
    pause();

    current_floor->stop_boss_music();
    current_floor->stop_floor_music();

    victory_window->showMaximized();
}

void MainWindow::check_collitions(Player *p) {

    /*------EDGES------*/
    if(p->getX() < p->getWidth()/2) { //colicion en x por la izquierda
        p->set_velX(p->getWidth()/2, -1*p->getE()*p->getVx());
    }
    if(p->getX() > h_limit - p->getWidth()/2) { //colicion en x por la derecha
        p->set_velX(h_limit - p->getWidth()/2, -1*p->getE()*p->getVx());
    }
    if(p->getY() < p->getHeight()/2) { //colicion en y por arriba (callendo)
        p->set_velY(p->getHeight()/2, -1*p->getE()*p->getVy());
        p->setJumping(false);
    }
    if(p->getY() > v_limit - p->getHeight()/2) { //colicion en y por abajo (saltando)
        p->set_velY(v_limit - p->getHeight()/2, -1*p->getE()*p->getVy());
    }

    /*------WALLS------*/
    for(int k = 0; k < p->collidingItems().size(); k++){

        if(typeid( *(p->collidingItems()[k]) )== typeid(Wall)){

            if(p->getX() < p->collidingItems().at(k)->x()) { //colicion en x por la izquierda

                //p->set_velX(p->collidingItems().at(k)->x() - p->getRadio(), -1*p->getE()*p->getVx());
                p->set_velX(p->collidingItems().at(k)->x() - p->getWidth()/2 + (p->getDirection() * p->getMovement_speed()), p->getVx()); //fails ******

            }
            if(p->getX() > p->collidingItems().at(k)->x() + p->collidingItems().at(k)->boundingRect().width()) { //colicion en x por la derecha

                //p->set_velX(p->collidingItems().at(k)->x() + p->collidingItems().at(k)->boundingRect().width() + p->getRadio(), -1*p->getE()*p->getVx());
                p->set_velX(p->collidingItems().at(k)->x() + p->collidingItems().at(k)->boundingRect().width() + p->getWidth()/2 + (p->getDirection() * p->getMovement_speed()), p->getVx()); //fails ******
            }
            if(p->getY() > v_limit - p->collidingItems().at(k)->y()) { //colicion en y por arriba (callendo)

                p->set_velY(v_limit - p->collidingItems().at(k)->y() + p->getHeight()/2, -1*p->getE()*p->getVy());
                p->setJumping(false);

            }
            if(p->getY() < v_limit - (p->collidingItems().at(k)->y() + p->collidingItems().at(k)->boundingRect().height())) { //colicion en y por abajo (saltando)

                p->set_velY(v_limit - (p->collidingItems().at(k)->y() + p->collidingItems().at(k)->boundingRect().height() + p->getHeight()/2), -1*p->getE()*p->getVy());

            }
        }

        /*------SPRINGS------*/
        if(typeid( *(p->collidingItems()[k]) ) == typeid(Spring)){

            if(p->getX() < p->collidingItems().at(k)->x()) { //colicion en x por la izquierda

                //p->set_velX(p->collidingItems().at(k)->x() - p->getRadio(), -1*p->getE()*p->getVx());
                p->set_velX(p->collidingItems().at(k)->x() - p->getWidth()/2 + (p->getDirection() * p->getMovement_speed()), p->getVx()); //fails ******

            }
            if(p->getX() > p->collidingItems().at(k)->x() + p->collidingItems().at(k)->boundingRect().width()) { //colicion en x por la derecha

                //p->set_velX(p->collidingItems().at(k)->x() + p->collidingItems().at(k)->boundingRect().width() + p->getRadio(), -1*p->getE()*p->getVx());
                p->set_velX(p->collidingItems().at(k)->x() + p->collidingItems().at(k)->boundingRect().width() + p->getHeight()/2 + (p->getDirection() * p->getMovement_speed()), p->getVx()); //fails ******
            }
            if(p->getY() > v_limit - p->collidingItems().at(k)->y()) { //colicion en y por arriba (callendo)

                Spring *s = dynamic_cast<Spring*>(p->collidingItems()[k]);

                s->setSpeed(p->getVy());

                p->set_velY(s->getHeight() + p->getHeight(), -1*p->getE()*p->getVy() * 10);
                p->setJumping(true);

            }
            if(p->getY() < v_limit - (p->collidingItems().at(k)->y() + p->collidingItems().at(k)->boundingRect().height())) { //colicion en y por abajo (saltando)

                //p->set_velY(v_limit - (p->collidingItems().at(k)->y() + p->collidingItems().at(k)->boundingRect().height() + p->getRadio()), -1*p->getE()*p->getVy());

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

void MainWindow::update_bodies(){

    if(p1->getAlive()){
        p1->Player::update();
        check_collitions(p1);
    }

    if(p2 != nullptr){
        if(p2->getAlive()){
            p2->Player::update();
            check_collitions(p2);
        }
    }

    if(spring != nullptr){
        scene->removeItem(spring);
        spring->update();
        scene->addItem(spring);
    }

    //    if(p1->getHealth() == 0 && p1->getAlive()){
    //        p1->die();
    //        scene->removeItem(p1);
    //    }
    //    if(p2 != nullptr){
    //        if(p2->getHealth() == 0 && p2->getAlive())
    //            scene->removeItem(p2);
    //    }

    //    if(game->getType() == "singleplayer"){
    //        if(p1->getHealth() == 0)
    //            p1->die();
    //        if(!p1->getAlive())
    //            game_over();
    //    }
    //    else if(game->getType() == "multiplayer"){

    //        if(p1->getHealth() == 0)
    //            p1->die();
    //        if(p2->getHealth() == 0)
    //            p2->die();

    //        if(!p1->getAlive() && !p2->getAlive())
    //            game_over();
    //    }

    if(boss != nullptr && (current_room_type == "boss" || current_room_type == "final_boss")){

        boss->update();
        check_collitions(boss);

        if (boss->getHealth() <= 0){
            //scene->removeItem(boss);
            boss = nullptr;

            current_room->clear_room();

            if(current_room_type == "boss"){

                scene->removeItem(p1);
                if(p2 != nullptr)
                    scene->removeItem(p2);

                current_room->spawn_item(game->get_random_item());

                scene->addItem(p1);
                if(p2 != nullptr)
                    scene->addItem(p2);
            }
            else if(current_room_type == "final_boss"){

                scene->removeItem(p1);
                if(p2 != nullptr)
                    scene->removeItem(p2);

                scene->addItem(p1);
                if(p2 != nullptr)
                    scene->addItem(p2);
            }
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

            scene->removeItem(p1);
            if(p2 != nullptr)
                scene->removeItem(p2);

            if(r <= 66 && r >= 0){
                current_room->spawn_heart();
            }
            else if(r > 66){
                current_room->spawn_item(game->get_random_item());
            }

            scene->addItem(p1);
            if(p2 != nullptr)
                scene->addItem(p2);

        }
    }

    if(current_room_type == "treasure" && !current_room->isClear()){
        current_room->clear_room();
        current_room->spawn_item(game->get_random_item());

        scene->removeItem(p1);
        if(p2 != nullptr){
            scene->removeItem(p2);
        }

        scene->addItem(p1);
        if(p2 != nullptr)
            scene->addItem(p2);
    }
}

void MainWindow::setPause_menu(PauseMenu *value) {
    pause_menu = value;
}
void MainWindow::setMain_menu(MainMenu *value) {
    main_menu = value;
}
void MainWindow::setGameover_window(MessageWindow *value) {
    gameover_window = value;
}
void MainWindow::setVictory_window(MessageWindow *value) {
    victory_window = value;
}

void MainWindow::setGame(Game *value) {

    game = value;

    p1 = game->getP1();
    p2 = game->getP2();

    current_floor = game->getCurrent_floor();
    current_room = game->getCurrent_room();

    current_room->load_room();
    current_room_type = current_room->getType();

    if(current_room_type == "normal" || current_room_type == "safe" || current_room_type == "treasure"){
            current_floor->start_floor_music();
            if(current_room_type == "normal")
                enemies = current_room->getEnemies();
    }
    else if(current_room_type == "boss" || current_room_type == "final_boss"){
        boss = current_room->getBoss();
        boss->init();
        current_floor->start_boss_music();
    }

    spring = current_room->getSpring();

    if(p1->getHealth() > 0)
        scene->addItem(p1);
    if(p2 != nullptr)
        if(p2->getHealth() > 0)
            scene->addItem(p2);

    timer->start(3); // not sure about this one right here
}
Game *MainWindow::getGame() const {
    return game;
}

std::list<Proyectile *> *MainWindow::getProyectiles() {
    return &proyectiles;
}
QGraphicsScene *MainWindow::getScene() const {
    return scene;
}




