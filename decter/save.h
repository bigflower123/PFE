#ifndef SAVE_H
#define SAVE_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QString>

using namespace cv;

class Save
{
public:
    Save(string fileName, Size ImgSize, double Rate, int MyCodec);
    ~Save();
    void SaveVideo(Mat);  //Save video
    void SaveCoordinate(Point &); //Save nombre frame, coordinate(x,y) et le temps courant
private:
    VideoWriter outputVideo;
    Size frameSize;
    double frameRate;
    string videoPath;  //Répertoire pour enregistrer les vidéos
    string coordinatePath;   //Répertoire pour enregistrer les données des coordonnées
    string commentPath;    //Répertoire pour enregistrer les commentaires
    int myCodec;    //Codec de video
};

#endif // SAVE_H
