#ifndef FICHIERCONTROL_H
#define FICHIERCONTROL_H
#include <opencv2\opencv.hpp>
#include <QString>
#include <QGraphicsView>
#include <QImage>
#include <QTimer>

using namespace cv;
using namespace std;

class fichierControl
{
public:
    fichierControl();
    void openVideo(QString &, QGraphicsView *videoGraphicsview);
private slots:
    void DisplayVideo(QGraphicsView *videoGraphicsview);
private:
    Mat frame;
};

#endif // FICHIERCONTROL_H
