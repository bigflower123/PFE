#ifndef INFORMATIONDIALOG_H
#define INFORMATIONDIALOG_H

#include <QDialog>
#include "player.h"

using namespace cv;
using namespace std;

namespace Ui {
class InformationDialog;
}

class InformationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InformationDialog(player *, QWidget *parent = 0);
    ~InformationDialog();
    void showHistogram(Mat &img);
    void displayHistogram(Mat &src);
private slots:
    //void on_showButton_clicked();

private:
    Ui::InformationDialog *ui;
    player *myPlayer;
    Mat img;
};

#endif // INFORMATIONDIALOG_H
