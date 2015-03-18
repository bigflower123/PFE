#include "player.h"

player::player(QObject *parent)
 : QThread(parent)
{
    stop = true;
}

void player::msleep(int ms){
    /*struct timespec ts = { ms / 1000, (ms % 1000) * 1000 * 1000 };
    nanosleep(&ts, NULL);*/
    sleep(ms/1000);
}

bool player::loadVideo(string filename) {
    capture  =  new cv::VideoCapture(filename);
    if (capture->isOpened())
    {
        frameRate = (int) capture->get(CV_CAP_PROP_FPS);
        return true;
    }
    else
        return false;
}

void player::Play(){
    if (!isRunning())
    {
        if (isStopped()){
            stop = false;
        }
        start(LowPriority);
    }
}

void player::run()
{
    int delay = (1000/frameRate);
    //long nbframe = 1;
    Save mySaver(videoPath.toStdString(), this->getFrameSize(), frameRate, this->getCodec());
    AlgoSoustraction *myAlgo;
    if(trajectoreChecked == true){
        myAlgo = new AlgoSoustraction(deplacement, getcurrentImage(framestart), &objectchoose);
    }
    while(!stop){
        if (!capture->read(frame))
        {
            stop = true;
        }
        if (frame.channels()== 3){
            cv::cvtColor(frame, RGBframe, CV_BGR2RGB);

            if(trajectoreChecked == true){
                   myAlgo->decter(RGBframe, getCurrentFrame());
                   myAlgo->getTrajectoire().drawTrajectoire(RGBframe);
            }
            img = QImage((const unsigned char*)(RGBframe.data),
                          RGBframe.cols,RGBframe.rows,QImage::Format_RGB888);
            mySaver.SaveVideo(frame);
           /* myAlgo.decter(frame);
            myAlgo.getTrajectoire().drawTrajectoire(frame);*/
        }
        else
        {
            img = QImage((const unsigned char*)(frame.data),
                         frame.cols,frame.rows,QImage::Format_Indexed8);
            mySaver.SaveVideo(frame);
        }
       // nbframe++;
        emit processedImage(img);
        this->msleep(delay);
    }
    if(trajectoreChecked == true){delete myAlgo;}
}

player::~player()
{
    mutex.lock();
    stop = true;
    capture->release();
    delete capture;
    condition.wakeOne();
    mutex.unlock();
    wait();
}

void player::Stop()
{
    stop = true;
}

bool player::isStopped() const{
    return this->stop;
}

double player::getCurrentFrame(){
    return capture->get(CV_CAP_PROP_POS_FRAMES);
}

double player::getNumberOfFrames(){
    return capture->get(CV_CAP_PROP_FRAME_COUNT);
}

double player::getFrameRate(){
    return frameRate;
}

void player::setCurrentFrame( int frameNumber )
{
    capture->set(CV_CAP_PROP_POS_FRAMES, frameNumber);
}

Mat& player::showImage(int frameNumber){
    capture->set(CV_CAP_PROP_POS_FRAMES, --frameNumber);
    if(frameNumber > 0){
        if(capture->read(frame)){
            cv::cvtColor(frame, RGBframe, CV_BGR2RGB);
            /*img = QImage((const unsigned char*)(RGBframe.data),
                          RGBframe.cols,RGBframe.rows,QImage::Format_RGB888);
            return img;*/
            return RGBframe;
        }
    }
    //return img;
    return RGBframe;
}

Mat player::getcurrentImage(int frameNumber){
    capture->set(CV_CAP_PROP_POS_FRAMES, --frameNumber);
    if(frameNumber > 0){
        if(capture->read(frame)){
            cv::cvtColor(frame, RGBframe, CV_BGR2RGB);
            return RGBframe;
        }
    }
    return RGBframe;
}

void player::setFileName(QString tmpFileName)
{
    videoPath = tmpFileName;
}

void player::setDeplacementMax(int tmpDeplacement)
{
    deplacement = tmpDeplacement;
}

void player::setVideoStart(int tmpstart)
{
    framestart = tmpstart;
}

void player::setVideoFin(int tmpfin)
{
    framefin = tmpfin;
}

/*void player::setStartVideo(long tmpstart)
{
    beginFrame = tmpstart;
    capture->set(CV_CAP_PROP_POS_MSEC, beginFrame);
}

void player::setFinVideo(long tmpfin)
{
    finFrame = tmpfin;
}*/

void player::setObjectChoose(Mat &object){
    objectchoose = object;
}

Mat player::getObjectChoose()
{
    return objectchoose;
}

Size player::getFrameSize(){
    Size size = Size((int)capture->get(CV_CAP_PROP_FRAME_WIDTH), (int)capture->get(CV_CAP_PROP_FRAME_HEIGHT));
    return size;
}

int player::getCodec(){
    return static_cast<int>(capture->get(CV_CAP_PROP_FOURCC));
}

int player::getFrameHeight(){
    return (int)capture->get(CV_CAP_PROP_FRAME_HEIGHT);
}

int player::getFrameWidth(){
    return (int)capture->get(CV_CAP_PROP_FRAME_WIDTH);
}
