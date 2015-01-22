#include <QtWidgets/QMainWindow>
#include <QFileDialog>
#include <opencv2\opencv.hpp>
#include "ui_mainwindow.h"
#include "fichiercontrol.h"

using namespace cv;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    fichierControl *fichierManage = new fichierControl();

public slots:
    void chooseVideo();
    void pauseVideo();

private:
    Ui::MainWindow ui;
};
