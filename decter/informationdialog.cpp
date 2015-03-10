#include "informationdialog.h"
#include "ui_informationdialog.h"

InformationDialog::InformationDialog(player * tmpPlayer, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InformationDialog)
{
    myPlayer = tmpPlayer;
    /*img = myPlayer->getObjectChoose();
    QImage qimg = QImage((const unsigned char*)(img.data),
                  img.cols,img.rows,QImage::Format_RGB888);
    ui->bluehistLabel->setAlignment(Qt::AlignCenter);
    ui->bluehistLabel->setPixmap(QPixmap::fromImage(qimg).scaled(ui->bluehistLabel->size(),
                            Qt::KeepAspectRatio, Qt::FastTransformation));*/
    ui->setupUi(this);
}

InformationDialog::~InformationDialog()
{
    delete ui;
}

/*InformationDialog::showHistogram()
{

}*/
