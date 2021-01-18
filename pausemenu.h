#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include <QMainWindow>

namespace Ui {
class PauseMenu;
}

class PauseMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit PauseMenu(QWidget *parent = nullptr);
    ~PauseMenu();

private:
    Ui::PauseMenu *ui;
};

#endif // PAUSEMENU_H
