#include "fichiercontrol.h"

double totalFrameNumber;
int currentFrame;
VideoCapture cap;
Mat frame;

fichierControl::fichierControl()
{
}

void tbCallback (int pos,void* usrdata)
{
    Mat src = *(Mat*)(usrdata);
    cap.set(CV_CAP_PROP_POS_FRAMES, pos);
    currentFrame = pos;
    imshow ("MyVideo",src);
}

void fichierControl::openVideo(QString &fileName, QGraphicsView *videoGraphicsview)
{
    cap.open(fileName.toStdString());
    if ( !cap.isOpened() )  // if not success, exit program
    {
       cout << "Cannot open the video file" << endl;
    }
    cap.set(CV_CAP_PROP_POS_MSEC, 300); //start the video at 300ms
    double fps = cap.get(CV_CAP_PROP_FPS); //get the frames per seconds of the video
    cout << "Frame per seconds : " << fps << endl;
    totalFrameNumber = cap.get(CV_CAP_PROP_FRAME_COUNT); //Number frame
    namedWindow("MyVideo",CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"
    if(totalFrameNumber != 0){
        createTrackbar("Position", "MyVideo",&currentFrame, totalFrameNumber, tbCallback, &frame);
    }

    while(1)
    {
        bool bSuccess = cap.read(frame); // read a new frame from video
         if (!bSuccess) //if not success, break loop
        {
               cout << "Cannot read the frame from video file" << endl;
               break;
        }

        imshow("MyVideo", frame); //show the frame in "MyVideo" window
        if(waitKey(30) == 27) //wait for 'esc' key press for 30 ms. If 'esc' key is pressed, break loop
       {
              cout << "esc key is pressed by user" << endl;
              break;

       }else if(waitKey(30) > 0 && waitKey(30) != 27 ){
            waitKey(-1);
        }
       currentFrame++;
       setTrackbarPos("Position", "MyVideo",currentFrame);
    }
}


