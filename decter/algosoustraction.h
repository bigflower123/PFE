#ifndef ALGOSOUSTRACTION_H
#define ALGOSOUSTRACTION_H

#include "algogeneral.h"

class AlgoSoustraction : public AlgoGeneral
{
public:
    AlgoSoustraction(int, Mat, Mat);
    void decter(Mat &);
    Mat generateBinaryImage(Mat);
    void calculeHistograme(Mat img);
private:
    int deplacementmax;     //Parameters of deplacementmax
    Mat start_frame;        //image of start frame
    Mat obj_choose;         //object choose
    Mat binary_fond;        //binary background image
    double thresh_red_1;    //The lower limit of red channel
    double thresh_red_2;    //The upper limit of red channel
    double thresh_green_1;  //The lower limit of green channel
    double thresh_green_2;  //The upper limit of green channel
    double thresh_blue_1;   //The lower limit of blue channel
    double thresh_blue_2;   //The upper limit of blue channel
    Mat element;
};

#endif // ALGOSOUSTRACTION_H
