/**
 * @Author: Lin SHEN
 * @Version: 2.0
 * @Date: 04/2015
 */

#include "mainwindow.h"
#include <QApplication>

using namespace cv;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    MainWindow* w = new MainWindow();
    w->setAttribute(Qt::WA_DeleteOnClose, true);
    w->show();

    return a.exec();
}

