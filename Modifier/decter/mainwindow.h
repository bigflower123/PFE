#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QTime>
#include <QMouseEvent>
#include "player.h"
#include "video_qlabel.h"
#include "informationdialog.h"
#include "deplacementmaxdialog.h"

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
    void updatePlayerUI(QImage img, QString tmpInfo);
    //Slot for the load video
    void chooseVideo();
    //Slot for choose save path
    void choosePath();
    void chooseInfoPath();
    //Slot for the play push button.
    void on_playBtn_clicked();
    //QString getFormattedTime(int timeInSeconds);

    //Slot for Slider
    void on_videoSlider_sliderPressed();
    void on_videoSlider_sliderReleased();
    void on_videoSlider_sliderMoved(int position);

    //Slot for the backward and forward push button
    void on_backwardButton_clicked();
    void on_forwardButton_clicked();
    void on_quickforwardButton_clicked();
    void on_quickbackwardButton_clicked();

    //Slot for choose object
     void myMouseMove(int, int);
     void myMousePressed(int, int);
     void myMouseLeft(int, int);
     void myMouseMovePressed(int, int);

     //Slot for open dialog
     void openInformationDialog();
     void openDeplacementDialog();

     void on_debutButton_clicked();
     void on_finButton_clicked();
     void on_trajectoirecheckBox_clicked();


     void on_savefinButton_clicked();

     void on_visualiserButton_clicked();

     void on_traiterButton_clicked();

     void on_ouvrirButton_clicked();

     //void on_zoomoutButton_clicked();

private:
    Ui::MainWindow *ui;
    player *myPlayer;
    //show video
    void displayImage(QImage &, double, QString tmpInfo);

    //Choose object
    Mat org, tmp, img, dst;
    Point pre_pt = (-1,-1);
    Point cur_pt = (-1,-1);
    int taille = 0;
    double valueScale = 1.0;
    char temp[16];
    double imgheight,imgwidth,labelheight,labelwidth ;
    double  heightscale, widthscale;
    bool flagmovepresse = false;

    //Dialog pointeur
    InformationDialog *infoDialog;
    DeplacementMaxDialog *deplacementDialog;

    //Postion of slider
    int postionSlider;
    int itemNumber = 0;

    //début et fin
    int start;
    int fin;

    int i = 0;
    //Prémier frame de vidéo avec trajectoire
    int base = 0;
    bool flagVisualier = false;
    bool flagTraiter = true;
    QString videoName;
};

#endif // MAINWINDOW_H
