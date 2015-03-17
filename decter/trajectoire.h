#ifndef TRAJECTOIRE_H
#define TRAJECTOIRE_H

#include "node.h"

class Trajectoire
{
public:
    Trajectoire();
    void addPoint(Point2f);
    vector<Point2f> getCenterlist();
    void drawTrajectoire(Mat&);
    Point2f center_back;  //The last value of the array 'center'
private:
    vector<Point2f> center_list;
};

#endif // TRAJECTOIRE_H
