#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include "player.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    //Display video frame in player UI
    void updatePlayerUI(QImage img);
    //Slot for the load video push button.
    void chooseVideo();
    // Slot for the play push button.
    void on_playBtn_clicked();

private:
    Ui::MainWindow *ui;
    player *myPlayer;
};

#endif // MAINWINDOW_H
