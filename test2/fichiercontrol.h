#ifndef FICHIERCONTROL_H
#define FICHIERCONTROL_H
#include <opencv2\opencv.hpp>
#include <QString>
#include <QGraphicsView>

using namespace cv;
using namespace std;

class fichierControl
{
public:
    fichierControl();
    void openVideo(QString &, QGraphicsView *videoGraphicsview);

};

#endif // FICHIERCONTROL_H
