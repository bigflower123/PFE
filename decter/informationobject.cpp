#include "informationobject.h"

InformationObject::InformationObject()
{
}

void InformationObject::setContours(vector<vector<Point>> tmpContours)
{
    contours = tmpContours;
}

void InformationObject::setCenter(Point2f tmpCenter)
{
    center = tmpCenter;
}

void InformationObject::setRadius(float tmpRadius)
{
    radius = tmpRadius;
}

vector<vector<Point> > InformationObject::getContours()
{
    return contours;
}

Point2f InformationObject::getCenter()
{
    return center;
}

float InformationObject::getRadius()
{
    return radius;
}
