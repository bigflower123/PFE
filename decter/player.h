#ifndef PLAYER_H
#define PLAYER_H
#include <QMutex>
#include <QThread>
#include <QImage>
#include <QWaitCondition>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "save.h"
#include "algosoustraction.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QStringList>

using namespace cv;
class player: public QThread
{
    Q_OBJECT
 private:
    bool stop;
    QMutex mutex;
    QWaitCondition condition;
    Mat frame;
    Mat firstframe;
    int frameRate;
    VideoCapture *capture;
    Mat RGBframe;
    QImage img;
    Mat objectchoose;
    QString videoPath;
    QString infoPath;
    int deplacement;
    int framestart;
    int framefin;
    int nbframe;
    double framecount;
    AlgoSoustraction *myAlgo;
    Save mySaver;
    QString info;
    QFile infoFile;
    QTextStream  output;
    QFile readFile;
    QTextStream readStream;
    int flagcontinue = 0;
    int flagtimeschoose = 0;
    int flagSave = 0;
    bool saveFin = false;
    int lineNb = 0;
    QHash<int, Point2f> hash;
    int beginFrame = 0;
    QStringList strList;
    bool flagVisualier = false;
    bool flagTraiter = false;
   // long beginFrame = 1;
   // long finFrame = getNumberOfFrames();
    //Save *mySaver;

 signals:
     //Signal to output frame to be displayed
     void processedImage(const QImage &image, QString);

 protected:
     void run();
     void msleep(int ms);

 public:
    //Constructor
    player(QObject *parent = 0);
    //Destructor
    ~player();
    //Load a video from memory
    bool loadVideo(string filename);
    //Play the video
    void Play();
    //Stop the video
    void Stop();
    //check if the player has been stopped
    bool isStopped() const;

    //set video properties
    void setCurrentFrame( int frameNumber);

    //Get video properties
    double getFrameRate();
    double getCurrentFrame();
    double getNumberOfFrames();
    Size getFrameSize();
    int getCodec();
    int getFrameHeight();
    int getFrameWidth();

    //Show image
    Mat &showImage( int frameNumber );

    //Get current image
    Mat getcurrentImage( int frameNumber );

    void setObjectChoose(Mat &);
    Mat getObjectChoose();
    void setFileName(QString);
    void setFileInfoName(QString);
    void setDeplacementMax(int);
    void setVideoStart(int);
    void setVideoFin(int);
    vector<Mat> hist;
    void setFramenb(long);
    long getFramenb();
    Mat getNextframe();
    void setThresh(int, int ,int, int, int, int);
    int thresh[6];
    bool trajectoreChecked = false;
    Mat getFirstFrame();
    void prepareSaveInfo();
    void closeInfoFile();
    void setFlagTimes(int tmpTimes);
    void setFlagContinue(int tmpContinue);
    void setSaveFin(bool);
    QString getNextInfo();
    int getCountLine();
    QStringList getFileList(int);
    int getFirstValue();
    bool flagFileOpen = true;
    vector<Point2f> findList(int);
    void drawLine(Mat&, vector<Point2f>);
    QStringList getStrList();
    void setFlagVisualiser(bool);
    void setFlagTraiter(bool);
    /*void setStartVideo(long start);
    void setFinVideo(long fin);*/
};

#endif // PLAYER_H
