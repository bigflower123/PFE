#ifndef FICHIERCONTROL_H
#define FICHIERCONTROL_H
#include <opencv2\opencv.hpp>
#include <QString>
#include <QGraphicsView>
#include <QImage>
#include <QTimer>
#include <QProgressBar>
using namespace cv;
using namespace std;

class fichierControl
{
public:
    fichierControl();
    void openVideo(QString &, QGraphicsView *videoGraphicsview, QProgressBar *);
    void pauseVideo(QGraphicsView *videoGraphicsview);

private slots:
    void DisplayVideo(QGraphicsView *videoGraphicsview);

private:
    Mat frame;
    bool isPause = false;
};

#endif // FICHIERCONTROL_H
