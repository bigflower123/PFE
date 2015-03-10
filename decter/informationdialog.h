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
    //showHistogram();

private:
    Ui::InformationDialog *ui;
    player *myPlayer;
    Mat img;
    int bins = 256;             // number of bins
    //int nc = img.channels();    // number of channels
    //vector<Mat> hist(nc);       // array for storing the histograms
    //vector<Mat> canvas(nc);     // images for displaying the histogram
    //int hmax[3] = {0,0,0};      // peak value for each histogram
};

#endif // INFORMATIONDIALOG_H
