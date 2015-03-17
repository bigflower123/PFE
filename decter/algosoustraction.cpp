#include "algosoustraction.h"
#include <QImage>

AlgoSoustraction::AlgoSoustraction(int tmpdpmax, Mat tmpstart, Mat tmpobj)
{
    deplacementmax = tmpdpmax;
    start_frame = tmpstart;
    obj_choose = tmpobj;
}

void AlgoSoustraction::decter(Mat & currentFrame)
{
    Mat binary_frame;   //the current frame on binary
    Mat img_act;        //the binary image which contains only the moving object
    Mat clean_act;      //img_act do erosion = clean_act
    calculeHistograme(obj_choose);
    binary_fond = generateBinaryImage(start_frame);
    binary_frame = generateBinaryImage(currentFrame);

    /******foreground OU background – background =
     * the binary image which contains only the moving object*************/
    absdiff(binary_frame+binary_fond,binary_fond,img_act);
    /*********************************************************************/

    /********Erosion********************************/
    morphologyEx(img_act,clean_act,MORPH_OPEN,element);
    /*************************************************/

    /**************************findContours***********************************/
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    findContours( clean_act, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );
    /****************************************************************************************/

}

Mat AlgoSoustraction::generateBinaryImage(Mat currentFtame)
{
    Mat binary;
    Mat mv_fond[3];
    split(currentFtame, mv_fond);

    Mat binary_red_1;
    threshold(mv_fond[2], binary_red_1, thresh_red_1, 255, THRESH_BINARY_INV);
    Mat binary_red_2;
    threshold(mv_fond[2], binary_red_2, thresh_red_2, 255, THRESH_BINARY);
    Mat binary_red = binary_red_1 + binary_red_2;

    Mat binary_green_1;
    threshold(mv_fond[1], binary_green_1, thresh_green_1, 255, THRESH_BINARY_INV);
    Mat binary_green_2;
    threshold(mv_fond[1], binary_green_2, thresh_green_2, 255, THRESH_BINARY);
    Mat binary_green = binary_green_1 + binary_green_2;

    Mat binary_blue_1;
    threshold(mv_fond[0], binary_blue_1, thresh_blue_1, 255, THRESH_BINARY_INV);
    Mat binary_blue_2;
    threshold(mv_fond[0], binary_blue_2, thresh_blue_2, 255, THRESH_BINARY);
    Mat binary_blue = binary_blue_1 + binary_blue_2;

    threshold(binary_blue+binary_green+binary_red, binary, 254, 255, THRESH_BINARY_INV);
    return binary;
}

void AlgoSoustraction::calculeHistograme(Mat img)
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
    }else{
        QImage qimgRed = QImage((const unsigned char*)(canvas[0].data),
                      canvas[0].cols,canvas[0].rows,QImage::Format_RGB888);
        QImage qimgGreen = QImage((const unsigned char*)(canvas[1].data),
                      canvas[1].cols,canvas[1].rows,QImage::Format_RGB888);
        QImage qimgBlue = QImage((const unsigned char*)(canvas[2].data),
                      canvas[2].cols,canvas[2].rows,QImage::Format_RGB888);
    }
    thresh_red_1 = binsmin[0];
    thresh_red_2 = binsmax[0];
    thresh_green_1 = binsmin[1];
    thresh_green_2 = binsmax[1];
    thresh_blue_1 = binsmin[2];
    thresh_blue_2 = binsmax[2];
}

