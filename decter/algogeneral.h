#ifndef ALGOGENERAL_H
#define ALGOGENERAL_H

#include "informationobject.h"
#include "trajectoire.h"

class AlgoGeneral
{
public:
    AlgoGeneral();
    virtual void decter(Mat &);
    InformationObject& getInformationobject();
    Trajectoire& getTrajectoire();

protected:
    InformationObject myObject;
    Trajectoire myTrajectoire;
};

#endif // ALGOGENERAL_H
