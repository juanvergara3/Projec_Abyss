#include "pausemenu.h"
#include "ui_pausemenu.h"

PauseMenu::PauseMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PauseMenu)
{
    ui->setupUi(this);
}

PauseMenu::~PauseMenu()
{
    delete ui;
}
