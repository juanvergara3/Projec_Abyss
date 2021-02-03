#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pausemenu.h"
#include "mainmenu.h"

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

    if(game != nullptr){ // if there's an active game

        if(p1->getAlive()){ // if the player's alive

            if(event->key() == Qt::Key_D){ // move right
                p1->addDirection(1);
                p1->setSight(1);
            }
            if(event->key() == Qt::Key_A){ //  move left
                p1->addDirection(-1);
                p1->setSight(-1);
            }
            if(event->key() == Qt::Key_W){ // jump
                if(!p1->getJumping())
                    p1->set_velY(p1->getY(), p1->getJump_Speed());
                p1->setJumping(true);
            }
            if(event->key() == Qt::Key_S){ // fall faster
                p1->set_velY(p1->getY(), -p1->getJump_Speed());
            }
            if(event->key() == Qt::Key_Space){ // shoot
                p1->shoot();
            }
            if(event->key() == Qt::Key_E){ // interact

                for(int k = 0; k < p1->collidingItems().size(); k++){

                    /*------ITEMS------*/
                    if(typeid( *(p1->collidingItems()[k]) ) == typeid(Item)){

                        Item *i = dynamic_cast<Item*>(p1->collidingItems()[k]);

                        p1->update_stats(i);

                        current_room->remove_item();

                    }
                    /*------DOORS------*/
                    if(typeid( *(p1->collidingItems()[k]) ) == typeid(Door)){

                        Door *d = dynamic_cast<Door*>(p1->collidingItems()[k]);

                        for (auto k = proyectiles.begin(); k != proyectiles.end(); ) { //clears the screen from proyectiles
                            scene->removeItem(*k);
                            delete (*k);
                            k = proyectiles.erase(k);
                        }

                        if(d->getType() == "normal"){ // for normal doors

                            // move the players to the location of the other room's door
                            if(p1->getAlive())
                                p1->set_vel(d->getLink()->getPosx(), v_limit - d->getLink()->getPosy(), 0, 0);
                            if(p2 != nullptr)
                                if(p2->getAlive())
                                    p2->set_vel(d->getLink()->getPosx(), v_limit - d->getLink()->getPosy(), 0, 0);

                            // deload current room and load the next one
                            current_room->deload_room();
                            current_room = d->getLink()->getSelf();
                            current_room->load_room();
                            current_room_type = current_room->getType();

                            spring = current_room->getSpring();

                            // play the music depending on the room type
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

                            // load boss if it's a boss room
                            if(current_room_type == "boss" || current_room_type == "final_boss") {
                                boss = current_room->getBoss();
                                enemies.clear();
                            }
                            // load enemies if it's a normal room
                            else if(current_room_type == "normal") {
                                enemies = current_room->getEnemies();
                                boss = nullptr;
                            }

                            // removes and adds the players back in so that they're in front of everything
                            if(p1->getAlive()){
                                scene->removeItem(p1);
                                scene->addItem(p1);
                            }
                            if(p2 != nullptr){
                                if(p2->getAlive()){
                                    scene->removeItem(p2);
                                    scene->addItem(p2);
                                }
                            }
                        }
                        else if(d->getType() == "boss"){ // for after boss fight doors

                            current_floor->stop_boss_music();
                            current_floor->stop_floor_music();

                            // changes the current floor to the next one and loads the next room
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

                            // makes sure the players are stading still
                            if(p1->getAlive())
                                p1->set_vel(d->getPlayerX(),  d->getPlayerY(), 0, 0);
                            if(p2 != nullptr)
                                if(p2->getAlive())
                                    p2->set_vel(d->getPlayerX(),  d->getPlayerY(), 0, 0);

                            // removes and adds the players back in so that they're in front of everything
                            if(p1->getAlive()){
                                scene->removeItem(p1);
                                scene->addItem(p1);
                            }
                            if(p2 != nullptr){
                                if(p2->getAlive()){
                                    scene->removeItem(p2);
                                    scene->addItem(p2);
                                }
                            }
                        }
                        else if (d->getType() == "final_boss"){ // for the final boss' door (shows the victory screen)
                            victory();
                        }
                    }
                }
            }
        }
        if(p2 != nullptr){
            if(p2->getAlive()){

                if(event->key() == Qt::Key_L){ // move right
                    p2->addDirection(1);
                    p2->setSight(1);
                }
                if(event->key() == Qt::Key_J){ //  move left
                    p2->addDirection(-1);
                    p2->setSight(-1);
                }
                if(event->key() == Qt::Key_I){ // jump
                    if(!p2->getJumping())
                        p2->set_velY(p2->getY(), p2->getJump_Speed());
                    p2->setJumping(true);
                }
                if(event->key() == Qt::Key_K){ // fall faster
                    p2->set_velY(p2->getY(), -p2->getJump_Speed());
                }
                if(event->key() == Qt::Key_O){ // interact

                    for(int k = 0; k < p2->collidingItems().size(); k++){

                        /*------ITEMS------*/
                        if(typeid( *(p2->collidingItems()[k]) ) == typeid(Item)){

                            Item *i = dynamic_cast<Item*>(p2->collidingItems()[k]);

                            p2->update_stats(i);

                            current_room->remove_item();

                        }
                        /*------DOORS------*/
                        if(typeid( *(p2->collidingItems()[k]) ) == typeid(Door)){

                            Door *d = dynamic_cast<Door*>(p2->collidingItems()[k]);

                            for (auto k = proyectiles.begin(); k != proyectiles.end(); ) { //clears the screen from proyectiles
                                scene->removeItem(*k);
                                delete (*k);
                                k = proyectiles.erase(k);
                            }

                            if(d->getType() == "normal"){ // for normal doors

                                // move the players to the location of the other room's door
                                if(p1->getAlive())
                                    p1->set_vel(d->getLink()->getPosx(), v_limit - d->getLink()->getPosy(), 0, 0);
                                if(p2->getAlive())
                                    p2->set_vel(d->getLink()->getPosx(), v_limit - d->getLink()->getPosy(), 0, 0);

                                 // deload current room and load the next one
                                current_room->deload_room();
                                current_room = d->getLink()->getSelf();
                                current_room->load_room();
                                current_room_type = current_room->getType();

                                spring = current_room->getSpring();

                                // play the music depending on the room type
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

                                // load boss if it's a boss room
                                if(current_room_type == "boss" || current_room_type == "final_boss") {
                                    boss = current_room->getBoss();
                                    enemies.clear();
                                }
                                // load enemies if it's a normal room
                                else if(current_room_type == "normal") {
                                    enemies = current_room->getEnemies();
                                    boss = nullptr;
                                }

                                // removes and adds the players back in so that they're in front of everything
                                if(p1->getAlive()){
                                    scene->removeItem(p1);
                                    scene->addItem(p1);
                                }
                                if(p2->getAlive()){
                                    scene->removeItem(p2);
                                    scene->addItem(p2);
                                }

                            }
                            else if(d->getType() == "boss"){ // for after boss fight doors

                                current_floor->stop_boss_music();
                                current_floor->stop_floor_music();

                                // changes the current floor to the next one and loads the next room
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

                                // makes sure the players are stading still
                                if(p1->getAlive())
                                    p1->set_vel(d->getPlayerX(),  d->getPlayerY(), 0, 0);
                                if(p2->getAlive())
                                    p2->set_vel(d->getPlayerX(),  d->getPlayerY(), 0, 0);

                                // removes and adds the players back in so that they're in front of everything
                                if(p1->getAlive()){
                                    scene->removeItem(p1);
                                    scene->addItem(p1);
                                }
                                if(p2->getAlive()){
                                    scene->removeItem(p2);
                                    scene->addItem(p2);
                                }

                            }
                            else if (d->getType() == "final_boss"){ // for the final boss' door (shows the victory screen)
                                victory();
                            }
                        }
                    }
                }
            }
        }

        if(event->key() == Qt::Key_Escape){ // shows the pause menu when the esc key is pressed
            pause();
            this->close();
            pause_menu->showMaximized();
        }
    }
}
void MainWindow::keyReleaseEvent(QKeyEvent *event) {

    //this allows multiple keypresses :D

    if (event->isAutoRepeat())
        return;

    // stops the player movement when the key gets released
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

    // when on singleplayer makes p1 shoot. when on multiplayer makes p2 shoot

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

void MainWindow::pause() { // pauses the game
    timer->stop();
    if(boss != nullptr && (current_room_type == "boss" || current_room_type == "final_boss" ))
        boss->stop();
    else if(current_room_type == "normal")
        for (auto k = enemies.begin(); k != enemies.end(); k++)
            (*k)->stop();
}
void MainWindow::resume() { // resumes the game
    timer->start(3);
    if(boss != nullptr && (current_room_type == "boss" || current_room_type == "final_boss" ))
        boss->init();
    else if(current_room_type == "normal")
        for (auto k = enemies.begin(); k != enemies.end(); k++)
            (*k)->init();
}
void MainWindow::reset_game() { // resets the current game

    current_room->deload_room();

    for (auto k = proyectiles.begin(); k != proyectiles.end(); ) { //clears the screen from proyectiles
        scene->removeItem(*k);
        delete (*k);
        k = proyectiles.erase(k);
    }

    pause();

    current_floor->stop_boss_music();
    current_floor->stop_floor_music();

    enemies.clear();

    p1 = nullptr;
    p2 = nullptr;

    current_floor = nullptr;

    current_room = nullptr;

    boss = nullptr;

    game->reset();

    setGame(game);
}
void MainWindow::close_game() { // "closes" the current game and sets almost all pointers to nullptr for safety reasons

    if(game != nullptr){

        pause();

        current_floor->stop_boss_music();
        current_floor->stop_floor_music();

        current_room->deload_room();

        for (auto k = proyectiles.begin(); k != proyectiles.end(); ) { //clears the screen from proyectiles
            scene->removeItem(*k);
            delete (*k);
            k = proyectiles.erase(k);
        }

        enemies.clear();

        delete game;

        game = nullptr;

        p1 = nullptr;
        p2 = nullptr;

        current_floor = nullptr;
        current_room = nullptr;

        spring = nullptr;

        boss = nullptr;
    }
}
void MainWindow::game_over() { // shows the game over screen
    pause();
    this->close();

    current_floor->stop_boss_music();
    current_floor->stop_floor_music();

    gameover_window->showMaximized();
}
void MainWindow::victory() { //  shows the victory screen
    pause();
    this->close();

    current_floor->stop_boss_music();
    current_floor->stop_floor_music();

    victory_window->showMaximized();
}

void MainWindow::check_collitions(Player *p) { // checks collitions for players

    /*------EDGES------*/
    if(p->getX() < p->getWidth()/2) { // collition on X axis from the left
        p->set_velX(p->getWidth()/2, -1*p->getE()*p->getVx());
    }
    if(p->getX() > h_limit - p->getWidth()/2) { // collition on X axis from the right
        p->set_velX(h_limit - p->getWidth()/2, -1*p->getE()*p->getVx());
    }
    if(p->getY() < p->getHeight()/2) { // collition on Y axis from above (falling)
        p->set_velY(p->getHeight()/2, -1*p->getE()*p->getVy());
        p->setJumping(false);
    }
    if(p->getY() > v_limit - p->getHeight()/2) { // collition on Y axis from bellow (jumping)
        p->set_velY(v_limit - p->getHeight()/2, -1*p->getE()*p->getVy());
    }

    for(int k = 0; k < p->collidingItems().size(); k++){

        /*------WALLS------*/
        if(typeid( *(p->collidingItems()[k]) )== typeid(Wall)){

            if(p->getX() < p->collidingItems().at(k)->x()) { // collition on X axis from the left
                p->set_velX(p->collidingItems().at(k)->x() - p->getWidth()/2 + (p->getDirection() * p->getMovement_speed()), p->getVx()); //fails when the speed is too high
            }
            if(p->getX() > p->collidingItems().at(k)->x() + p->collidingItems().at(k)->boundingRect().width()) { // collition on X axis from the right
                p->set_velX(p->collidingItems().at(k)->x() + p->collidingItems().at(k)->boundingRect().width() + p->getWidth()/2 + (p->getDirection() * p->getMovement_speed()), p->getVx());
            }
            if(p->getY() > v_limit - p->collidingItems().at(k)->y()) { // collition on Y axis from above (falling)
                p->set_velY(v_limit - p->collidingItems().at(k)->y() + p->getHeight()/2, -1*p->getE()*p->getVy());
                p->setJumping(false);
            }
            if(p->getY() < v_limit - (p->collidingItems().at(k)->y() + p->collidingItems().at(k)->boundingRect().height())) { // collition on Y axis from bellow (jumping)
                p->set_velY(v_limit - (p->collidingItems().at(k)->y() + p->collidingItems().at(k)->boundingRect().height() + p->getHeight()/2), -1*p->getE()*p->getVy());
            }
        }

        /*------SPRINGS------*/
        if(typeid( *(p->collidingItems()[k]) ) == typeid(Spring)){

            if(p->getX() < p->collidingItems().at(k)->x()) { // collition on X axis from the left
                p->set_velX(p->collidingItems().at(k)->x() - p->getWidth()/2 + (p->getDirection() * p->getMovement_speed()), p->getVx());
            }
            if(p->getX() > p->collidingItems().at(k)->x() + p->collidingItems().at(k)->boundingRect().width()) { // collition on X axis from the right
                p->set_velX(p->collidingItems().at(k)->x() + p->collidingItems().at(k)->boundingRect().width() + p->getHeight()/2 + (p->getDirection() * p->getMovement_speed()), p->getVx());
            }
            if(p->getY() > v_limit - p->collidingItems().at(k)->y()) { // collition on Y axis from above (falling)

                Spring *s = dynamic_cast<Spring*>(p->collidingItems()[k]);

                s->setSpeed(p->getVy()); //  changes the "speed" on the spring so that it compresses

                p->set_velY(s->getHeight() + p->getHeight(), -1*p->getE()*p->getVy() * 10); // makes the player bounce on the spring
                p->setJumping(true);
            }
            if(p->getY() < v_limit - (p->collidingItems().at(k)->y() + p->collidingItems().at(k)->boundingRect().height())) { // collition on Y axis from bellow (jumping) (not necessary)
                //p->set_velY(v_limit - (p->collidingItems().at(k)->y() + p->collidingItems().at(k)->boundingRect().height() + p->getRadio()), -1*p->getE()*p->getVy());
            }
        }
    }
}
bool MainWindow::check_collitions(Proyectile *p) { // checks collitions for projectiles (returns true if it collides or false if it doesn't)
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
                dynamic_cast<Enemy *>((p->collidingItems()[k]))->take_damage(p->getDamage()); // makes the enemy take damage
                return true;
            }
        }
        /*------PLAYERS------*/
        else if(typeid ( *(p->collidingItems()[k]) ) == typeid(Player)){

            if(p->getType() != "player"){
                dynamic_cast<Player *>((p->collidingItems()[k]))->take_damage(p->getDamage()); // makes the player take damage
                return true;
            }
        }
        /*------BOSSES------*/
        else if(typeid ( *(p->collidingItems()[k]) ) == typeid(Boss)){

            if(p->getType() != "boss" && p->getType() != "enemy"){
                dynamic_cast<Boss *>((p->collidingItems()[k]))->take_damage(p->getDamage()); // makes the boss take damage
                return true;
            }
        }

    }
    return false;
}
void MainWindow::check_collitions(Enemy *e) { // checks collitions for enemies

    /*------EDGES------*/
    if(e->getX() < e->getWidth()/2) { // collition on X axis from the left
        e->set_velX(e->getWidth()/2, -1*e->getE()*e->getVx());
    }
    if(e->getX() > h_limit - e->getWidth()/2) { // collition on X axis from the right
        e->set_velX(h_limit - e->getWidth()/2, -1*e->getE()*e->getVx());
    }
    if(e->getY() < e->getHeight()/2) { // collition on Y axis from above (falling)
        e->set_velY(e->getHeight()/2, -1*e->getE()*e->getVy());
    }
    if(e->getY() > v_limit - e->getHeight()/2) { // collition on Y axis from bellow (jumping)
        e->set_velY(v_limit - e->getHeight()/2, -1*e->getE()*e->getVy());
    }

    for(int k = 0; k < e->collidingItems().size(); k++){

        /*------WALLS------*/
        if(typeid( *(e->collidingItems()[k]) )== typeid(Wall)){
            if(e->getX() < e->collidingItems().at(k)->x()) { // collition on X axis from the left
                e->set_velX(e->collidingItems().at(k)->x() - e->getWidth()/2, -1*e->getE()*e->getVx());
            }
            if(e->getX() > e->collidingItems().at(k)->x() + e->collidingItems().at(k)->boundingRect().width()) { // collition on X axis from the right
                e->set_velX(e->collidingItems().at(k)->x() + e->collidingItems().at(k)->boundingRect().width() + e->getWidth()/2, -1*e->getE()*e->getVx());
            }
            if(e->getY() > v_limit - e->collidingItems().at(k)->y()) { // collition on Y axis from above (falling)
                e->set_velY(v_limit - e->collidingItems().at(k)->y() + e->getHeight()/2, -1*e->getE()*e->getVy());
            }
            if(e->getY() < v_limit - (e->collidingItems().at(k)->y() + e->collidingItems().at(k)->boundingRect().height())) { // collition on Y axis from bellow (jumping)
                e->set_velY(v_limit - (e->collidingItems().at(k)->y() + e->collidingItems().at(k)->boundingRect().height() + e->getHeight()/2), -1*e->getE()*e->getVy());
            }
        }
        else if(typeid ( *(e->collidingItems()[k]) ) == typeid(Player)){ //removed cause it's way too exaggerated

            //dynamic_cast<Player *>((e->collidingItems()[k]))->take_damage(e->getDamage());
        }
    }
}
void MainWindow::check_collitions(Boss *b) { // checks collitions for bosses
    /*------EDGES------*/
    if(b->getX() < b->getWidth()/2) { // collition on X axis from the left
        b->set_velX(b->getWidth()/2, -1*b->getE()*b->getVx());
    }
    if(b->getX() > h_limit - b->getWidth()/2) { // collition on X axis from the right
        b->set_velX(h_limit - b->getWidth()/2, -1*b->getE()*b->getVx());
    }
    if(b->getY() < b->getHeight()/2) { // collition on Y axis from above (falling)
        b->set_velY(b->getHeight()/2, -1*b->getE()*b->getVy());
    }
    if(b->getY() > v_limit - (b->getHeight()/2)) { // collition on Y axis from bellow (jumping)
        b->set_velY(v_limit - (b->getHeight()/2), -1*b->getE()*b->getVy());
    }

    for(int k = 0; k < b->collidingItems().size(); k++){

        /*------WALLS------*/
        if(typeid( *(b->collidingItems()[k]) )== typeid(Wall)){
            if(b->getX() < b->collidingItems().at(k)->x()) { // collition on X axis from the left
               b->set_velX(b->collidingItems().at(k)->x() - b->getWidth()/2, -1*b->getE()*b->getVx());
            }
            if(b->getX() > b->collidingItems().at(k)->x() + b->collidingItems().at(k)->boundingRect().width()) { // collition on X axis from the right
                b->set_velX(b->collidingItems().at(k)->x() + b->collidingItems().at(k)->boundingRect().width() + b->getWidth()/2, -1*b->getE()*b->getVx());
            }
            if(b->getY() > v_limit - b->collidingItems().at(k)->y()) { // collition on Y axis from above (falling)
                b->set_velY(v_limit - b->collidingItems().at(k)->y() + b->getHeight()/2, -1*b->getE()*b->getVy());
            }
            if(b->getY() < v_limit - (b->collidingItems().at(k)->y() + b->collidingItems().at(k)->boundingRect().height())) { // collition on Y axis from bellow (jumping)
                b->set_velY(v_limit - (b->collidingItems().at(k)->y() + b->collidingItems().at(k)->boundingRect().height() + b->getHeight()/2), -1*b->getE()*b->getVy());
            }
        }
        else if(typeid ( *(b->collidingItems()[k]) ) == typeid(Player)){ //removed cause it's way too exaggerated

            //dynamic_cast<Player *>((e->collidingItems()[k]))->take_damage(e->getDamage());
        }
    }
}

void MainWindow::update_bodies(){ // updates everything on screen

    /*------PLAYERS------*/
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

    if(game->getType() == "singleplayer"){ // checks for player's health
        if(p1->getHealth() == 0 && p1->getAlive()){
            p1->die();
            scene->removeItem(p1);
        }
        if(!p1->getAlive())
            game_over();
    }
    else if(game->getType() == "multiplayer"){

        if(p1->getHealth() == 0 && p1->getAlive()){
            p1->die();
            scene->removeItem(p1);
        }
        if(p2->getHealth() == 0 && p2->getAlive()){
            p2->die();
            scene->removeItem(p2);
        }

        if(!p1->getAlive() && !p2->getAlive())
            game_over();
    }

    /*------SPRINGS------*/
    if(spring != nullptr){
        scene->removeItem(spring);
        spring->update();
        scene->addItem(spring);
    }

    /*------BOSSES------*/
    if(boss != nullptr && (current_room_type == "boss" || current_room_type == "final_boss")){

        boss->update();
        check_collitions(boss);

        if (boss->getHealth() <= 0){
            //scene->removeItem(boss);
            boss = nullptr;

            current_room->clear_room();

            if(p1->getAlive())
                scene->removeItem(p1);
            if(p2 != nullptr)
                if(p2->getAlive())
                    scene->removeItem(p2);

            if(current_room_type == "boss")
                current_room->spawn_item(game->get_random_item()); // spawns an item when the boss dies

            if(p1->getAlive())
                scene->addItem(p1);
            if(p2 != nullptr)
                if(p2->getAlive())
                    scene->addItem(p2);
        }
    }

    /*------PROJECTILES------*/
    for (auto k = proyectiles.begin(); k != proyectiles.end(); ) {
        (*k)->Proyectile::update();

        if (check_collitions(*k)){
            scene->removeItem(*k);
            delete (*k);
            k = proyectiles.erase(k);
        }

        else
            k++;
    }

    /*------ENEMIES------*/
    if(current_room_type == "normal"){
        for (auto k = enemies.begin(); k != enemies.end(); ) { //checks for enemies' health

            (*k)->update();
            check_collitions(*k);

            if ((*k)->getHealth() <= 0){
                scene->removeItem(*k);
                (*k)->stop();
                k = enemies.erase(k);
            }
            else
                k++;
        }

        if(enemies.empty() && !current_room->isClear()) {
            current_room->clear_room();

            // spawns an item with a probability of 3/5 and a heart with a probaility of 2/5

            int r = rand() % 101;

            if(p1->getAlive())
                scene->removeItem(p1);
            if(p2 != nullptr)
                if(p2->getAlive())
                    scene->removeItem(p2);

            if(r <= 40 && r >= 0){
                current_room->spawn_heart();
            }
            else if(r > 40){
                current_room->spawn_item(game->get_random_item());
            }

            if(p1->getAlive())
                scene->addItem(p1);
            if(p2 != nullptr)
                if(p2->getAlive())
                    scene->addItem(p2);
        }
    }

    /*------ITEM ROOMS ?------*/
    if(current_room_type == "treasure" && !current_room->isClear()){ //  spawns a item on the treasure rooms
        current_room->clear_room();
        current_room->spawn_item(game->get_random_item());

        // removes and adds the players back in so that they're in front of everything
        if(p1->getAlive()){
            scene->removeItem(p1);
            scene->addItem(p1);
        }
        if(p2 != nullptr){
            if(p2->getAlive()){
                scene->removeItem(p2);
                scene->addItem(p2);
            }
        }
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

void MainWindow::setGame(Game *value) { // sets the game attribute to the game value (initializes the game)

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

    timer->start(3);
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
Room *MainWindow::getCurrent_room() const {
    return current_room;
}
Floor *MainWindow::getCurrent_floor() const {
    return current_floor;
}



