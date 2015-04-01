#ifndef NODE_H
#define NODE_H

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QDateTime>

using namespace cv;

class Node
{
public:
    Node();
    Node(Point2f, QDateTime, int);
    Point2f &getCenter();
    QString nodeToString();
private:
    Point2f center;
    QDateTime timenow;
    int currentFrame;

};

#endif // NODE_H
