#include "algosoustraction.h"
#include <QImage>
#include <QDebug>
#include <time.h>
#include <conio.h>

AlgoSoustraction::AlgoSoustraction(int tmpdpmax, Mat& tmpstart, Mat* tmpobj, int i)
{
    deplacementmax = tmpdpmax;
    start_frame = tmpstart;
    obj_choose = tmpobj;
    thresh_red_1 = 0;
    thresh_red_2 = 255;
    thresh_blue_1 = 0;
    thresh_blue_2 = 255;
    thresh_green_1 = 0;
    thresh_green_2 = 255;
    calculeHistogram(*obj_choose);
    Mat tmp = *obj_choose;
    //imwrite("objchoose.jpg", tmp);
    //imwrite("startframe.jpg", start_frame);
    binary_fond = generateBinaryImage(start_frame);
    //imwrite("fond.jpg", binary_fond);
    if(i == 0){
        pre_img = true;
    }else{
        pre_img = false;
    }
}


/**
 * Main algo of detecter
 * @brief AlgoSoustraction::decter
 * @param currentFrame
 */
void AlgoSoustraction::decter(Mat & currentFrame, int nbFrame)
{
    clock_t t_start,t_end, t_start1, t_end1;
    Mat binary_frame;   //the current frame on binary
    Mat img_act;        //the binary image which contains only the moving object
    Mat clean_act;      //img_act do erosion = clean_act
    Point2f center;     //the center of the circle
    float radius;       //the radius of the circle
    Mat obj_courant;
    Mat drawing = Mat::zeros( currentFrame.size(), CV_8UC3 );
    t_start = clock();
    //imwrite("currentframe.jpg",currentFrame);
    binary_frame = generateBinaryImage(currentFrame);
    t_end = clock();
    qDebug()<< "Binary img" <<(double)(t_end - t_start) / CLOCKS_PER_SEC;
    //imwrite("binaryframe.jpg",binary_frame);
    t_start1 = clock();
    /******foreground OU background – background =
     * the binary image which contains only the moving object*************/
    //imwrite("add.jpg",binary_frame+binary_fond);
    absdiff(binary_frame+binary_fond,binary_fond,img_act);
    //imwrite("img_act.jpg",img_act);
    /*********************************************************************/
    /********Erosion********************************/
    morphologyEx(img_act,clean_act,MORPH_OPEN,element);
    //imwrite("clean_act.jpg",clean_act);
    /*************************************************/
    /**************************findContours***********************************/
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours( clean_act, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );
    /*Mat dst= Mat::zeros(clean_act.size(), CV_8UC3);
   for (int i = 0; i< contours.size(); i++)
   {
       Scalar color = Scalar(0,0,255 );
       drawContours(dst, contours, i, color, 2, 8, hierarchy, 0, Point());
   }
   imwrite("contours.jpg", dst);*/
    myObject.setContours(contours);
    t_end1 = clock();
    qDebug()<< "Traite img" <<(double)(t_end1 - t_start1) / CLOCKS_PER_SEC;
    /****************************************************************************************/
    /***************Determine whether the object moves out of range of video****************/
    if(contours.size() == 0){
        if(!myTrajectoire.getCenterlist().empty()){
            myTrajectoire.setLastcenter(myTrajectoire.getCenterlist().back());
        }
        myTrajectoire.getCenterlist().clear();
    /***********************************************************************************/
    }else if(contours.size() >= 1){
        for( unsigned int i = 0; i < contours.size(); i++ )//find the biggest Connected domain
        {
            if(contourArea(contours[i])>max_domaine_cc)
            {
                max_domaine_cc = contourArea(contours[i]);
                max_domaine_i = i;
            }
        }
        Scalar color( rand()&255, rand()&255, rand()&255 );//define a color
        //computes the minimal enclosing circle for the biggest Connected domain
        minEnclosingCircle( (Mat)contours[max_domaine_i], center, radius);
        max_domaine_cc = 0;
        max_domaine_i = 0;
        //Mat obj_courant;
        if(!myTrajectoire.getCenterlist().empty()){
             double x = myTrajectoire.getCenterlist().back().getCenter().x;
             double y = myTrajectoire.getCenterlist().back().getCenter().y;
            if(sqrt((x-center.x)*(x-center.x) + (y-center.y)*(y-center.y))<deplacementmax){
                Node nodecenter(center, QDateTime::currentDateTime(), nbFrame);
                myTrajectoire.addPoint(nodecenter);
                double obj_x = center.x - radius*2/3;
                double obj_y = center.y - radius*2/3;
                if(obj_x < 0 ) obj_x = 0;
                if(obj_y < 0) obj_y = 0;
                obj_courant = currentFrame(Rect((int)(obj_x),(int)(obj_y),
                                             (int)radius*4/3,(int)radius*4/3));
                //this->testHistogram(obj_courant);
                //circle( currentFrame, center, (int)radius, color, 2, 8, 0 );//draw circle
                //circle( currentFrame, center, 2, color, -1, 8, 0 );//draw the center of circle
            }else{
                //Clear trajectoire
                myTrajectoire.getCenterlist().clear();
            }
        }else{
            if(pre_img){
                pre_img = false;
                Node nodecenter(center, QDateTime::currentDateTime(), nbFrame);
                myTrajectoire.addPoint(nodecenter);
                circle( currentFrame, center, (int)radius, color, 2, 8, 0 );//draw circle
                circle( currentFrame, center, 2, color, -1, 8, 0 );//draw the center of circle
            }else if(sqrt((myTrajectoire.getLastcenter().getCenter().x-center.x)*(myTrajectoire.getLastcenter().getCenter().x-center.x)
                     + (myTrajectoire.getLastcenter().getCenter().y-center.y)*(myTrajectoire.getLastcenter().getCenter().y-center.y))<deplacementmax*3/2)
            {
                Node nodecenter(center, QDateTime::currentDateTime(), nbFrame);
                myTrajectoire.addPoint(nodecenter);
                circle( currentFrame, center, (int)radius, color, 2, 8, 0 );
                circle( currentFrame, center, 2, color, -1, 8, 0 );
            }else{
                if(count_refond<=2)
                {
                    binary_fond = generateBinaryImage(currentFrame);
                    count_refond++;
                    //qDebug()<<"count_refond"<<count_refond;
                }
                else
                {
                    count_refond=0;
                    if(center.x > 0 && center.y > 0){
                        Node nodecenter(center, QDateTime::currentDateTime(), nbFrame);
                        myTrajectoire.addPoint(nodecenter);
                        //qDebug()<<center.x<<center.y;
                        circle( currentFrame, center, (int)radius, color, 2, 8, 0 );
                        circle( currentFrame, center, 2, color, -1, 8, 0 );
                    }
                }
            }

        }
    }
}



/**
 * Get the binary image
 * @brief AlgoSoustraction::generateBinaryImage
 * @param currentFtame
 * @return
 */
Mat AlgoSoustraction::generateBinaryImage(Mat& tmp)
{
    Mat binary;
    Mat mv_fond[3];
    split(tmp, mv_fond);

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

/**
 * calcule histograme of three channels
 * @brief AlgoSoustraction::calculeHistograme
 * @param img
 */
void AlgoSoustraction::calcule1Histograme(Mat& img)
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

    thresh_red_1 = binsmin[2];
    thresh_red_2 = binsmax[2];
    thresh_green_1 = binsmin[1];
    thresh_green_2 = binsmax[1];
    thresh_blue_1 = binsmin[0];
    thresh_blue_2 = binsmax[0];
}


/**
 * Histogram
 * @brief AlgoSoustraction::testHistogram
 * @param src
 */
void AlgoSoustraction::calculeHistogram(Mat & src)
{

     /// Separate the image in 3 places ( B, G and R )
      vector<Mat> bgr_planes;
      double maxRedVal = 0, maxGreenVal = 0, maxBlueVal = 0;
      double RedVal = 0, GreenVal = 0, BlueVal = 0;
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
      // obtain the maximum (peak) value for each channel
      for (int j = 0; j < 256; j++){
          if(b_hist.at<float>(j) > maxBlueVal ){
              maxBlueVal = b_hist.at<float>(j);
              BlueVal = j;
          }
          if(g_hist.at<float>(j) > maxGreenVal ){
              maxGreenVal = g_hist.at<float>(j);
              GreenVal = j;
          }
          if(r_hist.at<float>(j) > maxRedVal ){
              maxRedVal = r_hist.at<float>(j);
              RedVal = j;
          }
      }
      /*minMaxLoc(b_hist, &minBlueVal, &maxBlueVal, 0, 0);
      minMaxLoc(g_hist, &minGreenVal, &maxGreenVal, 0, 0);
      minMaxLoc(r_hist, &minRedVal, &maxRedVal, 0, 0);*/
      // obtain the minimum value on the abscissa
      while(thresh_red_1 < 256 && r_hist.at<float>(thresh_red_1) <= 5){
          thresh_red_1++;
      }

      while(thresh_green_1 < 256 && g_hist.at<float>(thresh_green_1) <= 5){
          thresh_green_1++;
      }

      while(thresh_blue_1 < 256 && b_hist.at<float>(thresh_blue_1) <= 5){
          thresh_blue_1++;
      }

      // obtain the maximum value on the abscissa
      while(thresh_red_2 >= 0 && r_hist.at<float>(thresh_red_2) <= 5){
          thresh_red_2--;
      }

      while(thresh_green_2 >= 0 && g_hist.at<float>(thresh_green_2) <= 5){
          thresh_green_2--;
      }

      while(thresh_blue_2 >= 0 && b_hist.at<float>(thresh_blue_2) <= 5){
          thresh_blue_2--;
      }

      thresh_red_1=(int)(thresh_red_1-15);
      thresh_red_2=(int)(thresh_red_2+15);
      if((thresh_red_2-RedVal)>3*(RedVal-thresh_red_1)) thresh_red_2=RedVal+3*(RedVal-thresh_red_1);
      if((RedVal-thresh_red_1)>3*(thresh_red_2-RedVal)) thresh_red_1=RedVal-3*(thresh_red_2-RedVal);
      if(thresh_red_1<=0)thresh_red_1=1;
      if(thresh_red_2>=256)thresh_red_2=255;

      thresh_green_1=(int)(thresh_green_1-15);
      thresh_green_2=(int)(thresh_green_2+15);
      if((thresh_green_2-GreenVal)>3*(GreenVal-thresh_green_1)) thresh_green_2=GreenVal+3*(GreenVal-thresh_green_1);
      if((GreenVal-thresh_green_1)>3*(thresh_green_2-GreenVal)) thresh_green_1=GreenVal-3*(thresh_green_2-GreenVal);
      if(thresh_green_1<=0)thresh_green_1=1;
      if(thresh_green_2>=256)thresh_green_2=255;

      thresh_blue_1=(int)(thresh_blue_1-15);
      thresh_blue_2=(int)(thresh_blue_2+15);
      if((thresh_blue_2-BlueVal)>3*(BlueVal-thresh_blue_1)) thresh_blue_2=BlueVal+3*(BlueVal-thresh_blue_1);
      if((BlueVal-thresh_blue_1)>3*(thresh_blue_2-BlueVal)) thresh_blue_1=BlueVal-3*(thresh_blue_2-BlueVal);
      if(thresh_blue_1<=0)thresh_blue_1=1;
      if(thresh_blue_2>=256)thresh_blue_2=255;


      // Draw the histograms for B, G and R
     /* int hist_w = 512; int hist_h = 400;
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

      /// Display
      imwrite("calcHistRed.jpg", histImageRed );
      imwrite("calcHistGreen.jpg", histImageGreen );
      imwrite("calcHistBlue.jpg", histImageBlue );*/
}


