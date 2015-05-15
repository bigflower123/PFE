#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->showNormal();
    myPlayer = new player();
    /*********choose and show video******************/
    QObject::connect(ui->actionOuvrirVideo, SIGNAL(triggered()), this, SLOT(chooseVideo()));
    QObject::connect(myPlayer, SIGNAL(processedImage(QImage, QString)), this, SLOT(updatePlayerUI(QImage, QString)));
    /***********************************************/
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
    ui->quickbackwardButton->setEnabled(false);
    ui->quickforwardButton->setEnabled(false);
    ui->trajectoirecheckBox->setEnabled(false);
    ui->debutButton->setEnabled(false);
    ui->finButton->setEnabled(false);
    ui->ouvrirButton->setVisible(false);
    ui->savefinButton->setEnabled(false);
    ui->VideoLbl->setEnabled(false);
    /***********************************/
    ui->actionInformationObjet->setEnabled(false);

    /*************open dialog**************/
    QObject::connect(ui->actionInformationObjet, SIGNAL(triggered()),this, SLOT(openInformationDialog()));
    QObject::connect(ui->actionDeplacement, SIGNAL(triggered()),this, SLOT(openDeplacementDialog()));
    /**************************************/
    /******Initialisation******************/
    start = 0;
    fin = 0;
    /*************************************/

}

/**
 * Destructors of MainWindow
 * @brief MainWindow::~MainWindow
 */
MainWindow::~MainWindow()
{
    delete myPlayer;
    delete infoDialog;
    delete ui;
}

/**
 * @brief MainWindow::displayImage
 * @param img: the image to display dans la window
 * @param framecourant: number of frame
 * @param tmpInfo: information to display in the listWidget
 */
void MainWindow::displayImage(QImage& img, double framecourant, QString tmpInfo)
{
    ui->VideoLbl->setAlignment(Qt::AlignCenter);
    //Set the image in the VideoLbl
    ui->VideoLbl->setPixmap(QPixmap::fromImage(img).scaled(ui->VideoLbl->size(),
                            Qt::KeepAspectRatio, Qt::FastTransformation));
    //Adjust size of the video
    ui->VideoLbl->adjustSize();
    //Set the value of Slider
    ui->videoSlider->setValue(framecourant);
    // Set the value of number of current frame
    ui->currentLable->setText(QString::number(framecourant));

    if(tmpInfo != ""){
          QListWidgetItem* lst1 = new QListWidgetItem(tmpInfo, ui->listWidget);
          ui->listWidget->addItem(lst1);
          //QListWidget moving to end of list automatically
          //ui->listWidget->scrollToBottom();
    }
}

/**
 * Appelle le fonction to show video and show data in ListWidget
 * @brief MainWindow::updatePlayerUI
 * @param img: image to display
 * @param tmpInfo: information of coordinates
 */
void MainWindow::updatePlayerUI(QImage img, QString tmpInfo)
{
    if (!img.isNull())
    {
        displayImage(img, myPlayer->getCurrentFrame(),tmpInfo);
    }
}

/**
 * Choose a video
 * @brief MainWindow::chooseVideo
 */
void MainWindow::chooseVideo()
{
    int nbFrame = 0;
    myPlayer->setFileName("");
    ui->playBtn->setText(tr("Play"));
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
            //Set the video name to window title
            this->setWindowTitle(name.fileName());
            this->videoName = name.fileName().left(name.fileName().length()-4);
            /************************************/
            ui->playBtn->setEnabled(true);
            ui->videoSlider->setEnabled(true);
            ui->backwardButton->setEnabled(true);
            ui->forwardButton->setEnabled(true);
            ui->quickbackwardButton->setEnabled(true);
            ui->quickforwardButton->setEnabled(true);
            nbFrame = myPlayer->getNumberOfFrames();
            ui->videoSlider->setMinimum(1);
            ui->videoSlider->setMaximum(nbFrame);
            ui->videoSlider->setValue(1);
            ui->totalLable->setText(QString::number(nbFrame));
            ui->currentLable->setText(QString::number(1));
            ui->finLabel->setText(QString::number(nbFrame));
            fin = nbFrame;
            myPlayer->setVideoFin(fin);
            //Show first image of video dans VideoLabel
            Mat firstimg = myPlayer->getFirstFrame();
            cv::cvtColor(firstimg, firstimg, CV_BGR2RGB);
            this->displayImage(QImage((const unsigned char*)(firstimg.data),
                               firstimg.cols,firstimg.rows,QImage::Format_RGB888),1,"");
        }
    }
    //Clear listWidget
    ui->listWidget->clear();
    //Checkbox
    if(ui->trajectoirecheckBox->isChecked()){
        ui->trajectoirecheckBox->setChecked(false);
        ui->trajectoirecheckBox->setEnabled(false);
        myPlayer->trajectoreChecked = false;
    }
    //Release dst, object choose
    dst = Mat(Size(100, 100), CV_8UC3, Scalar(0, 0, 0));
    this->dst.release();
    //Set flagTimeschoose
    myPlayer->setFlagTimes(0);
    ui->VideoLbl->setEnabled(true);
}


/**
 * Choisir de répertoire à sauvegarder les données de trajectoire
 * @brief MainWindow::chooseInfoPath
 */
void MainWindow::chooseInfoPath()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save trajectoire", "",
                                                    "csv fichiers (*.csv);;All files (*.*)");
    myPlayer->setFileInfoName(fileName);
}

/**
 * stop and start the video
 * @brief MainWindow::on_playBtn_clicked
 */
void MainWindow::on_playBtn_clicked()
{
    if (myPlayer->isStopped())
    {
        if(flagVisualier == true){
            if(myPlayer->getInfoPath() == ""){
                QMessageBox msgBox;
                msgBox.setText("Vous n'avez pas choisit le fichier!");
                msgBox.exec();
            }else{
                myPlayer->Play();
                ui->playBtn->setText(tr("Stop"));
            }
        }
        if(flagTraiter == true){
            myPlayer->Play();
            ui->playBtn->setText(tr("Stop"));
            /***************************************/
            if(myPlayer->trajectoreChecked == true){
                ui->backwardButton->setEnabled(false);
                ui->forwardButton->setEnabled(false);
                ui->quickbackwardButton->setEnabled(false);
                ui->quickforwardButton->setEnabled(false);
                ui->debutButton->setEnabled(false);
                ui->finButton->setEnabled(false);
            }
        }
        /*************************************/
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
    vector<Point2f> vlist;
    Mat img = myPlayer->showImage(postionSlider);
    if(this->flagVisualier == true){
        myPlayer->drawTrack(postionSlider,img);
        QImage qimg = QImage((unsigned char*) img.data, img.cols, img.rows, QImage::Format_RGB888);
        //Modifier ListWidget
        QStringList list = myPlayer->getStrList();
        ui->listWidget->clear();
        ui->listWidget->addItems(list);
        displayImage(qimg, postionSlider, "");
    }
    if(this->flagTraiter == true){
        QImage qimg = QImage((unsigned char*) img.data, img.cols, img.rows, QImage::Format_RGB888);
        displayImage(qimg, postionSlider, "");
    }
}

void MainWindow::on_videoSlider_sliderMoved(int position)
{
    ui->currentLable->setText(QString::number(position));
    postionSlider = position;
}
/*******************************************/


/************Backward and Forward*****************/
/**
 * Reculer le vidéo lentement
 * @brief MainWindow::on_backwardButton_clicked
 */
void MainWindow::on_backwardButton_clicked()
{
    //QImage img;
    vector<Point2f> vlist;
    myPlayer->Stop();
    double framecourant = myPlayer->getCurrentFrame();
    if(framecourant > 0){
        Mat img = myPlayer->showImage(--framecourant);
        //Modifier ListWidget
        if(this->flagVisualier == true){
            myPlayer->drawTrack(framecourant,img);
            QImage qimg = QImage((unsigned char*) img.data, img.cols, img.rows, QImage::Format_RGB888);
            //Modifier ListWidget
            QStringList list = myPlayer->getStrList();
            ui->listWidget->clear();
            ui->listWidget->addItems(list);
            displayImage(qimg, framecourant, "");
        }
        if(this->flagTraiter == true){
            QImage qimg = QImage((unsigned char*) img.data, img.cols, img.rows, QImage::Format_RGB888);
            displayImage(qimg, framecourant, "");
        }
    }

}

/**
 * avancer le vidéo lentement
 * @brief MainWindow::on_forwardButton_clicked
 */
void MainWindow::on_forwardButton_clicked()
{
    myPlayer->Stop();
    double framecourant = myPlayer->getCurrentFrame();
    if(framecourant < myPlayer->getNumberOfFrames()){
        Mat img = myPlayer->getNextframe();
        //Modifier ListWidget
        if(this->flagVisualier == true){
            myPlayer->drawTrack(framecourant,img);
            QImage qimg = QImage((unsigned char*) img.data, img.cols, img.rows, QImage::Format_RGB888);
            //Modifier ListWidget
            QStringList list = myPlayer->getStrList();
            ui->listWidget->clear();
            ui->listWidget->addItems(list);
            displayImage(qimg, framecourant, "");
        }
        if(this->flagTraiter == true){
            QImage qimg = QImage((unsigned char*) img.data, img.cols, img.rows, QImage::Format_RGB888);
            displayImage(qimg, framecourant, "");
        }
    }

}

/**
 * Reculer le vidéo rapidement
 * @brief MainWindow::on_quickbackwardButton_clicked
 */
void MainWindow::on_quickbackwardButton_clicked()
{
    myPlayer->Stop();
    double framecourant = myPlayer->getCurrentFrame();
    framecourant = framecourant - 10;
    if(framecourant >= 0){
        Mat img = myPlayer->showImage(framecourant);
        if(this->flagVisualier == true){
            myPlayer->drawTrack(framecourant,img);
            QImage qimg = QImage((unsigned char*) img.data, img.cols, img.rows, QImage::Format_RGB888);
            //Modifier ListWidget
            QStringList list = myPlayer->getStrList();
            ui->listWidget->clear();
            ui->listWidget->addItems(list);
            displayImage(qimg, framecourant,"");
        }
        if(this->flagTraiter == true){
            QImage qimg = QImage((unsigned char*) img.data, img.cols, img.rows, QImage::Format_RGB888);
            displayImage(qimg, framecourant,"");
        }
    }
}

/**
 * avancer le vidéo rapidement
 * @brief MainWindow::on_quickforwardButton_clicked
 */
void MainWindow::on_quickforwardButton_clicked()
{
    myPlayer->Stop();
    double framecourant = myPlayer->getCurrentFrame();
    framecourant = framecourant + 10;
    if(framecourant <= myPlayer->getNumberOfFrames()){
        Mat img = myPlayer->showImage(framecourant);
        if(this->flagVisualier == true){
            myPlayer->drawTrack(framecourant,img);
            QImage qimg = QImage((unsigned char*) img.data, img.cols, img.rows, QImage::Format_RGB888);
            //Modifier ListWidget
            QStringList list = myPlayer->getStrList();
            ui->listWidget->clear();
            ui->listWidget->addItems(list);
            displayImage(qimg, framecourant,"");
        }
        if(this->flagTraiter == true){
            QImage qimg = QImage((unsigned char*) img.data, img.cols, img.rows, QImage::Format_RGB888);
            displayImage(qimg, framecourant,"");
        }
    }
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
    this->flagmovepresse = false;
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
    displayImage(qimg,framecourant,"");
    ui->statusBar->showMessage(QString("Mouse press (%1,%2)").arg(x).arg(y));
}

void MainWindow::myMouseMovePressed(int x, int y)
{
    myPlayer->Stop();
    this->flagmovepresse = true;
    double framecourant = myPlayer->getCurrentFrame();
    img.copyTo(tmp);
    sprintf_s(temp,"(%d,%d)",x,y);
    cur_pt = Point(x*widthscale,y*heightscale);
    putText(tmp,temp,cur_pt,FONT_HERSHEY_SIMPLEX,0.8,Scalar(0,0,255,0),2,8);
    rectangle(tmp,pre_pt,cur_pt,Scalar(0,255,0,0),2,8,0);//Drag the mouse, display the rectangle on the temporary image
    QImage qimg = QImage((const unsigned char*)(tmp.data),
                  tmp.cols,tmp.rows,QImage::Format_RGB888);
    displayImage(qimg,framecourant,"");
    ui->statusBar->showMessage(QString("Mouse move and press (%1,%2)").arg(x).arg(y));
}


void MainWindow::myMouseLeft(int x, int y)
{
    myPlayer->Stop();
    double framecourant = myPlayer->getCurrentFrame();
    if(this->flagmovepresse == true){
        tmp.copyTo(img);
        sprintf_s(temp,"(%d,%d)",x,y);
        cur_pt = Point(x*widthscale,y*heightscale);
        putText(img,temp,cur_pt,FONT_HERSHEY_SIMPLEX,0.8,Scalar(255,0,0,0),2,8);
        circle(img,pre_pt,2,Scalar(255,0,0,0),CV_FILLED,CV_AA,0);
        QImage qimg = QImage((const unsigned char*)(img.data),
                      img.cols,img.rows,QImage::Format_RGB888);
        displayImage(qimg,framecourant,"");
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
        //Get the object choose
        dst = org(Rect(min(cur_pt.x,pre_pt.x),min(cur_pt.y,pre_pt.y),zonewidth, zoneheight));
        Mat RGBdst;
        cv::cvtColor(dst, RGBdst, CV_BGR2RGB);
        myPlayer->setObjectChoose(RGBdst);
        //Set checkbox and menu InformationObject true
        ui->actionInformationObjet->setEnabled(true);
        if(!ui->trajectoirecheckBox->isEnabled())
            ui->trajectoirecheckBox->setEnabled(true);
        //Set flagContinue
        myPlayer->setFlagContinue(0);
    }
}


/******************Choose object*******************/

/******************Open dialog********************/
/**
 * open information dialog
 * @brief MainWindow::openInformationDialog
 */
void MainWindow::openInformationDialog()
{
    infoDialog = new InformationDialog(myPlayer);
    infoDialog->setModal(false);
    infoDialog->exec();
}

/**
 * open déplacement dialog
 * @brief MainWindow::openDeplacementDialog
 */
void MainWindow::openDeplacementDialog()
{
        deplacementDialog = new DeplacementMaxDialog(myPlayer);
        deplacementDialog->setModal(false);
        deplacementDialog->exec();
}

/**************************************************/

/**
 * set the begin of the video
 * @brief MainWindow::on_debutButton_clicked
 */
void MainWindow::on_debutButton_clicked()
{
    start = ui->currentLable->text().toInt();
    if(fin >= start){
        ui->debutLabel->setText(QString::number(start));
        myPlayer->setVideoStart(start);
    }
}

/**
 * set fin of the video
 * @brief MainWindow::on_finButton_clicked
 */
void MainWindow::on_finButton_clicked()
{
    fin = ui->currentLable->text().toInt();
    if(fin >= start){
        ui->finLabel->setText(QString::number(fin));
        myPlayer->setVideoFin(fin);
    }
}
/*****************************************************/
/**
 * Checkbox pour définir si on détecter
 * @brief MainWindow::on_trajectoirecheckBox_clicked
 */
void MainWindow::on_trajectoirecheckBox_clicked()
{
    if(!myPlayer->trajectoreChecked){
         ui->trajectoirecheckBox->setChecked(true);
         myPlayer->trajectoreChecked = true;
         //On peut définir début et fin de vidéo avec trajectoire
         ui->debutButton->setEnabled(true);
         ui->finButton->setEnabled(true);
         ui->savefinButton->setEnabled(true);
    }else{
         ui->trajectoirecheckBox->setChecked(false);
         myPlayer->trajectoreChecked = false;
         //Mettre débutvideo à 0 et finvideo à MaxFrameVideo
         ui->debutButton->setEnabled(false);
         ui->finButton->setEnabled(false);
         ui->savefinButton->setEnabled(false);
         ui->debutLabel->setText(QString::number(0));
         myPlayer->setVideoStart(0);
         ui->finLabel->setText(QString::number(myPlayer->getNumberOfFrames()));
         myPlayer->setVideoFin(myPlayer->getNumberOfFrames());
    }
}

/**
 * Save the informations of coordinates
 * @brief MainWindow::on_savefinButton_clicked
 */
void MainWindow::on_savefinButton_clicked()
{
    myPlayer->Stop();
    ui->playBtn->setText("Play");
    //QMessageBox pour confirmer de sauvegarder
    QMessageBox msgBox;
    QFile infoFile;
    QTextStream output;
    QString listitem;
    msgBox.setInformativeText("Voulez-vous confirmer l'enregistrement?");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    int ret = msgBox.exec();
    if(ret == QMessageBox::Save){
        //myPlayer->setSaveFin(true);
        /****Créer une répertoire avec le nom de vidéo*************/
        QDir *temp = new QDir;
        QString repertoire = "C://temp/"+videoName;
        bool exist = temp->exists(repertoire);
        if(!exist)
        {
           bool ok = temp->mkdir(repertoire);
        }
        //Ouvrir la fenêtre de sauvegarder
        QString fileName = QFileDialog::getSaveFileName(this, "Sauvegarder trajectoire", repertoire,
                                                        "csv fichiers (*.csv);;All files (*.*)");
        infoFile.setFileName(fileName);
        infoFile.open(QIODevice::WriteOnly);
        /* Check it opened OK */
        if(!infoFile.isOpen()){
            qDebug() <<  "Error, unable to open" ;
        }
        output.setDevice(&infoFile);
        //Sauvegarder les textes dans QListWidget
        int c = ui->listWidget->count();
        for(int row = 0; row < c; row++){
            QListWidgetItem *item = ui->listWidget->item(row);
            listitem = item->text() + "\n";
            output<<listitem;
        }
    }
}

/**
 * Ouvrir la fichier de données
 * @brief MainWindow::on_ouvrirButton_clicked
 */
void MainWindow::on_ouvrirButton_clicked()
{
    QString fileInfoName = QFileDialog::getOpenFileName(
                            this, "Ouvrir données",
                            "C://temp/"+videoName,
                            "csv fichiers (*.csv);;All files (*.*)");
    myPlayer->setFileInfoName(fileInfoName);
}


/****************Choisir la modalité*************************/
/**
 * RadioButton: Modalité visualiser
 * @brief MainWindow::on_visualiserButton_clicked
 */
void MainWindow::on_visualiserButton_clicked()
{
    //Clear listWidget
    ui->listWidget->clear();
    if(ui->visualiserButton->isChecked()){
        myPlayer->setFlagVisualiser(true);
        this->flagVisualier = true;
        myPlayer->setFlagTraiter(false);
        this->flagTraiter = false;
        ui->savefinButton->setVisible(false);
        ui->ouvrirButton->setVisible(true);
        myPlayer->trajectoreChecked = false;
        ui->trajectoirecheckBox->setChecked(false);
        ui->trajectoirecheckBox->setEnabled(false);
        ui->forwardButton->setEnabled(true);
        ui->backwardButton->setEnabled(true);
        ui->quickforwardButton->setEnabled(true);
        ui->quickbackwardButton->setEnabled(true);
    }else{
        myPlayer->setFlagVisualiser(false);
        this->flagVisualier = false;
    }

}

/**
 * RadioButton: Modalité traiter
 * @brief MainWindow::on_traiterButton_clicked
 */
void MainWindow::on_traiterButton_clicked()
{
    //Clear listWidget
    ui->listWidget->clear();
    if(ui->traiterButton->isChecked()){
        myPlayer->setFlagTraiter(true);
        this->flagTraiter = true;
        myPlayer->setFlagVisualiser(false);
        this->flagVisualier = false;
        ui->savefinButton->setVisible(true);
        ui->ouvrirButton->setVisible(false);
    }else{
         myPlayer->setFlagTraiter(false);
         this->flagTraiter = false;
    }
}

/**************************************************************/
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














