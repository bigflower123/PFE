#include "video_qlabel.h"

video_qlabel::video_qlabel(QWidget *parent) :
    QLabel(parent)
{
     myPlayer = new player();
     this->setMouseTracking(true);
}

void video_qlabel::mouseMoveEvent(QMouseEvent *evt)
{
    int x = evt->x();
    int y = evt->y();
    this->setCursor(Qt::CrossCursor);
    if(evt->buttons() & Qt::LeftButton){
        emit Mouse_Move_Pressed(x, y);
    }else if(!evt->buttons()){
        emit Mouse_Move(x, y);
    }
}

void video_qlabel::mousePressEvent(QMouseEvent *evt)
{
    int x = evt->x();
    int y = evt->y();
    emit Mouse_Pressed(x, y);
}

void video_qlabel::mouseReleaseEvent(QMouseEvent *evt)
{
    int x = evt->x();
    int y = evt->y();
    emit Mouse_Left(x, y);
}


