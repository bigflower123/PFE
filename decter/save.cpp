#include "save.h"

Save::Save(string tmpPath, Size tmpSize, double tmpRate, int tmpMyCodec)
{
    videoPath = tmpPath;
    frameSize = tmpSize;
    frameRate = tmpRate;
    myCodec = tmpMyCodec;
    outputVideo.open(videoPath, myCodec,frameRate,frameSize,true);
    if(!outputVideo.isOpened()){
        printf("output video could not be opened");
    }
}

Save::~Save()
{

}

void Save::SaveVideo(Mat currentframe)
{
    resize(currentframe, currentframe,frameSize);
    outputVideo.write(currentframe);
}

void Save::SaveCoordinate(Point &)
{

}
