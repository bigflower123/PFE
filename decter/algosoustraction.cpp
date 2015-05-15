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
    /*****Initialiser la limite inférieure
     *  et la limite supérieure****/
    thresh_red_1 = 0;
    thresh_red_2 = 255;
    thresh_blue_1 = 0;
    thresh_blue_2 = 255;
    thresh_green_1 = 0;
    thresh_green_2 = 255;
    /*************************************/
    //Calculer la limite inférieure et la limite supérieure
    calculeHistogram(*obj_choose);
    //Générer l'image binaire de la prémière image de la vidéo
    binary_fond = generateBinaryImage(start_frame);
    if(i == 0){
        pre_img = true;
    }else{
        pre_img = false;
    }
}


/**
 * La fonction principale de détection et suivie
 * @brief AlgoSoustraction::decter
 * @param currentFrame: Image courante de la vidéo
 * @param nbFrame: Numéro du frame courante
 */
void AlgoSoustraction::decter(Mat & currentFrame, int nbFrame)
{
    clock_t t_start,t_end, t_start1, t_end1;
    Mat binary_frame;   //the current frame on binary
    Mat img_act;        //the binary image which contains only the moving object
    Mat clean_act;      //img_act do erosion = clean_act
    Point2f center;     //the center of the circle
    float radius;       //the radius of the circle
    Mat obj_courant;    //current object
    Mat drawing = Mat::zeros( currentFrame.size(), CV_8UC3 );
    t_start = clock();
    binary_frame = generateBinaryImage(currentFrame);   //Générer l'image binaire du frame courant
    t_end = clock();
    qDebug()<< "Binary img" <<(double)(t_end - t_start) / CLOCKS_PER_SEC;

    t_start1 = clock();
    /******foreground OU background – background =
     * the binary image which contains only the moving object*************/
    absdiff(binary_frame+binary_fond,binary_fond,img_act);
    /*********************************************************************/
    /********Erosion********************************/
    morphologyEx(img_act,clean_act,MORPH_OPEN,element);
    /*************************************************/
    /**************************findContours***********************************/
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours( clean_act, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );
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
                //this->calculeHistogram(obj_courant);
                *obj_choose = obj_courant;
            }else{
                //Clear trajectoire
                myTrajectoire.getCenterlist().clear();
            }
        }else{
            //If it is the first image
            if(pre_img){
                pre_img = false;
                Node nodecenter(center, QDateTime::currentDateTime(), nbFrame);
                myTrajectoire.addPoint(nodecenter);
                circle( currentFrame, center, (int)radius, color, 2, 8, 0 );//draw circle
                circle( currentFrame, center, 2, color, -1, 8, 0 );//draw the center of circle
            //If it moves too fast in the last image
            }else if(sqrt((myTrajectoire.getLastcenter().getCenter().x-center.x)*(myTrajectoire.getLastcenter().getCenter().x-center.x)
                     + (myTrajectoire.getLastcenter().getCenter().y-center.y)*(myTrajectoire.getLastcenter().getCenter().y-center.y))<deplacementmax*3/2)
            {
                Node nodecenter(center, QDateTime::currentDateTime(), nbFrame);
                myTrajectoire.addPoint(nodecenter);
                circle( currentFrame, center, (int)radius, color, 2, 8, 0 );
                circle( currentFrame, center, 2, color, -1, 8, 0 );
            //If it display again in the screen
            }else{
                if(count_refond<=2)
                {
                    binary_fond = generateBinaryImage(currentFrame);
                    count_refond++;
                }
                else
                {
                    count_refond=0;
                    if(center.x > 0 && center.y > 0){
                        Node nodecenter(center, QDateTime::currentDateTime(), nbFrame);
                        myTrajectoire.addPoint(nodecenter);
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
 * @param tmp
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
 * Histogram
 * @brief AlgoSoustraction::calculeHistogram
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

      // calcule six values
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

}


