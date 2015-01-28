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
       // ui->VideoLbl->setPixmap(QPixmap::fromImage(img));
        ui->VideoLbl->setPixmap(QPixmap::fromImage(img).scaled(ui->VideoLbl->size(),
                                                               Qt::KeepAspectRatio, Qt::FastTransformation));
    }
}

void MainWindow::chooseVideo()
{
    //Open filedialog to choose video file
    QString filename = QFileDialog::getOpenFileName(
                this, "Ouvrir vidéo",
                "",
                "Vidéo fichiers (*.avi *.mp4 *.asf);;All files (*.*)");

    if (!filename.isEmpty()){
        if (!myPlayer->loadVideo(filename.toStdString()))
        {
            QMessageBox msgBox;
            msgBox.setText("The selected video could not be opened!");
            msgBox.exec();
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
