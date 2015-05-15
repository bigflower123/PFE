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
    char bufferx[50], buffery[50];
    sprintf (bufferx, "%-.2f", center.x);
    sprintf (buffery, "%-.2f", center.y);
    return QString("%1;   %2;   %3;   %4").arg(currentFrame).arg(bufferx).arg(buffery).arg(timenow.toString());
}
