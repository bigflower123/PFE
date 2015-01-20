#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;
using namespace cv;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    connect(ui.actionOuvrirVideo, SIGNAL(triggered()), this, SLOT(chooseVideo()));
}

MainWindow::~MainWindow()
{
    delete fichierManage;
}

void MainWindow::chooseVideo(){
    //Open filedialog to choose video file
    QString fileName = QFileDialog::getOpenFileName(
                this, "Ouvrir vidéo",
                "",
                "Vidéo fichiers (*.avi *.mp4 *.asf);;All files (*.*)");
    fichierManage->openVideo(fileName, ui.graphicsView);
}

/*void MainWindow::openVideo()
{
    //Open filedialog to choose video file
    QString fileName = QFileDialog::getOpenFileName(
                this, "Ouvrir vidéo",
                "",
                "Vidéo fichiers (*.avi *.mp4 *.asf);;All files (*.*)");
    if (!videoCap.open(fileName.toStdString())){
          ui.msgLabel->text() == "Problem loading file!";
          std::abort();
    }else{
         ui.msgLabel->text() == "Ok!";
         //Number frame
         totalFrameNumber = videoCap.get(CV_CAP_PROP_FRAME_COUNT);
         //rate
         rate = videoCap.get(CV_CAP_PROP_FPS); //get the frames per seconds of the video
         videoCap.set(CV_CAP_PROP_POS_MSEC, 300); //start the video at 300ms
         srcImage = Mat::zeros(videoCap.get(CV_CAP_PROP_FRAME_HEIGHT), videoCap.get(CV_CAP_PROP_FRAME_WIDTH), CV_8UC3);
    }
    //cvWaitKey(1000/rate);
    connect(&theTimer, &QTimer::timeout, this, &MainWindow::DisplayVideo);
    theTimer.start(1000/rate);
}

void MainWindow::DisplayVideo(){
    videoCap>>srcImage;
    if(srcImage.data){
        cvtColor(srcImage, srcImage, CV_BGR2RGB);  //Qt support RGB, OpenCv support BGR
    }
    QImage image = QImage((uchar*)(srcImage.data), srcImage.cols, srcImage.rows, QImage::Format_RGB888);
    QImage result = image.scaled(800,600).scaled(495,325, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QGraphicsScene *scene = new QGraphicsScene;
    scene->addPixmap(QPixmap::fromImage(result));
    ui.graphicsView->setScene(scene);
    ui.graphicsView->show();

}*/

