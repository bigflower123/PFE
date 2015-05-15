#include "trajectoire.h"

Trajectoire::Trajectoire()
{
}

void Trajectoire::addPoint(Node &tmpNode)
{
    center_list.push_back(tmpNode);
}

vector<Node>& Trajectoire::getCenterlist()
{
    return center_list;
}

/**
 * Draw trajectory
 * @brief Trajectoire::drawTrajectoire
 * @param frame
 */
void Trajectoire::drawTrajectoire(Mat &frame)
{
    Scalar color( 255, 0, 0 );
    if(center_list.size()>1)
    {
        for(unsigned int i = 1; i<center_list.size() ; i++)
        {
            line(frame, center_list[i].getCenter(), center_list[i-1].getCenter(),color,3);
        }
     }
}

void Trajectoire::setLastcenter(Node &tmpNode)
{
    center_back = tmpNode;
}

Node Trajectoire::getLastcenter()
{
    return center_back;
}


