#ifndef VIDEO_QLABEL_H
#define VIDEO_QLABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <QEvent>
#include "player.h"

class video_qlabel : public QLabel
{
    Q_OBJECT
public:
    explicit video_qlabel(QWidget *parent = 0);
    //void eventFilter(QObject *, QEvent *);

signals:
    void Mouse_Pressed(int, int);
    void Mouse_Move(int, int);
    void Mouse_Left(int , int);
    void Mouse_Move_Pressed(int, int);

protected:
     void mouseMoveEvent(QMouseEvent *evt);
     void mousePressEvent(QMouseEvent *evt);
     void mouseReleaseEvent(QMouseEvent *evt);

private:
    player *myPlayer;
    Mat org, img, tmp;
    char coord[16];
    Point pre_pt = (-1,-1);
    Point cur_pt = (-1,-1);
};

#endif // VIDEO_QLABEL_H
