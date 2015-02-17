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
    int x, y;

signals:
    void Mouse_Pressed();
    void Mouse_Pos();
    void Mouse_Left();

public slots:

private:
    player *myPlayer;
    QImage org, img, tmpImg;
};

#endif // VIDEO_QLABEL_H
