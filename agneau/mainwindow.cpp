#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionOuvrirVideo, SIGNAL(triggered()), this, SLOT(chooseVideo()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::chooseVideo(){
    //Open filedialog to choose video file
    QString filename = QFileDialog::getOpenFileName(
                this, "Ouvrir vidéo",
                "",
                "Vidéo fichiers (*.avi *.mp4 *.asf);;All files (*.*)");
}
