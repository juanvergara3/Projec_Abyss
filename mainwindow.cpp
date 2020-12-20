#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    scene = new QGraphicsScene(this);

    ui->graphicsView->setScene(scene);
    scene->addRect(scene->sceneRect());

    p1 = new Player;
    r1 = new Room;

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
    }
    if(event->key() == Qt::Key_A){
        p1->set_vel(p1->getX(), p1->getY(), -10, p1->getVy());
    }
    if(event->key() == Qt::Key_W || event->key() == Qt::Key_Space){
        p1->set_vel(p1->getX(), p1->getY(), p1->getVx(), 50);
    }
    if(event->key() == Qt::Key_S){
        p1->set_vel(p1->getX(), p1->getY(), p1->getVx(), -50);
    }
}

void MainWindow::update_bodies(){

    p1->update(1080);
}
