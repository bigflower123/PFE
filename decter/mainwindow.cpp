#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    myPlayer = new player();
    QObject::connect(ui->actionOuvrirVideo, SIGNAL(triggered()), this, SLOT(chooseVideo()));
    QObject::connect(ui->actionSauvegarderVideo, SIGNAL(triggered()), this, SLOT(choosePath()));
    QObject::connect(myPlayer, SIGNAL(processedImage(QImage)), this, SLOT(updatePlayerUI(QImage)));
    /*****For choose object**************/
    ui->VideoLbl->setMouseTracking(true);
    QObject::connect(ui->VideoLbl, SIGNAL(Mouse_Move(int, int)), this, SLOT(myMouseMove(int, int)));
    QObject::connect(ui->VideoLbl, SIGNAL(Mouse_Pressed(int,int)), this, SLOT(myMousePressed(int, int)));
    QObject::connect(ui->VideoLbl, SIGNAL(Mouse_Left(int, int)), this, SLOT(myMouseLeft(int, int)));
    QObject::connect(ui->VideoLbl, SIGNAL(Mouse_Move_Pressed(int,int)), this, SLOT(myMouseMovePressed(int, int)));
    /************************************/

    /***Set Button et Slider disabled****/
    ui->playBtn->setEnabled(false);
    ui->backwardButton->setEnabled(false);
    ui->forwardButton->setEnabled(false);
    ui->videoSlider->setEnabled(false);
    /***********************************/
    QObject::connect(ui->actionInformationObjet, SIGNAL(triggered()),this, SLOT(openInformationDialog()));
}

MainWindow::~MainWindow()
{
    delete myPlayer;
    delete infoDialog;
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
    ui->VideoLbl->adjustSize(); //Adjust size of the video
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
 * Choisir de répertoire à sauvegarder
 * @brief MainWindow::choosePath
 */
void MainWindow::choosePath()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save video", "",
                                                    "Vidéo fichiers (*.avi *.mp4 *.asf);;All files (*.*)");
    myPlayer->setFileName(fileName);
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

/***************Slider*********************/
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
/*******************************************/


/************Backward and Forward*****************/
/**
 * Reculer le vidéo
 * @brief MainWindow::on_backwardButton_clicked
 */
void MainWindow::on_backwardButton_clicked()
{
    QImage img;
    myPlayer->Stop();
    double framecourant = myPlayer->getCurrentFrame();
    img = myPlayer->showImage(--framecourant);
    displayImage(img, framecourant);
}

/**
 * avancer le vidéo
 * @brief MainWindow::on_forwardButton_clicked
 */
void MainWindow::on_forwardButton_clicked()
{
    QImage img;
   // myPlayer->Stop();
    double framecourant = myPlayer->getCurrentFrame();
    img = myPlayer->showImage(++framecourant);
    displayImage(img, framecourant);
}
/*************Backward and Forward*****************/

/************Choose object*************************/
/**
 * Mouse move in the zone of VideoLbl, show the coordinate
 * @brief MainWindow::myMouseMove
 * @param x
 * @param y
 */
void MainWindow::myMouseMove(int x, int y)
{
    ui->statusBar->showMessage(QString("Mouse move (%1,%2)").arg(x).arg(y));
}

/**
 * Mouse pressed, show the coordiantes and draw a point at that position
 * @brief MainWindow::myMousePressed
 * @param x
 * @param y
 */
void MainWindow::myMousePressed(int x, int y)
{
    myPlayer->Stop();
    double framecourant = myPlayer->getCurrentFrame();
    org = myPlayer->getcurrentImage(framecourant);
    org.copyTo(img);//Copy the original images to 'img'
    sprintf_s(temp,"(%d,%d)",x,y);

    //Get width and height of the original video
    imgheight = myPlayer->getFrameHeight();
    imgwidth = myPlayer->getFrameWidth();
    //Get width and height of the VideoLabel
    labelheight = ui->VideoLbl->size().height();
    labelwidth = ui->VideoLbl->size().width();
    //Get width and height scale
    heightscale = imgheight/labelheight;
    widthscale = imgwidth/labelwidth;
    //Le coordiante of point in the original image
    pre_pt = Point(x*widthscale,y*heightscale);

    putText(img,temp,pre_pt,FONT_HERSHEY_SIMPLEX,0.8,Scalar(255,0,0,0),2,8);//Display coordinates in the window
    circle(img,pre_pt,2,Scalar(255,0,0,0),CV_FILLED,CV_AA,0);//draw circle
    QImage qimg = QImage((const unsigned char*)(img.data),
                  img.cols,img.rows,QImage::Format_RGB888);
    displayImage(qimg,framecourant);
    ui->statusBar->showMessage(QString("Mouse press (%1,%2)").arg(x).arg(y));
}

void MainWindow::myMouseMovePressed(int x, int y)
{
    myPlayer->Stop();
    double framecourant = myPlayer->getCurrentFrame();
    img.copyTo(tmp);
    sprintf_s(temp,"(%d,%d)",x,y);
    cur_pt = Point(x*widthscale,y*heightscale);
    putText(tmp,temp,cur_pt,FONT_HERSHEY_SIMPLEX,0.8,Scalar(0,0,255,0),2,8);
    rectangle(tmp,pre_pt,cur_pt,Scalar(0,255,0,0),2,8,0);//Drag the mouse, display the rectangle on the temporary image
    QImage qimg = QImage((const unsigned char*)(tmp.data),
                  tmp.cols,tmp.rows,QImage::Format_RGB888);
    displayImage(qimg,framecourant);
    ui->statusBar->showMessage(QString("Mouse move and press (%1,%2)").arg(x).arg(y));
}


void MainWindow::myMouseLeft(int x, int y)
{
    myPlayer->Stop();
    double framecourant = myPlayer->getCurrentFrame();
    tmp.copyTo(img);
    sprintf_s(temp,"(%d,%d)",x,y);
    cur_pt = Point(x*widthscale,y*heightscale);
    putText(img,temp,cur_pt,FONT_HERSHEY_SIMPLEX,0.8,Scalar(255,0,0,0),2,8);
    circle(img,pre_pt,2,Scalar(255,0,0,0),CV_FILLED,CV_AA,0);
    QImage qimg = QImage((const unsigned char*)(img.data),
                  img.cols,img.rows,QImage::Format_RGB888);
    displayImage(qimg,framecourant);
    img.copyTo(tmp);
    ui->statusBar->showMessage(QString("Mouse left (%1,%2)").arg(x).arg(y));

    //Intercept the image surrounded by rectangle, and saved it to dst
    int zonewidth = abs(pre_pt.x - cur_pt.x);
    int zoneheight = abs(pre_pt.y - cur_pt.y);
    if(zonewidth < zoneheight)
    {taille = zonewidth;}
    else
    {taille = zoneheight;}
    if (zonewidth == 0 || zoneheight == 0)
    {
        printf("width == 0 || height == 0");
    }
    dst = org(Rect(min(cur_pt.x,pre_pt.x),min(cur_pt.y,pre_pt.y),zonewidth, zoneheight));
}

/******************Choose object*******************/


void MainWindow::openInformationDialog()
{
    infoDialog = new InformationDialog(this);
    infoDialog->show();
}


/************Choose object*************************/
/*void MainWindow::mousePressEvent(QMouseEvent *evt){
    char coord[16];
    myPlayer->Stop();
    double framecourant = myPlayer->getCurrentFrame();
    org = myPlayer->getcurrentImage(framecourant);
    org.copyTo(img);
    QPoint point = ui->VideoLbl->mapFrom(this, evt->pos());
    int x = point.x();
    int y = point.y();
    sprintf_s(coord,"(%d,%d)",x,y);
    QImage qimg = QImage((const unsigned char*)(img.data),
                  img.cols,img.rows,QImage::Format_RGB888);
    //double labelsize = ui->VideoLbl->size();
    int imgheight = qimg.size().height();
    int imgwidth = qimg.size().width();
    int labelheight = ui->VideoLbl->size().height();
    int labelwidth = ui->VideoLbl->size().width();
    valueScale = (imgheight * imgwidth)/(labelheight * labelwidth);
    printf("%d",valueScale);
    pre_pt = Point(x*valueScale,y*valueScale);
    putText(img,coord,pre_pt,FONT_HERSHEY_SIMPLEX,1,Scalar(255,0,0,0),2,8);//Display coordinates in the window
    circle(img,pre_pt,2,Scalar(255,0,0,0),CV_FILLED,CV_AA,0);
    displayImage(qimg, framecourant);
    ui->statusBar->showMessage(QString("Mouse press (%1,%2)").arg(x).arg(y));
}

void MainWindow::mouseMoveEvent(QMouseEvent *evt){
    char coord[16];
    myPlayer->Stop();
    double framecourant = myPlayer->getCurrentFrame();
    img.copyTo(tmp);
    QPoint point = ui->VideoLbl->mapFrom(this, evt->pos());
    int x = point.x();
    int y = point.y();
    sprintf_s(coord,"(%d,%d)",x,y);
    cur_pt = Point(x,y);
    if(evt->buttons() & Qt::LeftButton){
        putText(tmp,coord,cur_pt,FONT_HERSHEY_SIMPLEX,1,Scalar(0,0,255,0),2,8);
        rectangle(tmp,pre_pt,cur_pt,Scalar(0,255,0,0),2,8,0);//Drag the mouse, display the rectangle on the temporary image
        QImage qimg = QImage((const unsigned char*)(tmp.data),
                      tmp.cols,tmp.rows,QImage::Format_RGB888);
        displayImage(qimg, framecourant);
        ui->statusBar->showMessage(QString("Mouse move(%1,%2) et left buttons pressed").arg(x).arg(y));
    }else{
        putText(tmp,coord,cur_pt,FONT_HERSHEY_SIMPLEX,1,Scalar(0,0,255,0),2,8);
        QImage qimg = QImage((const unsigned char*)(tmp.data),
                      tmp.cols,tmp.rows,QImage::Format_RGB888);
        displayImage(qimg, framecourant);
        ui->statusBar->showMessage(QString("Mouse move(%1,%2)").arg(x).arg(y));
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent * evt){
    char coord[16];
    myPlayer->Stop();
    double framecourant = myPlayer->getCurrentFrame();
    tmp.copyTo(img);
    QPoint point = ui->VideoLbl->mapFrom(this, evt->pos());
    int x = point.x();
    int y = point.y();
    sprintf_s(coord,"(%d,%d)",x,y);
    cur_pt = Point(x,y);
    int width = abs(pre_pt.x - cur_pt.x);
    int height = abs(pre_pt.y - cur_pt.y);
    if(width<height)
    {taille = width;}
    else
    {taille = height;}
    if (width == 0 || height == 0)
    {
       ui->statusBar->showMessage(QString("Choose a object"));
    }
    if(width != 0 && height != 0){
        putText(img,coord,cur_pt,FONT_HERSHEY_SIMPLEX,1,Scalar(255,0,0,0),2,8);
        circle(img,pre_pt,2,Scalar(255,0,0,0),CV_FILLED,CV_AA,0);
        QImage qimg = QImage((const unsigned char*)(tmp.data),
                      tmp.cols,tmp.rows,QImage::Format_RGB888);
        displayImage(qimg, framecourant);
        img.copyTo(tmp);
        ui->statusBar->showMessage(QString("Mouse release"));
    }

    Mat dst = org(Rect(min(cur_pt.x,pre_pt.x),min(cur_pt.y,pre_pt.y),width,height));
    myPlayer->setObjectChoose(dst);

}*/
/*****************************Choose object********************/
/*void MainWindow::Mouse_current_pos(){
     ui->statusBar->showMessage(QString("Mouse move (%1,%2)").arg(ui->VideoLbl->x).arg(ui->VideoLbl->y));
}*/

/*bool MainWindow::eventFilter(QObject * obj, QEvent * evt){
    Mat org, tmp, img;
    Point pre_pt = (-1,-1);
    Point cur_pt = (-1,-1);
    char coord[16];
    QMouseEvent *mouseEvent = (QMouseEvent *)evt;
    QPoint point = ui->VideoLbl->mapFrom(this, mouseEvent->pos());
    int x = point.x();
    int y = point.y();
    if(obj == ui->VideoLbl){
        double framecourant = myPlayer->getCurrentFrame();
        org = myPlayer->getcurrentImage(framecourant);
        if(evt->type() == QEvent::MouseButtonPress){
            if(mouseEvent->buttons()&Qt::LeftButton){

                org.copyTo(img);
                sprintf_s(coord,"(%d,%d)",x,y);
                pre_pt = Point(x,y);
                putText(img,coord,pre_pt,FONT_HERSHEY_SIMPLEX,1,Scalar(255,0,0,0),2,8);//Display coordinates in the window
                circle(img,pre_pt,2,Scalar(255,0,0,0),CV_FILLED,CV_AA,0);
                QImage qimg = QImage((const unsigned char*)(img.data),
                              img.cols,img.rows,QImage::Format_RGB888);
                displayImage(qimg, framecourant);
                ui->statusBar->showMessage(QString("Mouse press (%1,%2)").arg(x).arg(y));
            }
        }else if(evt->type() == QEvent::MouseMove){
           img.copyTo(tmp);
           sprintf_s(coord,"(%d,%d)",x,y);
           cur_pt = Point(x,y);
           putText(tmp,coord,cur_pt,FONT_HERSHEY_SIMPLEX,0.5,Scalar(0,0,255,0),2,8);
           rectangle(tmp,pre_pt,cur_pt,Scalar(0,255,0,0),2,8,0);//Drag the mouse, display the rectangle on the temporary image
           QImage qimg = QImage((const unsigned char*)(tmp.data),
                         tmp.cols,tmp.rows,QImage::Format_RGB888);
           displayImage(qimg, framecourant);
           ui->statusBar->showMessage(QString("Mouse move"));
        }else if(evt->type() == QEvent::MouseButtonRelease){
           ui->statusBar->showMessage(QString("Mouse release"));
        }
        else{
          return false;
        }
    }
    return QMainWindow::eventFilter(obj, evt);
}*/

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
