#include "fichiercontrol.h"

int currentFrame;
VideoCapture cap;
int trackbarPos;

fichierControl::fichierControl()
{
}

void tbCallback (int pos,void* usrdata)
{
    Mat src = *(Mat*)(usrdata);
    cap.set(CV_CAP_PROP_POS_FRAMES, pos);
    currentFrame = pos;
    //imshow ("MyVideo",src);
}

void fichierControl::openVideo(QString &fileName, QGraphicsView *videoGraphicsview, QProgressBar *progressBar)
{
    bool stop = false;
    if (!cap.open(fileName.toStdString())){
          cout << "Cannot read the frame from video file" << endl;
    }
    //get the number of frame
    long totalFrameNumber = cap.get(CV_CAP_PROP_FRAME_COUNT);
    cout<<"Number of frame"<<totalFrameNumber<<endl;

    //start the video at 300ms
    long frameToStart = 300;
    cap.set( CV_CAP_PROP_POS_FRAMES,frameToStart);
    cout<<"Frame to start"<<frameToStart<<endl;

    //stop the video at 400ms
    int frameToStop = 400;

    if(frameToStop < frameToStart)
    {
        cout<<"Frametostop smaller than frametostart！"<<endl;
    }
    else
    {
        cout<<"Frame to stop"<<frameToStop<<endl;
    }

    //get the frames per seconds of the video
    double rate = cap.get(CV_CAP_PROP_FPS);
    cout<<"the frames per seconds"<<rate<<endl;

    int delay = 1000/rate;
    currentFrame = frameToStart;

    //set the minimum and maximum value of progressBar
    progressBar->setMinimum(frameToStart);
    progressBar->setMaximum(frameToStop);
    //namedWindow("MyVideo",WINDOW_NORMAL); //create a window called "MyVideo"
    //resizeWindow("MyVideo", 400, 300);
    //Create Trackbar
    /*if(totalFrameNumber != 0){
         createTrackbar("Position", "MyVideo", &currentFrame, totalFrameNumber, tbCallback, &frame);
    }*/
    while(!stop)
    {
         bool bSuccess = cap.read(frame); // read a new frame from video
         if (!bSuccess) //if not success, break loop
         {
                cout << "Cannot read the frame from video file" << endl;
         }
         /*******/
          if(frame.data){
              cvtColor(frame, frame, CV_BGR2RGB);  //Qt support RGB, OpenCv support BGR
          }else{
              cout << "Frame no data" << endl;
          }
          QImage image = QImage((uchar*)(frame.data), frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
          QImage result = image.scaled(800,600).scaled(495,325, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
          QGraphicsScene *scene = new QGraphicsScene;
          scene->addPixmap(QPixmap::fromImage(result));
          videoGraphicsview->setScene(scene);
          videoGraphicsview->show();
          cout<<"currentFrame"<<currentFrame<<endl;
         /*******/
         //imshow("MyVideo", frame); //show the frame in "MyVideo" window
         if(waitKey(delay) == 27 || currentFrame >= frameToStop) //wait for 'esc' key press for 30 ms. If 'esc' key is pressed, break loop
         {
               cout << "esc key is pressed by user" << endl;
               stop = true;
         }
         //suspendre
        if( waitKey(delay) >= 0)
        {
            waitKey(0);
        }
        currentFrame++;
        progressBar->setValue(currentFrame);
         //setTrackbarPos("Position", "MyVideo",currentFrame);
     }
    //Close video file
    cap.release();
    waitKey(0);
}

void fichierControl::pauseVideo(QGraphicsView *videoGraphicsview){
    double position= 100.0;
    cap.set(CV_CAP_PROP_POS_FRAMES, position);
    bool bSuccess = cap.read(frame); // read a new frame from video
    if (!bSuccess) //if not success, break loop
    {
           cout << "Cannot read the frame from video file" << endl;
    }
    QImage image = QImage((uchar*)(frame.data), frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
    QImage result = image.scaled(800,600).scaled(495,325, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QGraphicsScene *scene = new QGraphicsScene;
    scene->addPixmap(QPixmap::fromImage(result));
    videoGraphicsview->setScene(scene);
    videoGraphicsview->show();
}
