#include "node.h"

Node::Node()
{

}

Node::Node(Point2f tmpcenter, QDateTime tmptime, int tmpcurrentFrame)
{
    center = tmpcenter;
    timenow = tmptime;
    currentFrame = tmpcurrentFrame;
}

Point2f &Node::getCenter()
{
    return center;
}
