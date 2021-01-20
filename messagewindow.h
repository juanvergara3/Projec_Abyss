#ifndef MESSAGEWINDOW_H
#define MESSAGEWINDOW_H

#include <QMainWindow>
#include "QKeyEvent"

namespace Ui { class MessageWindow; }

class MainMenu;
class MainWindow;

class MessageWindow : public QMainWindow {
    Q_OBJECT
private: // variables
    Ui::MessageWindow *ui;

    MainMenu *main_menu;
    MainWindow *main_window;

public: // variables

private: // methods

public: // methods
    explicit MessageWindow(QWidget *parent = nullptr, std::string type = "gameover");
    ~MessageWindow();

    void keyPressEvent(QKeyEvent *event);

    void setMain_menu(MainMenu *value);
    void setMain_window(MainWindow *value);

private slots:
    void on_continueButton_clicked();

};

#endif // MESSAGEWINDOW_H
