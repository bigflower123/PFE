#include "mainwindow.h"
#include "ui_mainwindow.h"
using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    connect(ui.actionOuvrirVideo, SIGNAL(triggered()), this, SLOT(openVideo()));
}

MainWindow::~MainWindow()
{

}

void MainWindow::openVideo()
{
    QString fileName = QFileDialog::getOpenFileName(
                this, "Ouvrir vidéo",
                ".",
                "Vidéo fichiers (*.avi *.mp4 *.asf);;All files (*.*)");
   // connect(&theTimer, &QTimer::timeout, this, &MainWindow::updateImage);
    if (!videoCap.open(fileName.toStdString())){
          ui.msgLabel->text() == "Problem loading file!";
          //ui->txtInfo->appendPlainText("Problem loading file!");
          std::abort();
      } else {
         ui.msgLabel->text() == "Ok!";
         srcImage = Mat::zeros(videoCap.get(CV_CAP_PROP_FRAME_HEIGHT), videoCap.get(CV_CAP_PROP_FRAME_WIDTH), CV_8UC3);
          //ui->txtInfo->appendPlainText("Ok!");
       }
   /* if(videoCap.open(fileName.toStdString()))
    {
        srcImage = Mat::zeros(videoCap.get(CV_CAP_PROP_FRAME_HEIGHT), videoCap.get(CV_CAP_PROP_FRAME_WIDTH), CV_8UC3);
        theTimer.start(33);
    }*/
    cvWaitKey(100);
    connect(&theTimer, &QTimer::timeout, this, &MainWindow::DisplayVideo);
    theTimer.start(33);
}

void MainWindow::DisplayVideo(){
    videoCap>>srcImage;
    if(srcImage.data){
        cvtColor(srcImage, srcImage, CV_BGR2RGB);
    }
    QImage image = QImage((uchar*)(srcImage.data), srcImage.cols, srcImage.rows, QImage::Format_RGB888);
    ui.imageLabel->setPixmap(QPixmap::fromImage(image));
    ui.imageLabel->resize(image.size());
    ui.imageLabel->show();

}
/*void MainWindow::paintEvent(QPaintEvent)
{
    QImage image = QImage((uchar*)(srcImage.data), srcImage.cols, srcImage.rows, QImage::Format_RGB888);
    ui.imageLabel->setPixmap(QPixmap::fromImage(image));
    ui.imageLabel->resize(image.size());
    ui.imageLabel->show();
}

void MainWindow::updateImage()
{
    videoCap>>srcImage;
    if(srcImage.data)
    {
        cvtColor(srcImage, srcImage, CV_BGR2RGB);//Qt中支持的是RGB图像, OpenCV中支持的是BGR
        this->update();	//发送刷新消息
    }
}*/
