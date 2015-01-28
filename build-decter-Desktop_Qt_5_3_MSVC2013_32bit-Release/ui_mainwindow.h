/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOuvrirVideo;
    QWidget *centralWidget;
    QLabel *VideoLbl;
    QPushButton *playBtn;
    QMenuBar *menuBar;
    QMenu *menuFichier;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(631, 455);
        actionOuvrirVideo = new QAction(MainWindow);
        actionOuvrirVideo->setObjectName(QStringLiteral("actionOuvrirVideo"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        VideoLbl = new QLabel(centralWidget);
        VideoLbl->setObjectName(QStringLiteral("VideoLbl"));
        VideoLbl->setGeometry(QRect(20, 20, 461, 321));
        VideoLbl->setStyleSheet(QStringLiteral("Background-color: #000;"));
        playBtn = new QPushButton(centralWidget);
        playBtn->setObjectName(QStringLiteral("playBtn"));
        playBtn->setGeometry(QRect(510, 130, 75, 23));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 631, 21));
        menuFichier = new QMenu(menuBar);
        menuFichier->setObjectName(QStringLiteral("menuFichier"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFichier->menuAction());
        menuFichier->addAction(actionOuvrirVideo);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionOuvrirVideo->setText(QApplication::translate("MainWindow", "Ouvrir video", 0));
        VideoLbl->setText(QString());
        playBtn->setText(QApplication::translate("MainWindow", "Play", 0));
        menuFichier->setTitle(QApplication::translate("MainWindow", "Fichier", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
