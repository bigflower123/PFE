#ifndef ALGOSOUSTRACTION_H
#define ALGOSOUSTRACTION_H

#include "algogeneral.h"
#include "node.h"

class AlgoSoustraction : public AlgoGeneral
{
public:
    AlgoSoustraction(int, Mat &, Mat *, int i);
    void decter(Mat &, int);
    Mat generateBinaryImage(Mat &);
    void calculeHistogram(Mat &);
    double thresh_red_1;    //The lower limit of red channel
    double thresh_red_2;    //The upper limit of red channel
    double thresh_green_1;  //The lower limit of green channel
    double thresh_green_2;  //The upper limit of green channel
    double thresh_blue_1;   //The lower limit of blue channel
    double thresh_blue_2;   //The upper limit of blue channel

private:
    int deplacementmax;     //Parameters of deplacementmax
    Mat start_frame;        //image of start frame
    Mat *obj_choose;        //object choose
    Mat binary_fond;        //binary background image
    Mat element;
    Point2f center_back;    //The last value of the array 'center'
    bool pre_img;
    double max_domaine_cc=0; // the surface of the biggest contour
    int max_domaine_i=0;     // the number of the contour which has the biggest surface
    int count_refond=0;

};

#endif // ALGOSOUSTRACTION_H
