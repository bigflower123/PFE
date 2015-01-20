#include <QtWidgets/QMainWindow>
#include <QFileDialog>
#include <QPaintEvent>
#include <QTimer>
#include <QPainter>
#include <QPixmap>
#include <QImage>
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

private:
    Ui::MainWindow ui;
};
