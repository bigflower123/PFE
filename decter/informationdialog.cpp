#include "informationdialog.h"
#include "ui_informationdialog.h"

InformationDialog::InformationDialog(player * tmpPlayer, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InformationDialog)
{
    ui->setupUi(this);
    myPlayer = tmpPlayer;
    Mat tmp;
    img = myPlayer->getObjectChoose();
    /*img.copyTo(tmp);
    QImage qimg = QImage((const unsigned char*)(tmp.data),
                  tmp.cols,tmp.rows,QImage::Format_RGB888);
    ui->bluehistLabel->setAlignment(Qt::AlignCenter);
    ui->bluehistLabel->setPixmap(QPixmap::fromImage(qimg).scaled(ui->bluehistLabel->size(),
                            Qt::KeepAspectRatio, Qt::FastTransformation));*/
    showHistogram(img);
}

InformationDialog::~InformationDialog()
{
    delete ui;
}

void InformationDialog::showHistogram(Mat &img)
{
    int bins = 256;             // number of bins
    int nc = img.channels();    // number of channels
    vector<Mat> hist(nc);       // array for storing the histograms
    vector<Mat> canvas(nc);     // images for displaying the histogram
    int hmax[3] = {0,0,0};      // peak value for each histogram
    for (int i = 0; i < hist.size(); i++)
        hist[i] = Mat::zeros(1, bins, CV_32SC1);

    for (int i = 0; i < img.rows; i++)
    {
        for (int j = 0; j < img.cols; j++)
        {
            for (int k = 0; k < nc; k++)
            {
                uchar val = nc == 1 ? img.at<uchar>(i,j) : img.at<Vec3b>(i,j)[k];
                hist[k].at<int>(val) += 1;
            }
        }
    }


    for (int i = 0; i < nc; i++)
    {
        for (int j = 0; j < bins-1; j++)
            hmax[i] = hist[i].at<int>(j) > hmax[i] ? hist[i].at<int>(j) : hmax[i];
    }
    //const char* wname[3] = { "blue", "green", "red" };
    Scalar colors[3] = { Scalar(255,0,0), Scalar(0,255,0), Scalar(0,0,255) };

    for (int i = 0; i < nc; i++)
    {
        canvas[i] = Mat::ones(125, bins, CV_8UC3);
        for (int j = 0, rows = canvas[i].rows; j < bins-1; j++)
        {
            line(
                canvas[i],
                Point(j, rows),
                Point(j, rows - (hist[i].at<int>(j) * rows/hmax[i])),
                nc == 1 ? Scalar(200,200,200) : colors[i],
                1, 8, 0
            );
        }

     //imshow(nc == 1 ? "value" : wname[i], canvas[i]);
    }
    QImage qimgRed = QImage((const unsigned char*)(canvas[0].data),
                  canvas[0].cols,canvas[0].rows,QImage::Format_RGB888);
    QImage qimgGreen = QImage((const unsigned char*)(canvas[1].data),
                  canvas[1].cols,canvas[1].rows,QImage::Format_RGB888);
    QImage qimgBlue = QImage((const unsigned char*)(canvas[2].data),
                  canvas[2].cols,canvas[2].rows,QImage::Format_RGB888);
    ui->bluehistLabel->setPixmap(QPixmap::fromImage(qimgBlue));
    ui->greenhistLabel->setPixmap(QPixmap::fromImage(qimgGreen));
    ui->redhistLabel->setPixmap(QPixmap::fromImage(qimgRed));
}

/*void InformationDialog::on_showButton_clicked()
{
    Mat tmp;
    img = myPlayer->getObjectChoose();
    img.copyTo(tmp);
    QImage qimg = QImage((const unsigned char*)(tmp.data),
                  tmp.cols,tmp.rows,QImage::Format_RGB888);
    ui->bluehistLabel->setAlignment(Qt::AlignCenter);
    ui->bluehistLabel->setPixmap(QPixmap::fromImage(qimg).scaled(ui->bluehistLabel->size(),
                            Qt::KeepAspectRatio, Qt::FastTransformation));
}*/
