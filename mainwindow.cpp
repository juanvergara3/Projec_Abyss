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

    if(event->key() == Qt::Key_D){
        p1->set_vel(p1->getX(), p1->getY(),10, p1->getVy());
        p1->setDir("Right");
    }
    if(event->key() == Qt::Key_A){
        p1->set_vel(p1->getX(), p1->getY(), -10, p1->getVy());
        p1->setDir("Left");
    }
    if(event->key() == Qt::Key_W || event->key() == Qt::Key_Space){
        p1->set_vel(p1->getX(), p1->getY(), p1->getVx(), 50);
        p1->setDir("Up");
    }
    if(event->key() == Qt::Key_S){
        p1->set_vel(p1->getX(), p1->getY(), p1->getVx(), -50);
        p1->setDir("Down");
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

        if(p->getX() < p->collidingItems().at(k)->x()) {

            p->set_vel(p->getX(), p->getY(), -1*p->getVx(), p->getVy());


        }
        if(p->getX() > p->collidingItems().at(k)->x() + p->collidingItems().at(k)->boundingRect().width()) {

            p->set_vel(p->getX(), p->getY(), -1*p->getE()*p->getVx(), p->getVy());

        }
        if(p->getY() < p->getRadio()) {
            p->set_vel(p->getX(), p->getRadio(), p->getVx(), -1*p->getE()*p->getVy());


        }
        if(p->getY() > v_limit - p->getRadio()) {
            p->set_vel(p->getX(), v_limit - p->getRadio(), p->getVx(), -1*p->getE()*p->getVy());


        }

    }


}

void MainWindow::update_bodies(){

    p1->update(720);
    check_collitions(p1);

    if(p1->getVy() < 0)
        p1->setDir("Down");
}











