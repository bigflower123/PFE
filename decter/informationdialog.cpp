#include "informationdialog.h"
#include "ui_informationdialog.h"

InformationDialog::InformationDialog(player * tmpPlayer, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InformationDialog)
{
    ui->setupUi(this);
    myPlayer = tmpPlayer;
    // Get the image of object choose
    img = myPlayer->getObjectChoose();
    // Produice histograms
    displayHistogram(img);
}

InformationDialog::~InformationDialog()
{
    delete ui;
}

/**
 * Produice histograms
 * @brief InformationDialog::displayHistogram
 * @param src
 */
void InformationDialog::displayHistogram(Mat &src)
{
    int thresh_red_1 = 0;
    int thresh_blue_1 = 0;
    int thresh_green_1 = 0;
    int thresh_red_2 = 255;
    int thresh_blue_2 = 255;
    int thresh_green_2 = 255;
    /// Separate the image in 3 places ( B, G and R )
     vector<Mat> bgr_planes;
     split( src, bgr_planes );

     /// Establish the number of bins
     int histSize = 256;

     /// Set the ranges ( for B,G,R) )
     float range[] = { 0, 256 } ;
     const float* histRange = { range };

     bool uniform = true; bool accumulate = false;

     Mat b_hist, g_hist, r_hist;

     /// Compute the histograms:
     calcHist( &bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate );
     calcHist( &bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate );
     calcHist( &bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate );

     /// Calcule max and min value
     // obtain the minimum value on the abscissa
     while(thresh_red_1 < 255 && r_hist.at<float>(thresh_red_1) < 5){
         thresh_red_1++;
     }

     while(thresh_green_1 < 255 && g_hist.at<float>(thresh_green_1) < 5){
         thresh_green_1++;
     }

     while(thresh_blue_1 < 255 && b_hist.at<float>(thresh_blue_1) < 5){
         thresh_blue_1++;
     }

     // obtain the maximum value on the abscissa
     while(thresh_red_2 >=0 && r_hist.at<float>(thresh_red_2) < 5){
         thresh_red_2--;
     }

     while(thresh_green_2 >=0 && g_hist.at<float>(thresh_green_2) < 5){
         thresh_green_2--;
     }

     while(thresh_blue_2 >= 0 && b_hist.at<float>(thresh_blue_2) < 5){
         thresh_blue_2--;
     }

     // Draw the histograms for B, G and R
     //int hist_w = 512; int hist_h = 400;
     int hist_w = 212; int hist_h = 150;
     int bin_w = cvRound( (double) hist_w/histSize );

     Mat histImageRed( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );
     Mat histImageGreen( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );
     Mat histImageBlue( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );

     /// Normalize the result to [ 0, histImage.rows ]
     normalize(b_hist, b_hist, 0, histImageBlue.rows, NORM_MINMAX, -1, Mat() );
     normalize(g_hist, g_hist, 0, histImageGreen.rows, NORM_MINMAX, -1, Mat() );
     normalize(r_hist, r_hist, 0, histImageRed.rows, NORM_MINMAX, -1, Mat() );

     /// Draw for each channel
     for( int i = 1; i < histSize; i++ )
     {
         line( histImageBlue, Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ) ,
                          Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ),
                          Scalar( 255, 0, 0), 2, 8, 0  );
         line( histImageGreen, Point( bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1)) ) ,
                          Point( bin_w*(i), hist_h - cvRound(g_hist.at<float>(i)) ),
                          Scalar( 0, 255, 0), 2, 8, 0  );
         line( histImageRed, Point( bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1)) ) ,
                          Point( bin_w*(i), hist_h - cvRound(r_hist.at<float>(i)) ),
                          Scalar( 0, 0, 255), 2, 8, 0  );
     }
     cv::cvtColor(histImageBlue,histImageBlue,CV_BGR2RGB);
     cv::cvtColor(histImageRed,histImageRed,CV_BGR2RGB);
     QImage qimgBlue = QImage((const unsigned char*)(histImageBlue.data),
                   histImageBlue.cols,histImageBlue.rows,QImage::Format_RGB888);
     QImage qimgGreen = QImage((const unsigned char*)(histImageGreen.data),
                   histImageGreen.cols,histImageGreen.rows,QImage::Format_RGB888);
     QImage qimgRed = QImage((const unsigned char*)(histImageRed.data),
                   histImageRed.cols,histImageRed.rows,QImage::Format_RGB888);
     ui->bluehistLabel->setPixmap(QPixmap::fromImage(qimgBlue));
     ui->greenhistLabel->setPixmap(QPixmap::fromImage(qimgGreen));
     ui->redhistLabel->setPixmap(QPixmap::fromImage(qimgRed));

     //show the min and max value of histogram on the abscissa
     ui->redminLabel->setText(QString::number(thresh_red_1));
     ui->redmaxLabel->setText(QString::number(thresh_red_2));
     ui->greenminLabel->setText(QString::number(thresh_green_1));
     ui->greenmaxLabel->setText(QString::number(thresh_green_2));
     ui->blueminLabel->setText(QString::number(thresh_blue_1));
     ui->bluemaxLabel->setText(QString::number(thresh_blue_2));

}

