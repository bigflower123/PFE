#include "mainwindow.h"
#include <QApplication>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
/**
 * Get the binary image
 * @brief AlgoSoustraction::generateBinaryImage
 * @param currentFtame
 * @return
 */
Mat generateBinaryImage(Mat& currentFtame)
{
    Mat binary;
    Mat mv_fond[3];
    split(currentFtame, mv_fond);
    double thresh_red_1 = 250;
    double thresh_red_2 = 255;
    double thresh_green_1 = 250;
    double thresh_green_2 = 255;
    double thresh_blue_1 = 250;
    double thresh_blue_2 = 255;
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

int main(int argc, char *argv[])
{
    /*QApplication a(argc, argv);
    //MainWindow w;
    MainWindow* w = new MainWindow();
    w->setAttribute(Qt::WA_DeleteOnClose, true);
    w->show();

    return a.exec();*/

    Mat binary_frame;   //the current frame on binary
    Mat binary_fond;
    Mat img_act;        //the binary image which contains only the moving object
    Mat clean_act;      //img_act do erosion = clean_act
    Point2f center;     //the center of the circle
    float radius;       //the radius of the circle
    Mat element;
    double max_domaine_cc=0; // the surface of the biggest contour
    int max_domaine_i=0; // the number of the contour which has the biggest surface
    Mat start_frame = imread("bg.jpg");
    Mat currentFrame = imread("fond.jpg");
    namedWindow("binary_fond");
    namedWindow("binary_frame");
    namedWindow("img_act");
    namedWindow("clean_act");
    Mat drawing = Mat::zeros( currentFrame.size(), CV_8UC3 );
    //calculeHistograme();
    binary_fond = generateBinaryImage(start_frame);
    binary_frame = generateBinaryImage(currentFrame);
    imshow("binary_fond",binary_fond);
    imshow("binary_frame",binary_frame);
    /******foreground OU background – background =
     * the binary image which contains only the moving object*************/
    absdiff(binary_frame+binary_fond,binary_fond,img_act);
    imshow("img_act",img_act);
    /*********************************************************************/
    /********Erosion********************************/
    morphologyEx(img_act,clean_act,MORPH_OPEN,element);
    imshow("clean_act",clean_act);
    /*************************************************/
    /**************************findContours***********************************/
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours( clean_act, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );
    Mat dst= Mat::zeros(clean_act.size(), CV_8UC3);
    for (int i = 0; i< contours.size(); i++)
    {
        //随机颜色
        Scalar color = Scalar(0,0,255 );
        drawContours(dst, contours, i, color, 2, 8, hierarchy, 0, Point());
    }
    // Create Window
    char* source_window = "countors";
    namedWindow(source_window, CV_WINDOW_NORMAL);
    imshow(source_window, dst);
    //myObject.setContours(contours);
    /****************************************************************************************/
    /***************Determine whether the object moves out of range of video****************/
    if(contours.size() == 0){
       /* if(!myTrajectoire.getCenterlist().empty()){
            myTrajectoire.setLastcenter(myTrajectoire.getCenterlist().back());
        }
        myTrajectoire.getCenterlist().clear();*/
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
        Mat obj_courant;
        obj_courant = currentFrame(Rect((int)(center.x-radius*2/3),(int)(center.y-radius*2/3),
                                     (int)radius*4/3,(int)radius*4/3));
        circle( currentFrame, center, (int)radius, color, 2, 8, 0 );//draw circle
        circle( currentFrame, center, 2, color, -1, 8, 0 );//draw the center of circle
        namedWindow("traite");
        imshow("traite",currentFrame);
        /*if(!myTrajectoire.getCenterlist().empty()){
            double x = myTrajectoire.getCenterlist().back().getCenter().x;
            double y = myTrajectoire.getCenterlist().back().getCenter().y;
            if(sqrt((x-center.x)*(x-center.x) + (y-center.y)*(y-center.y))<deplacementmax){
                Node nodecenter(center, QDateTime::currentDateTime(), nbFrame);
                myTrajectoire.addPoint(nodecenter);

                obj_courant = currentFrame(Rect((int)(center.x-radius*2/3),(int)(center.y-radius*2/3),
                                             (int)radius*4/3,(int)radius*4/3));
                circle( currentFrame, center, (int)radius, color, 2, 8, 0 );//draw circle
                circle( currentFrame, center, 2, color, -1, 8, 0 );//draw the center of circle
            }
        }
        (*obj_choose) = obj_courant;*/
    }
    waitKey(0);
     return 0;
}

