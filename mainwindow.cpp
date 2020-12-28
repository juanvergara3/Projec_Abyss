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

    r1 = new Room;

    r1->load_walls(scene);

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
        Proyectile * p = p1->shoot(scene);
        //proyectiles.push_back(p);
        Qproyectiles.push_back(p);

    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {

    if (event->isAutoRepeat()) //this allows multiple keypresses :D
        return; // also removes double jump; No it doesn't :/

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

    /*------WALLS------*/
    for(int k = 0; k < p->collidingItems().size(); k++){

        if(typeid ( *(p->collidingItems()[k]) ) == typeid(Wall)){

            return true;

        }
    }
    return false;
}

void MainWindow::update_bodies(){

    p1->Player::update(v_limit);
    check_collitions(p1);

    QList<Proyectile*> aux; //just testing stuff, not very efficient ://
    for(int k = 0; k < Qproyectiles.size(); k++){
        Qproyectiles.at(k)->update(v_limit);
        if(!check_collitions(Qproyectiles.at(k)))
            aux.push_back(Qproyectiles.at(k));
        else
            scene->removeItem(Qproyectiles.at(k));
    }
    Qproyectiles = aux;

    //    for (auto k = proyectiles.begin(); k != proyectiles.end(); ) { //checks for proyectiles collitions

    //        (*k)->update(v_limit);

    //        if (check_collitions(*k)){
    //            scene->removeItem(*k);
    //            k = proyectiles.erase(k);

    //            //delete (*k);
    //        }

    //        else
    //            ++k;
    //    }


}











