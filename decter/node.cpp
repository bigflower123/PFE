#include "node.h"

Node::Node()
{
    currentFrame = -1;
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

QString Node::nodeToString()
{
    return QString("%1;   %2;   %3;   %4").arg(currentFrame).arg(center.x).arg(center.y).arg(timenow.toString());
}
