#ifndef ALGOGENERAL_H
#define ALGOGENERAL_H

#include "informationobject.h"
#include "trajectoire.h"

class AlgoGeneral
{
public:
    AlgoGeneral();
    virtual void decter(Mat &);

private:
    InformationObject *myObject;
    Trajectoire *myTrajectoire;
};

#endif // ALGOGENERAL_H
