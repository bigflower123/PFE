#include "informationdialog.h"
#include "ui_informationdialog.h"

InformationDialog::InformationDialog(player * tmpPlayer, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InformationDialog)
{
    ui->setupUi(this);
    myPlayer = tmpPlayer;
    img = myPlayer->getObjectChoose();
    displayHistogram(img);
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
    imwrite("showhis.jpg",img);
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
    Scalar colors[3] = { Scalar(0,0,255), Scalar(0,255,0), Scalar(255,0,0) };
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
        QImage qimgBlue = QImage((const unsigned char*)(canvas[0].data),
                      canvas[0].cols,canvas[0].rows,QImage::Format_RGB888);
        QImage qimgGreen = QImage((const unsigned char*)(canvas[1].data),
                      canvas[1].cols,canvas[1].rows,QImage::Format_RGB888);
        QImage qimgRed = QImage((const unsigned char*)(canvas[2].data),
                      canvas[2].cols,canvas[2].rows,QImage::Format_RGB888);
        ui->bluehistLabel->setPixmap(QPixmap::fromImage(qimgBlue));
        ui->greenhistLabel->setPixmap(QPixmap::fromImage(qimgGreen));
        ui->redhistLabel->setPixmap(QPixmap::fromImage(qimgRed));

        //show the min and max value of histogram on the abscissa
        ui->redminLabel->setText(QString::number(binsmin[2]));
        ui->redmaxLabel->setText(QString::number(binsmax[2]));
        ui->greenminLabel->setText(QString::number(binsmin[1]));
        ui->greenmaxLabel->setText(QString::number(binsmax[1]));
        ui->blueminLabel->setText(QString::number(binsmin[0]));
        ui->bluemaxLabel->setText(QString::number(binsmax[0]));

        //myPlayer->setThresh(binsmin[0], binsmax[0], binsmin[2], binsmax[2], binsmin[1], binsmax[1]);
    }
}

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

     //imwrite("calcHistRed.jpg", histImageRed );
     //imwrite("calcHistGreen.jpg", histImageGreen );
     //imwrite("calcHistBlue.jpg", histImageBlue );
     //show the min and max value of histogram on the abscissa
     ui->redminLabel->setText(QString::number(thresh_red_1));
     ui->redmaxLabel->setText(QString::number(thresh_red_2));
     ui->greenminLabel->setText(QString::number(thresh_green_1));
     ui->greenmaxLabel->setText(QString::number(thresh_green_2));
     ui->blueminLabel->setText(QString::number(thresh_blue_1));
     ui->bluemaxLabel->setText(QString::number(thresh_blue_2));

}

/*void InformationDialog::displayHistogram()
{
    QImage qimgRed = QImage((const unsigned char*)(hist[0].data),
                  hist[0].cols,hist[0].rows,QImage::Format_RGB888);
    QImage qimgGreen = QImage((const unsigned char*)(hist[1].data),
                  hist[1].cols,hist[1].rows,QImage::Format_RGB888);
    QImage qimgBlue = QImage((const unsigned char*)(hist[2].data),
                  hist[2].cols,hist[2].rows,QImage::Format_RGB888);
    ui->greenhistLabel->setPixmap(QPixmap::fromImage(qimgGreen));
    ui->redhistLabel->setPixmap(QPixmap::fromImage(qimgRed));
    ui->bluehistLabel->setPixmap(QPixmap::fromImage(qimgBlue));
}*/

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
