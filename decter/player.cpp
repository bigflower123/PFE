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
    capture.open(filename);
    if (capture.isOpened())
    {
        frameRate = (int) capture.get(CV_CAP_PROP_FPS);
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
    while(!stop){
        if (!capture.read(frame))
        {
            stop = true;
        }
        if (frame.channels()== 3){
            cv::cvtColor(frame, RGBframe, CV_BGR2RGB);
            img = QImage((const unsigned char*)(RGBframe.data),
                          RGBframe.cols,RGBframe.rows,QImage::Format_RGB888);
        }
        else
        {
            img = QImage((const unsigned char*)(frame.data),
                         frame.cols,frame.rows,QImage::Format_Indexed8);
        }
        emit processedImage(img);
        this->msleep(delay);
    }
}

player::~player()
{
    mutex.lock();
    stop = true;
    capture.release();
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
