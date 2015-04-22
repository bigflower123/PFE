#include "deplacementmaxdialog.h"
#include "ui_deplacementmaxdialog.h"
#include <QMessageBox>

DeplacementMaxDialog::DeplacementMaxDialog(player *tmpPlayer , QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeplacementMaxDialog)
{
    myPlayer = tmpPlayer;
    ui->setupUi(this);
}



DeplacementMaxDialog::~DeplacementMaxDialog()
{
    delete ui;
}



void DeplacementMaxDialog::on_OkButton_clicked()
{
    int deplacement = ui->deplacementlineEdit->text().toInt();
    if(ui->deplacementlineEdit->text() != ""){
        myPlayer->setDeplacementMax(deplacement);
        //QMessageBox::StandardButton reply;
        //reply = QMessageBox::information(this, tr("Confirme"), "déplacement ok");
        this->close();
    }else{
        ui->msgLabel->setText("Il faut saisir déplacement");
    }
}
