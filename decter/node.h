#ifndef NODE_H
#define NODE_H

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

class Node
{
public:
    Node(Point2f, int);

private:
    Point2f center;
    time_t timenow;
    int currentFrame;

};

#endif // NODE_H
