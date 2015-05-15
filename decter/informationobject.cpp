#include "informationobject.h"

InformationObject::InformationObject()
{
}

/**
 * set contours
 * @brief InformationObject::setContours
 * @param tmpContours
 */
void InformationObject::setContours(vector<vector<Point>> tmpContours)
{
    contours = tmpContours;
}

/**
 * set center
 * @brief InformationObject::setCenter
 * @param tmpCenter
 */
void InformationObject::setCenter(Point2f tmpCenter)
{
    center = tmpCenter;
}

/**
 * set radius
 * @brief InformationObject::setRadius
 * @param tmpRadius
 */
void InformationObject::setRadius(float tmpRadius)
{
    radius = tmpRadius;
}


/**
 * Get contour
 * @brief InformationObject::getContours
 * @return
 */
vector<vector<Point> > InformationObject::getContours()
{
    return contours;
}

/**
 * Get center of object
 * @brief InformationObject::getCenter
 * @return
 */
Point2f InformationObject::getCenter()
{
    return center;
}

/**
 * Get radius of object
 * @brief InformationObject::getRadius
 * @return
 */
float InformationObject::getRadius()
{
    return radius;
}
