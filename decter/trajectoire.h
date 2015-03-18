#ifndef TRAJECTOIRE_H
#define TRAJECTOIRE_H

#include "node.h"

class Trajectoire
{
public:
    Trajectoire();
    void addPoint(Node &);
    vector<Node> &getCenterlist();
    void drawTrajectoire(Mat&);
    void setLastcenter(Node&);
private:
    vector<Node> center_list;
    Node center_back;  //The last value of the array 'center'
};

#endif // TRAJECTOIRE_H
