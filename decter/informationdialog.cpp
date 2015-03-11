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
    img.copyTo(tmp);
    showHistogram(tmp);
}

InformationDialog::~InformationDialog()
{
    delete ui;
}

/**
 * calcule histogram of three channels and show
 * @brief InformationDialog::showHistogram
 * @param img
 */
void InformationDialog::showHistogram(Mat &img)
{
    int bins = 256;                 // number of bins
    int nc = img.channels();        // number of channels
    vector<Mat> hist(nc);           // array for storing the histograms
    vector<Mat> canvas(nc);         // images for displaying the histogram
    int hmax[3] = {0,0,0};          // peak value for each histogram
    int binsmin[3] = {0, 0 ,0};     //min value of bins for each histogram
    int binsmax[3] = {255, 255, 255};     //max value of bins for each histogram

    //Initialize the hist arrays
    for (int i = 0; i < hist.size(); i++)
        hist[i] = Mat::zeros(1, bins, CV_32SC1);

    //Calculate the number of pixels of each tonal value in each channel
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
        // obtain the maximum (peak) value for each channel
        // The max value is needed to normalize the display later
        for (int j = 0; j < bins-1; j++)
            hmax[i] = hist[i].at<int>(j) > hmax[i] ? hist[i].at<int>(j) : hmax[i];

        // obtain the minimum value on the abscissa
        while(hist[i].at<int>(binsmin[i]) == 0 &&  binsmin[i]<= 255){
            binsmin[i]++;
        }

        // obtain the maximum value on the abscissa
        while(hist[i].at<int>(binsmax[i]) == 0 && binsmax[i] >= 0){
            binsmax[i]--;
        }
    }

    // Initialize the canvas
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
    }
    // Display the histograms
    if(nc == 1){
        QImage qimgNB = QImage((const unsigned char*)(canvas[0].data),
                      canvas[0].cols,canvas[0].rows,QImage::Format_RGB888);
        ui->bluehistLabel->setPixmap(QPixmap::fromImage(qimgNB));
        ui->redminLabel->setText(QString::number(binsmin[0]));
        ui->redmaxLabel->setText(QString::number(binsmax[0]));
    }else{
        QImage qimgRed = QImage((const unsigned char*)(canvas[0].data),
                      canvas[0].cols,canvas[0].rows,QImage::Format_RGB888);
        QImage qimgGreen = QImage((const unsigned char*)(canvas[1].data),
                      canvas[1].cols,canvas[1].rows,QImage::Format_RGB888);
        QImage qimgBlue = QImage((const unsigned char*)(canvas[2].data),
                      canvas[2].cols,canvas[2].rows,QImage::Format_RGB888);
        ui->bluehistLabel->setPixmap(QPixmap::fromImage(qimgBlue));
        ui->greenhistLabel->setPixmap(QPixmap::fromImage(qimgGreen));
        ui->redhistLabel->setPixmap(QPixmap::fromImage(qimgRed));

        //show the min and max value of histogram on the abscissa
        ui->redminLabel->setText(QString::number(binsmin[0]));
        ui->redmaxLabel->setText(QString::number(binsmax[0]));
        ui->greenminLabel->setText(QString::number(binsmin[1]));
        ui->greenmaxLabel->setText(QString::number(binsmax[1]));
        ui->blueminLabel->setText(QString::number(binsmin[2]));
        ui->bluemaxLabel->setText(QString::number(binsmax[2]));
    }
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
