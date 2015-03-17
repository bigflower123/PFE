#ifndef INFORMATIONOBJECT_H
#define INFORMATIONOBJECT_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
class InformationObject
{
public:
    InformationObject();
    void setContours(vector<vector<Point>>);
    void setCenter(Point2f);
    void setRadius(float);
    vector<vector<Point>> getContours();
    Point2f getCenter();
    float getRadius();

private:
    vector<vector<Point>> contours;
    Point2f center;
    float radius;
};

#endif // INFORMATIONOBJECT_H
