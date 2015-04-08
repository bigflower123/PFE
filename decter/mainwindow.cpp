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
    QObject::connect(ui->actionSauvegarderVideo, SIGNAL(triggered()), this, SLOT(choosePath()));
    QObject::connect(ui->actionSauvegarderDonnees, SIGNAL(triggered()),this, SLOT(chooseInfoPath()));
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
    ui->commenttextEdit->setEnabled(false);
    ui->commentButton->setEnabled(false);
    ui->savefinButton->setEnabled(false);
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
void MainWindow::displayImage(QImage& img, double framecourant, QString tmpInfo)
{
    ui->VideoLbl->setAlignment(Qt::AlignCenter);
    ui->VideoLbl->setPixmap(QPixmap::fromImage(img).scaled(ui->VideoLbl->size(),
                            Qt::KeepAspectRatio, Qt::FastTransformation));
    //Adjust size of the video
    ui->VideoLbl->adjustSize();

    if(tmpInfo != ""){
        if(tmpInfo != "-1"){
          QListWidgetItem* lst1 = new QListWidgetItem(tmpInfo, ui->listWidget);
          ui->listWidget->addItem(lst1);
          ui->videoSlider->setValue(base + framecourant-1);
          ui->currentLable->setText(QString::number(base + framecourant-1));
        }else{
          ui->videoSlider->setValue(framecourant);
          ui->currentLable->setText(QString::number(framecourant));
        }
    }else{
        ui->videoSlider->setValue(framecourant);
        ui->currentLable->setText(QString::number(framecourant));
    }
}

/**
 * Appelle le fonction to show video and show data in ListWidget
 * @brief MainWindow::updatePlayerUI
 * @param img
 * @param tmpInfo
 */
void MainWindow::updatePlayerUI(QImage img, QString tmpInfo)
{
    if (!img.isNull())
    {
        displayImage(img, myPlayer->getCurrentFrame(),tmpInfo);
        /*ui->R1label->setText(QString::number(myPlayer->thresh[0]));
        ui->R2label->setText(QString::number(myPlayer->thresh[1]));
        ui->V1label->setText(QString::number(myPlayer->thresh[2]));
        ui->V2label->setText(QString::number(myPlayer->thresh[3]));
        ui->B1label->setText(QString::number(myPlayer->thresh[4]));
        ui->B2label->setText(QString::number(myPlayer->thresh[5]));*/

       /* if(tmpInfo != ""){
            QListWidgetItem* lst1 = new QListWidgetItem(tmpInfo, ui->listWidget);
            ui->listWidget->insertItem(++itemNumber,lst1 );
        }*/
    }
}

/**
 * Choose a video
 * @brief MainWindow::chooseVideo
 */
void MainWindow::chooseVideo()
{
    int nbFrame = 0;
    //If InfoFile is open, we close it
    myPlayer->closeInfoFile();
    myPlayer->setFileName("");
    myPlayer->setSaveFin(false);
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
            //nbFrame = myPlayer->getNumberOfFrames();
            /*if(myPlayer->flagFileOpen == true){
                base = myPlayer->getFirstValue();
                //nbFrame = myPlayer->getCountLine();
                ui->videoSlider->setMinimum(base);
                ui->videoSlider->setMaximum(base + nbFrame);
                ui->videoSlider->setValue(base);
                //ui->totalLable->setText( getFormattedTime( (int)myPlayer->getNumberOfFrames()/(int)myPlayer->getFrameRate()) );
                ui->totalLable->setText(QString::number(base+nbFrame));
                ui->currentLable->setText(QString::number(base));
                ui->debutLabel->setText(QString::number(base));
                ui->finLabel->setText(QString::number(base+nbFrame));
                //Set video fin
                fin = base+nbFrame;
                myPlayer->setVideoFin(base+nbFrame);
            }else{*/
                nbFrame = myPlayer->getNumberOfFrames();
                ui->videoSlider->setMinimum(1);
                ui->videoSlider->setMaximum(nbFrame);
                ui->videoSlider->setValue(1);
                ui->totalLable->setText(QString::number(nbFrame));
                ui->currentLable->setText(QString::number(1));
                ui->finLabel->setText(QString::number(nbFrame));
                fin = nbFrame;
                myPlayer->setVideoFin(fin);
            //}
            //Show first image of video dans VideoLabel
            /*Mat firstimg = myPlayer->getFistFrame();
            cv::cvtColor(firstimg, firstimg, CV_BGR2RGB);
            this->displayImage(QImage((const unsigned char*)(firstimg.data),
                               firstimg.cols,firstimg.rows,QImage::Format_RGB888),1);*/
        }
    }
    //Clear listWidget
    ui->listWidget->clear();
    //Initialiser write stream
    //myPlayer->prepareSaveInfo();
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
}


/**
 * Choisir de répertoire à sauvegarder
 * @brief MainWindow::choosePath
 */
void MainWindow::choosePath()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save video", "",
                                                    "Vidéo fichiers (*.avi *.asf);;All files (*.*)");
    myPlayer->setFileName(fileName);
    //Initialiser write stream
     myPlayer->prepareSaveInfo();
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
    //Initialiser write stream
    //myPlayer->prepareSaveInfo();
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
        /***************************************/
        if(myPlayer->trajectoreChecked == true){
            ui->backwardButton->setEnabled(false);
            ui->forwardButton->setEnabled(false);
            ui->quickbackwardButton->setEnabled(false);
            ui->quickforwardButton->setEnabled(false);
            ui->debutButton->setEnabled(false);
            ui->finButton->setEnabled(false);
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
    //myPlayer->Play();
    //postionSlider = myPlayer->getCurrentFrame();
   /* ui->currentLable->setText(QString::number(postionSlider));
    Mat img = myPlayer->showImage(postionSlider);
    ui->VideoLbl->setAlignment(Qt::AlignCenter);
    ui->VideoLbl->setPixmap(QPixmap::fromImage(QImage((unsigned char*) img.data, img.cols, img.rows,
                           QImage::Format_RGB888)).scaled(ui->VideoLbl->size(),Qt::KeepAspectRatio,
                           Qt::FastTransformation));
    ui->VideoLbl->adjustSize(); //Adjust size of the video*/
    if(myPlayer->flagFileOpen == true){
        Mat img = myPlayer->showImage(postionSlider-base+1);
        QImage qimg = QImage((unsigned char*) img.data, img.cols, img.rows, QImage::Format_RGB888);
        //Modifier ListWidget
        QStringList list = myPlayer->getFileList(postionSlider-base+1);
        ui->listWidget->clear();
        ui->listWidget->addItems(list);
        displayImage(qimg, postionSlider, "-1");
    }else{
        Mat img = myPlayer->showImage(postionSlider);
        QImage qimg = QImage((unsigned char*) img.data, img.cols, img.rows, QImage::Format_RGB888);
        displayImage(qimg, postionSlider, "");
    }
}

void MainWindow::on_videoSlider_sliderMoved(int position)
{
    //myPlayer->setCurrentFrame(position);
    //ui->currentLable->setText( getFormattedTime( position/(int)myPlayer->getFrameRate()) );
    //ui->currentLable->setText(QString::number(myPlayer->getFrameRate()));
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
    myPlayer->Stop();
    double framecourant = myPlayer->getCurrentFrame();
    if(framecourant > 0){
        Mat img = myPlayer->showImage(--framecourant);
        //Modifier ListWidget
        if(myPlayer->flagFileOpen == true){
            QStringList list = myPlayer->getFileList(framecourant);
            ui->listWidget->clear();
            ui->listWidget->addItems(list);
            QImage qimg = QImage((unsigned char*) img.data, img.cols, img.rows, QImage::Format_RGB888);
            displayImage(qimg, framecourant, "-1");
        }else{
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
    long framecourant = myPlayer->getCurrentFrame();
    QString line = myPlayer->getNextInfo();
    if(framecourant < myPlayer->getNumberOfFrames()){
        Mat img = myPlayer->getNextframe();
        QImage qimg = QImage((unsigned char*) img.data, img.cols, img.rows, QImage::Format_RGB888);
        displayImage(qimg, ++framecourant, line);
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
        QImage qimg = QImage((unsigned char*) img.data, img.cols, img.rows, QImage::Format_RGB888);

        if(myPlayer->flagFileOpen == true){
            QStringList list = myPlayer->getFileList(framecourant);
            ui->listWidget->clear();
            ui->listWidget->addItems(list);
            displayImage(qimg, framecourant,"-1");
        }else{
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
        QImage qimg = QImage((unsigned char*) img.data, img.cols, img.rows, QImage::Format_RGB888);

        if(myPlayer->flagFileOpen == true){
            QStringList list = myPlayer->getFileList(framecourant);
            ui->listWidget->clear();
            ui->listWidget->addItems(list);
            displayImage(qimg, framecourant,"-1");
        }else{
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
 * Confirmer de sauvegarder le vidéo
 * @brief MainWindow::on_savefinButton_clicked
 */
void MainWindow::on_savefinButton_clicked()
{
    //QMessageBox pour confirmer de sauvegarder
    QMessageBox msgBox;
    QFile infoFile;
    QTextStream output;
    QString listitem;
    msgBox.setInformativeText("Voulez-vous confirmer d'enregistrer?");
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
    if(ui->visualiserButton->isChecked()){
        this->flagVisualier = true;
        ui->savefinButton->setVisible(false);
        ui->ouvrirButton->setVisible(true);
    }else{
        this->flagVisualier = false;
    }

}

/**
 * RadioButton: Modalité traiter
 * @brief MainWindow::on_traiterButton_clicked
 */
void MainWindow::on_traiterButton_clicked()
{
    if(ui->traiterButton->isChecked()){
        this->flagTraiter = true;
        ui->savefinButton->setVisible(true);
        ui->ouvrirButton->setVisible(false);
    }else{
        this->flagTraiter = false;
    }
}
/*******************************************************/
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












