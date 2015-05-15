#ifndef DEPLACEMENTMAXDIALOG_H
#define DEPLACEMENTMAXDIALOG_H

#include <QDialog>
#include "player.h"

namespace Ui {
class DeplacementMaxDialog;
}

class DeplacementMaxDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeplacementMaxDialog(player *, QWidget *parent = 0);
    ~DeplacementMaxDialog();

private slots:
    void on_OkButton_clicked();

private:
    Ui::DeplacementMaxDialog *ui;
    player *myPlayer;
};

#endif // DEPLACEMENTMAXDIALOG_H
