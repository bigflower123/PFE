#include "player.h"
#include <time.h>
#include <conio.h>
#include <QDir>
#include <QMessageBox>

/**
 * Constructeur
 * @brief player::player
 * @param parent
 */
player::player(QObject *parent)
 : QThread(parent)
{
    stop = true;
    nbframe = 0;
    framecount = 0;
    videoPath = "";
    info = "";
    deplacement = 150;
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
    //Clear hash
    hash.clear();

    if (capture->isOpened())
    {
        frameRate = (int) capture->get(CV_CAP_PROP_FPS);
        //Set nbframe à 0
        nbframe = 0;
        flagcontinue = 0;
        flagSave = 0;
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
    char bufferx[50], buffery[50];
    int currentFrame;
    double delay = (1000/frameRate);
    if(nbframe == 0 ){
        capture->set(CV_CAP_PROP_POS_FRAMES,0);
        firstframe = this->getFirstFrame();
    }
    currentFrame = this->getCurrentFrame();
    /******************************Algo de détection**************************************/
    if(trajectoreChecked == true && flagcontinue == 0){
        myAlgo = new AlgoSoustraction(deplacement, firstframe, &objectchoose, flagcontinue);
        qDebug()<<"flagcontinue="<<++flagcontinue;
    }

    /*************************************************************************************/
    qDebug() << framecount<<" "<<currentFrame<<" "<<this->framefin;
    while(!stop && currentFrame < this->framefin){
        currentFrame = getCurrentFrame();
        if (!capture->read(frame))
        {
            stop = true;
            qDebug()<<"frame read fin";
        }else{
            if (frame.channels()== 3){
                //cv::cvtColor(frame, RGBframe, CV_BGR2RGB);
                /****************Algo de détection*************************/
                this->info = "";
                if(trajectoreChecked == true){
                       myAlgo->decter(frame, getCurrentFrame());
                       if(!myAlgo->getTrajectoire().getCenterlist().empty()){
                            this->info = myAlgo->getTrajectoire().getCenterlist().back().nodeToString();
                       }
                       myAlgo->getTrajectoire().drawTrajectoire(frame);

                }
                /**********************************************************/
                /**************************************/
                if(this->flagVisualier == true && this->flagTraiter == false){
                    if(hash.contains(currentFrame)){
                       sprintf_s(bufferx, "%-.2f", hash[currentFrame].x);
                       sprintf_s(buffery, "%-.2f", hash[currentFrame].y);
                       info = QString("%1;   %2;   %3").arg(currentFrame).arg(bufferx).arg(buffery);                 
                    }
                    if(currentFrame >= beginFrame){
                        drawTrack(currentFrame, frame);
                    }
                }
                /************************************/
                cv::cvtColor(frame, RGBframe, CV_BGR2RGB);
                img = QImage((const unsigned char*)(RGBframe.data),
                              RGBframe.cols,RGBframe.rows,QImage::Format_RGB888);
            }
            else
            {
                img = QImage((const unsigned char*)(frame.data),
                             frame.cols,frame.rows,QImage::Format_Indexed8);
            }
            nbframe++;
            emit processedImage(img, this->info);

            this->msleep(delay);
        }
    }
    qDebug()<<nbframe;
    if(trajectoreChecked == true && flagcontinue == 0){delete myAlgo;}
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
    if(frameNumber != 0){
        --frameNumber;
    }
    capture->set(CV_CAP_PROP_POS_FRAMES, frameNumber);
    if(frameNumber >= 0){
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


/**
 * Draw trajectory
 * @brief player::drawTrack
 * @param currentFrame
 * @param frame
 */
void player::drawTrack(int currentFrame,Mat &frame)
{
    QString tmp;
    char bufferx[50], buffery[50];
    int j = 0;
    strList.clear();
    if(currentFrame >= beginFrame){
        for(int i = beginFrame; i <= currentFrame; i++){
            if(hash.contains(i)){
                sprintf_s(bufferx, "%-.2f", hash[i].x);
                sprintf_s(buffery, "%-.2f", hash[i].y);
                tmp = QString("%1;  %2;  %3").arg(i).arg(bufferx).arg(buffery);
                strList.append(tmp);
                if(hash.contains(i+1)){
                    if(j <= 255){
                        j = i*0.1;
                    }
                     Scalar color( j, 255, j);
                     line(frame, hash[i], hash[i+1],color,3);
                }
            }
        }
    }
}

/**
 * @brief player::getStrList
 * @return
 */
QStringList player::getStrList()
{
    return strList;
}

void player::setFlagTraiter(bool tmpTraiter)
{
    this->flagTraiter = tmpTraiter;
}

QString player::getInfoPath()
{
    return this->infoPath;
}

void player::setFlagVisualiser(bool tmpVisualiser)
{
    this->flagVisualier = tmpVisualiser;
}

/**
 * Get current Image
 * @brief player::getcurrentImage
 * @param frameNumber
 * @return
 */
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

/**
 * Save Path of information coordinate
 * @brief player::setFileName
 * @param tmpFileName
 */
void player::setFileName(QString tmpFileName)
{
    videoPath = tmpFileName;
}

/**
 * set file name(information of coordinate)
 * @brief player::setFileInfoName
 * @param tmpInfoName
 */
void player::setFileInfoName(QString tmpInfoName)
{
    int i = 0;
    infoPath = tmpInfoName;
    QString donnee;
    Point2f pt;
    QByteArray line;
    //Initialiser readFile
    readFile.setFileName(tmpInfoName);
    if(!readFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug()<<"Can't open the file!"<<endl;
        this->flagFileOpen = false;
    }else{
        this->flagFileOpen = true;
        while(!readFile.atEnd()){
             line = readFile.readLine();
             donnee = line;
             if(i == 0){
                beginFrame = donnee.section(";",0,0).toInt();
                i = 1;
             }
             pt.x = donnee.section(";",1,1).toFloat();
             pt.y = donnee.section(";",2,2).toFloat();
             hash[donnee.section(";",0,0).toInt()] = pt;
        }

    }
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
    capture->set(CV_CAP_PROP_POS_FRAMES, framestart);

}

/**
 * set fin frame
 * @brief player::setVideoFin
 * @param tmpfin
 */
void player::setVideoFin(int tmpfin)
{
    framefin = tmpfin;
    capture->set(CV_CAP_PROP_POS_FRAMES, framestart);
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
 * Get first frame of video
 * @brief player::getFistFrame
 * @return
 */
Mat player::getFirstFrame()
{
    Mat frame;
    capture->set(CV_CAP_PROP_POS_FRAMES, 1);
    if(capture->read(frame)){
        //cv::cvtColor(frame, frame, CV_BGR2RGB);
        return frame;
    }
    return frame;
}


/**
 * Set flag: times of choose object
 * @brief player::setFlagTimes
 * @param tmpTimes
 */
void player::setFlagTimes(int tmpTimes)
{
    this->flagtimeschoose = tmpTimes;
}

/**
 * Set flag: flagcontinue
 * @brief player::setFlagContinue
 * @param tmpContinue
 */
void player::setFlagContinue(int tmpContinue)
{
    this->flagcontinue = tmpContinue;
}






