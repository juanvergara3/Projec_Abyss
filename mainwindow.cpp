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

    p1 = new Player;
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

    if (event->isAutoRepeat()) //this allows multiple keypresses :D
        return; // also removes double jump

    if(event->key() == Qt::Key_D){
        p1->set_velX(p1->getX(), p1->getMovement_speed());
    }
    if(event->key() == Qt::Key_A){
        p1->set_velX(p1->getX(), -p1->getMovement_speed());
    }
    if(event->key() == Qt::Key_W || event->key() == Qt::Key_Space){
        p1->set_velY(p1->getY(), p1->getJump_Speed());
    }
    if(event->key() == Qt::Key_S){
        p1->set_velY(p1->getY(), -p1->getJump_Speed());
    }
}

void MainWindow::check_collitions(Player *p) {
    if(p->getX() < p->getRadio()) {
        p->set_vel(p->getRadio(), p->getY(), -1*p->getE()*p->getVx(), p->getVy());
    }
    if(p->getX() > h_limit - p->getRadio()) {
        p->set_vel(h_limit - p->getRadio(), p->getY(), -1*p->getE()*p->getVx(), p->getVy());
    }
    if(p->getY() < p->getRadio()) {
        p->set_vel(p->getX(), p->getRadio(), p->getVx(), -1*p->getE()*p->getVy());
    }
    if(p->getY() > v_limit - p->getRadio()) {
        p->set_vel(p->getX(), v_limit - p->getRadio(), p->getVx(), -1*p->getE()*p->getVy());
    }

    for(int k = 0; k < p->collidingItems().size(); k++){

        if(p->getX() < p->collidingItems().at(k)->x()) { //colicion en x por la izquierda

            p->set_velX(p->collidingItems().at(k)->x() - p->getRadio(), -1*p->getE()*p->getVx());

        }
        if(p->getX() > p->collidingItems().at(k)->x() + p->collidingItems().at(k)->boundingRect().width()) { //colicion en x por la derecha

            p->set_velX(p->collidingItems().at(k)->x() + p->collidingItems().at(k)->boundingRect().width() + p->getRadio(), -1*p->getE()*p->getVx());

        }
        if(p->getY() > v_limit - p->collidingItems().at(k)->y()) { //colicion en y por arriba (callendo)

            p->set_velY(v_limit - p->collidingItems().at(k)->y() + p->getRadio(), -1*p->getE()*p->getVy());

        }
        if(p->getY() < v_limit - (p->collidingItems().at(k)->y() + p->collidingItems().at(k)->boundingRect().height())) { //colicion en y por abajo (saltando)

            // it's better if you don't collide when jumping, gonna leave it working just in case

            p->set_velY(v_limit - (p->collidingItems().at(k)->y() + p->collidingItems().at(k)->boundingRect().height() + p->getRadio()), -1*p->getE()*p->getVy());

        }
    }
}

void MainWindow::update_bodies(){

    p1->update(720);
    check_collitions(p1);

}











