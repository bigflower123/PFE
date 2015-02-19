#include "save.h"

Save::Save(string tmpPath, Size tmpSize, double tmpRate)
{
    videoPath = tmpPath;
    frameSize = tmpSize;
    frameRate = tmpRate;
}

void Save::SaveVideo(Mat currentframe)
{
    outputVideo.open(videoPath, CV_FOURCC('M','P','4','2'), frameRate,frameSize,true);
    if(outputVideo.isOpened())
        outputVideo << currentframe;
}

void Save::SaveCoordinate(Point &)
{

}
