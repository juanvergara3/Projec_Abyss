#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include <QMainWindow>

namespace Ui { class PauseMenu; }

class PauseMenu : public QMainWindow
{
    Q_OBJECT
public: // variables

private: // variables
    QList<QWidget*> mainScreen;
    QList<QWidget*> resetScreen;
    QList<QWidget*> menuScreen;

    Ui::PauseMenu *ui;

public: // methods
    explicit PauseMenu(QWidget *parent = nullptr);
    ~PauseMenu();

private: // methods
    void init_lists();

    void hide_mainScreen();
    void hide_resetScreen();
    void hide_menuScreen();

    void show_mainScreen();
    void show_resetScreen();
    void show_menuScreen();

private slots:

    void on_resumeButton_clicked();
    void on_saveButton_clicked();
    void on_restartButton_clicked();
    void on_exitButton_clicked();
    void on_noButton_res_clicked();
    void on_yesButton_res_clicked();
    void on_noButton_men_clicked();
    void on_yesButton_men_clicked();
};

#endif // PAUSEMENU_H
