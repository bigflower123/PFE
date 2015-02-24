#include "save.h"

/**
 * Constructeur
 * initialisation les données
 * ouvrir VideoWriter
 * @brief Save::Save
 * @param tmpPath: Répertoire pour enregistrer les vidéos
 * @param tmpSize: Size de vidéo
 * @param tmpRate: Frame rate
 * @param tmpMyCodec: Codec
 */
Save::Save(string tmpPath, Size tmpSize, double tmpRate, int tmpMyCodec)
{
    videoPath = tmpPath;
    frameSize = tmpSize;
    frameRate = tmpRate;
    myCodec = tmpMyCodec;
    //Ouvrir outputVideo
    outputVideo.open(videoPath, myCodec,frameRate,frameSize,true);
    if(!outputVideo.isOpened()){
        printf("output video could not be opened");
    }
}

Save::~Save()
{

}

/**
 * Sauvegarder la vidéo
 * @brief Save::SaveVideo
 * @param currentframe: frame courant
 */
void Save::SaveVideo(Mat currentframe)
{
    resize(currentframe, currentframe,frameSize);
    outputVideo.write(currentframe);
}

void Save::SaveCoordinate(Point &)
{

}
