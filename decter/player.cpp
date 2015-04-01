#include "player.h"
#include <time.h>
#include <conio.h>

/**
 * Constructeur
 * @brief player::player
 * @param parent
 */
player::player(QObject *parent)
 : QThread(parent)
{
    stop = true;
}

/**
 * Destructeur
 * @brief player::~player
 */
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

/**
 * sleep
 * @brief player::msleep
 * @param ms
 */
void player::msleep(int ms){
    /*struct timespec ts = { ms / 1000, (ms % 1000) * 1000 * 1000 };
    nanosleep(&ts, NULL);*/
    sleep(ms/1500);
}


/**
 * load video from file
 * @brief player::loadVideo
 * @param filename
 * @return
 */
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

/**
 * Play video
 * @brief player::Play
 */
void player::Play(){
    if (!isRunning())
    {
        if (isStopped()){
            stop = false;
        }
        start(LowPriority);
    }
}

/**
 * stop video
 * @brief player::Stop
 */
void player::Stop()
{
    stop = true;
}

/**
 * if video is stopped
 * @brief player::isStopped
 * @return
 */
bool player::isStopped() const{
    return this->stop;
}

/**
 * Run of thread
 * @brief player::run
 */
void player::run()
{
    clock_t t_start,t_end, t_start1, t_end1;
    double delay = (1000/frameRate);
    /******************************Save le vidéo******************************************/
    Save mySaver(videoPath.toStdString(), this->getFrameSize(), frameRate, this->getCodec());
    /*************************************************************************************/
    /******************************Algo de détection**************************************/
    AlgoSoustraction *myAlgo;
    if(trajectoreChecked == true){
        myAlgo = new AlgoSoustraction(deplacement, this->getFistFrame(), &objectchoose);
    }

    /*************************************************************************************/
    qDebug() << framecount;
    while(!stop){
        if (!capture->read(frame))
        {
            stop = true;
            qDebug()<<"frame read fin";
        }else{
            if (frame.channels()== 3){
                //cv::cvtColor(frame, RGBframe, CV_BGR2RGB);
                /****************Algo de détection*************************/
                if(trajectoreChecked == true){
                       t_start = clock();
                       myAlgo->decter(frame, getCurrentFrame());
                       this->setThresh(myAlgo->thresh_red_1,myAlgo->thresh_red_2, myAlgo->thresh_green_1,
                                       myAlgo->thresh_green_2, myAlgo->thresh_blue_1, myAlgo->thresh_blue_2);
                       t_end = clock();
                       qDebug()<< "detecter time" <<(double)(t_end - t_start) / CLOCKS_PER_SEC;;
                       t_start1 = clock();
                       myAlgo->getTrajectoire().drawTrajectoire(frame);
                       t_end1 = clock();
                       qDebug()<< "draw time" <<(double)(t_end1 - t_start1) / CLOCKS_PER_SEC;;
                }
                /**********************************************************/
                cv::cvtColor(frame, RGBframe, CV_BGR2RGB);
                img = QImage((const unsigned char*)(RGBframe.data),
                              RGBframe.cols,RGBframe.rows,QImage::Format_RGB888);
                /***********Save le vidéo*********************************/
                 mySaver.SaveVideo(frame);
                /*********************************************************/
            }
            else
            {
                img = QImage((const unsigned char*)(frame.data),
                             frame.cols,frame.rows,QImage::Format_Indexed8);
                /***********Save le vidéo*********************************/
                mySaver.SaveVideo(frame);
                /*********************************************************/
            }
            nbframe++;
            emit processedImage(img);
            this->msleep(delay);
        }
    }
    qDebug()<<nbframe;
    if(trajectoreChecked == true){delete myAlgo;}
}


/*****************Get and set parametres of the video******************/

/**
 * Get value of current frame
 * @brief player::getCurrentFrame
 * @return
 */
double player::getCurrentFrame(){
    return capture->get(CV_CAP_PROP_POS_FRAMES);
}

/**
 * Total frame number
 * @brief player::getNumberOfFrames
 * @return
 */
double player::getNumberOfFrames(){
    framecount = capture->get(CV_CAP_PROP_FRAME_COUNT);
    return framecount;
}

/**
 * frame rate
 * @brief player::getFrameRate
 * @return
 */
double player::getFrameRate(){
    frameRate = capture->get(CV_CAP_PROP_FPS);
    return frameRate;
}

/**
 * Set video in the current frame
 * @brief player::setCurrentFrame
 * @param frameNumber
 */
void player::setCurrentFrame( int frameNumber )
{
    capture->set(CV_CAP_PROP_POS_FRAMES, frameNumber);
}

/**
 * Get the size of video
 * @brief player::getFrameSize
 * @return
 */
Size player::getFrameSize(){
    Size size = Size((int)capture->get(CV_CAP_PROP_FRAME_WIDTH), (int)capture->get(CV_CAP_PROP_FRAME_HEIGHT));
    return size;
}

/**
 * Get codec of video
 * @brief player::getCodec
 * @return
 */
int player::getCodec(){
    return static_cast<int>(capture->get(CV_CAP_PROP_FOURCC));
}

/**
 * Get frame height of video
 * @brief player::getFrameHeight
 * @return
 */
int player::getFrameHeight(){
    return (int)capture->get(CV_CAP_PROP_FRAME_HEIGHT);
}

/**
 * Get frame width of video
 * @brief player::getFrameWidth
 * @return
 */
int player::getFrameWidth(){
    return (int)capture->get(CV_CAP_PROP_FRAME_WIDTH);
}
/********************************************************************/
/**
 * Get image in the position frameNumber
 * @brief player::showImage
 * @param frameNumber
 * @return
 */
Mat& player::showImage(int frameNumber){
    capture->set(CV_CAP_PROP_POS_FRAMES, --frameNumber);
    if(frameNumber > 0){
        if(capture->read(frame)){
             cv::cvtColor(frame, RGBframe, CV_BGR2RGB);
             return RGBframe;
        }
    }
    return RGBframe;
}

/**
 * Read next frame
 * @brief player::getNextframe
 * @return
 */
Mat player::getNextframe()
{
    if(capture->read(frame)){
        if(frame.channels() == 3){
            cv::cvtColor(frame, RGBframe, CV_BGR2RGB);
        }
    }
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

/**
 * set value of deplcamentMax
 * @brief player::setDeplacementMax
 * @param tmpDeplacement
 */
void player::setDeplacementMax(int tmpDeplacement)
{
    deplacement = tmpDeplacement;
}

/**
 * set start frame
 * @brief player::setVideoStart
 * @param tmpstart
 */
void player::setVideoStart(int tmpstart)
{
    framestart = tmpstart;
}

/**
 * set fin frame
 * @brief player::setVideoFin
 * @param tmpfin
 */
void player::setVideoFin(int tmpfin)
{
    framefin = tmpfin;
}

/**
 * set nombre frame
 * @brief player::setFramenb
 * @param tmpnb
 */
void player::setFramenb(long tmpnb)
{
    nbframe = tmpnb;
}

/**
 * get nombre frame
 * @brief player::getFramenb
 * @return
 */
long player::getFramenb()
{
    return nbframe;
}

/**
 * set object choose
 * @brief player::setObjectChoose
 * @param object
 */
void player::setObjectChoose(Mat &object){
    objectchoose = object;
}

/**
 * get object choose
 * @brief player::getObjectChoose
 * @return
 */
Mat player::getObjectChoose()
{
    return objectchoose;
}

/**
 * set threshold()
 * @brief player::setThresh
 * @param red1
 * @param red2
 * @param blue1
 * @param blue2
 * @param green1
 * @param green2
 */
void player::setThresh(int red1, int red2, int blue1, int blue2, int green1, int green2)
{
    thresh[0] = red1;
    thresh[1] = red2;
    thresh[2] = blue1;
    thresh[3] = blue2;
    thresh[4] = green1;
    thresh[5] = green2;
}


/**
 * Get first frame of video
 * @brief player::getFistFrame
 * @return
 */
Mat player::getFistFrame()
{
    Mat frame;
    capture->set(CV_CAP_PROP_POS_FRAMES, 1);
    if(capture->read(frame)){
        //cv::cvtColor(frame, frame, CV_BGR2RGB);
        return frame;
     }
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




