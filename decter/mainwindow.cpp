#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    myPlayer = new player();
    QObject::connect(ui->actionOuvrirVideo, SIGNAL(triggered()), this, SLOT(chooseVideo()));
    QObject::connect(myPlayer, SIGNAL(processedImage(QImage)), this, SLOT(updatePlayerUI(QImage)));
    //QObject::connect(ui->VideoLbl, SIGNAL(Mouse_Pos()), this, SLOT(Mouse_current_pos()));
    /***Set Button et Slider disabled****/
    ui->playBtn->setEnabled(false);
    ui->backwardButton->setEnabled(false);
    ui->forwardButton->setEnabled(false);
    ui->videoSlider->setEnabled(false);
    /***********************************/
}

MainWindow::~MainWindow()
{
    delete myPlayer;
    delete ui;
}

/**
 * @brief MainWindow::displayImage
 * @param img: the image to display dans la window
 * @param framecourant
 */
void MainWindow::displayImage(QImage img, double framecourant)
{
    ui->VideoLbl->setAlignment(Qt::AlignCenter);
    ui->VideoLbl->setPixmap(QPixmap::fromImage(img).scaled(ui->VideoLbl->size(),
                                                           Qt::KeepAspectRatio, Qt::FastTransformation));
    ui->videoSlider->setValue(framecourant);
    ui->currentLable->setText(QString::number(framecourant));
}

/**
 * @brief MainWindow::updatePlayerUI: update the image dans la window
 * @param img
 */
void MainWindow::updatePlayerUI(QImage img)
{
    if (!img.isNull())
    {
        displayImage(img, myPlayer->getCurrentFrame());
    }
}

/**
 * Choose a video
 * @brief MainWindow::chooseVideo
 */
void MainWindow::chooseVideo()
{
    //Open filedialog to choose video file
    QString filename = QFileDialog::getOpenFileName(
                this, "Ouvrir vidéo",
                "",
                "Vidéo fichiers (*.avi *.mp4 *.asf);;All files (*.*)");
    QFileInfo name = filename;

    if (!filename.isEmpty()){
        if (!myPlayer->loadVideo(filename.toStdString()))
        {
            QMessageBox msgBox;
            msgBox.setText("The selected video could not be opened!");
            msgBox.exec();
        }
        else
        {
            this->setWindowTitle(name.fileName());
            ui->playBtn->setEnabled(true);
            ui->videoSlider->setEnabled(true);
            ui->backwardButton->setEnabled(true);
            ui->forwardButton->setEnabled(true);
            ui->videoSlider->setMaximum(myPlayer->getNumberOfFrames());
            //ui->totalLable->setText( getFormattedTime( (int)myPlayer->getNumberOfFrames()/(int)myPlayer->getFrameRate()) );
            ui->totalLable->setText(QString::number(myPlayer->getNumberOfFrames()));
        }
    }
}

/**
 * stop and start the video
 * @brief MainWindow::on_playBtn_clicked
 */
void MainWindow::on_playBtn_clicked()
{
    if (myPlayer->isStopped())
    {
        myPlayer->Play();
        ui->playBtn->setText(tr("Stop"));
    }else
    {
        myPlayer->Stop();
        ui->playBtn->setText(tr("Play"));
    }
}

//************************************************
//------------Slider-----------------------------
void MainWindow::on_videoSlider_sliderPressed()
{
    myPlayer->Stop();
}

void MainWindow::on_videoSlider_sliderReleased()
{
    myPlayer->Play();
}

void MainWindow::on_videoSlider_sliderMoved(int position)
{
    myPlayer->setCurrentFrame(position);
    //ui->currentLable->setText( getFormattedTime( position/(int)myPlayer->getFrameRate()) );
    ui->currentLable->setText(QString::number(myPlayer->getFrameRate()));
}
//************************************************
/*QString MainWindow::getFormattedTime(int timeInSeconds){

    int seconds = (int) (timeInSeconds) % 60 ;
    int minutes = (int) ((timeInSeconds / 60) % 60);
    int hours   = (int) ((timeInSeconds / (60*60)) % 24);

    QTime t(hours, minutes, seconds);
    if (hours == 0 )
        return t.toString("mm:ss");
    else
        return t.toString("h:mm:ss");
}*/


void MainWindow::on_backwardButton_clicked()
{
    QImage img;
    myPlayer->Stop();
    double framecourant = myPlayer->getCurrentFrame();
    img = myPlayer->showImage(--framecourant);
    displayImage(img, framecourant);
}

void MainWindow::on_forwardButton_clicked()
{
    QImage img;
    myPlayer->Stop();
    double framecourant = myPlayer->getCurrentFrame();
    img = myPlayer->showImage(++framecourant);
    displayImage(img, framecourant);
}

void MainWindow::mousePressEvent(QMouseEvent *evt){
    Mat org, tmp;
    Point pre_pt = (-1,-1);
    char coord[16];
    myPlayer->Stop();
    double framecourant = myPlayer->getCurrentFrame();
    org = myPlayer->getcurrentImage(framecourant);
    org.copyTo(tmp);
    QPoint point = ui->VideoLbl->mapFrom(this, evt->pos());
    int x = point.x();
    int y = point.y();
    sprintf_s(coord,"(%d,%d)",x,y);
    pre_pt = Point(x,y);
    putText(tmp,coord,pre_pt,FONT_HERSHEY_SIMPLEX,1,Scalar(255,0,0,0),2,8);//Display coordinates in the window
    circle(tmp,pre_pt,2,Scalar(255,0,0,0),CV_FILLED,CV_AA,0);
    QImage img = QImage((const unsigned char*)(tmp.data),
                  tmp.cols,tmp.rows,QImage::Format_RGB888);
    displayImage(img, framecourant);
    ui->statusBar->showMessage(QString("Mouse move (%1,%2)").arg(x).arg(y));
}
/*
void MainWindow::mouseMoveEvent(QMouseEvent *evt){
    QPoint point = ui->VideoLbl->mapFrom(this, evt->pos());

}*/

/*void MainWindow::Mouse_current_pos(){
     ui->statusBar->showMessage(QString("Mouse move (%1,%2)").arg(ui->VideoLbl->x).arg(ui->VideoLbl->y));
}*/

bool MainWindow::eventFilter(QObject * object, QEvent * event){
    Mat org, tmp;
    Point pre_pt = (-1,-1);
    char coord[16];
    double framecourant = myPlayer->getCurrentFrame();
    org = myPlayer->getcurrentImage(framecourant);
    if(object == ui->VideoLbl){
        if(event->type() == QEvent::MouseButtonPress){
            QMouseEvent *mouseEvent = (QMouseEvent *)event;
            org.copyTo(tmp);
            QPoint point = ui->VideoLbl->mapFrom(this,mouseEvent->pos());
            int x = point.x();
            int y = point.y();
            sprintf_s(coord,"(%d,%d)",x,y);
            pre_pt = Point(x,y);
            putText(tmp,coord,pre_pt,FONT_HERSHEY_SIMPLEX,0.5,Scalar(255,0,0,0),2,8);//Display coordinates in the window
            namedWindow("img",WINDOW_NORMAL);
            imshow("img",tmp);
        }
    }
    return QMainWindow::eventFilter(object, event);
}

