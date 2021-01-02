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

    r1 = new Room(this, scene, &proyectiles, "");

    r1->load_room();

    enemies = r1->getEnemies();

    scene->addItem(p1);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update_bodies()));
    timer->start(3);
}
MainWindow::~MainWindow() {

    delete timer;
    delete r1;
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
        //Qproyectiles.push_back(p);

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

void MainWindow::update_bodies(){

    p1->Player::update();
    check_collitions(p1);

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

    for (auto k = enemies.begin(); k != enemies.end(); ) { //checks for enemies' health

        (*k)->update();
        check_collitions(*k);

        if ((*k)->getHealth() <= 0){
            scene->removeItem(*k);
            delete(*k);
            k = enemies.erase(k);
        }
        else
            k++;
    }
}











