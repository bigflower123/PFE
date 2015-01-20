#include <QtWidgets/QMainWindow>
#include <QFileDialog>
#include <QPaintEvent>
#include <QTimer>
#include <QPainter>
#include <QPixmap>
#include <QLabel>
#include <QImage>
#include <opencv2\opencv.hpp>
#include "ui_mainwindow.h"
using namespace cv;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void openVideo();
    void DisplayVideo();

private:
    QTimer theTimer;
    Mat srcImage;
    VideoCapture videoCap;
    long totalFrameNumber;
    double rate;

    Ui::MainWindow ui;
};
