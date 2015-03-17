#include "trajectoire.h"

Trajectoire::Trajectoire()
{
}

void Trajectoire::addPoint(Point2f tmpPoint)
{
    center_list.push_back(tmpPoint);
}

vector<Point2f> Trajectoire::getCenterlist()
{
    return center_list;
}

void Trajectoire::drawTrajectoire(Mat &frame)
{
    if(center_list.size()>1)
        {
            Scalar color( 0, 0, 255 );
            for(unsigned int i_tj = 1; i_tj<center_list.size() ; i_tj++)
            {
                line(frame,center_list[i_tj],center_list[i_tj-1],color,5);
            }
        }
}
