#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    myPlayer = new player();
    QObject::connect(ui->actionOuvrirVideo, SIGNAL(triggered()), this, SLOT(chooseVideo()));
    QObject::connect(myPlayer, SIGNAL(processedImage(QImage)),
                     this, SLOT(updatePlayerUI(QImage)));
    ui->playBtn->setEnabled(false);
    ui->videoSlider->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete myPlayer;
    delete ui;
}

void MainWindow::updatePlayerUI(QImage img)
{
    if (!img.isNull())
    {
        ui->VideoLbl->setAlignment(Qt::AlignCenter);
        ui->VideoLbl->setPixmap(QPixmap::fromImage(img).scaled(ui->VideoLbl->size(),
                                                               Qt::KeepAspectRatio, Qt::FastTransformation));
        ui->videoSlider->setValue(myPlayer->getCurrentFrame());
        //ui->currentLable->setText( getFormattedTime( (int)myPlayer->getCurrentFrame()/(int)myPlayer->getFrameRate()) );
        ui->currentLable->setText(QString::number(myPlayer->getCurrentFrame()));
    }
}

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
            ui->videoSlider->setMaximum(myPlayer->getNumberOfFrames());
            //ui->totalLable->setText( getFormattedTime( (int)myPlayer->getNumberOfFrames()/(int)myPlayer->getFrameRate()) );
            ui->totalLable->setText(QString::number(myPlayer->getNumberOfFrames()));
        }
    }
}
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

QString MainWindow::getFormattedTime(int timeInSeconds){

    int seconds = (int) (timeInSeconds) % 60 ;
    int minutes = (int) ((timeInSeconds / 60) % 60);
    int hours   = (int) ((timeInSeconds / (60*60)) % 24);

    QTime t(hours, minutes, seconds);
    if (hours == 0 )
        return t.toString("mm:ss");
    else
        return t.toString("h:mm:ss");
}

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

