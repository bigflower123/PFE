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
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOuvrirVideo;
    QAction *actionSauvegarderVideo;
    QAction *actionSauvegarderDonnees;
    QAction *actionQuitter;
    QAction *actionInformationObjet;
    QAction *actionDeplacement;
    QWidget *centralWidget;
    QLabel *VideoLbl;
    QPushButton *playBtn;
    QSlider *videoSlider;
    QLabel *currentLable;
    QLabel *totalLable;
    QPushButton *forwardButton;
    QPushButton *backwardButton;
    QMenuBar *menuBar;
    QMenu *menuFichier;
    QMenu *menuInformation;
    QMenu *menuReglage;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(742, 465);
        actionOuvrirVideo = new QAction(MainWindow);
        actionOuvrirVideo->setObjectName(QStringLiteral("actionOuvrirVideo"));
        actionSauvegarderVideo = new QAction(MainWindow);
        actionSauvegarderVideo->setObjectName(QStringLiteral("actionSauvegarderVideo"));
        actionSauvegarderDonnees = new QAction(MainWindow);
        actionSauvegarderDonnees->setObjectName(QStringLiteral("actionSauvegarderDonnees"));
        actionQuitter = new QAction(MainWindow);
        actionQuitter->setObjectName(QStringLiteral("actionQuitter"));
        actionInformationObjet = new QAction(MainWindow);
        actionInformationObjet->setObjectName(QStringLiteral("actionInformationObjet"));
        actionDeplacement = new QAction(MainWindow);
        actionDeplacement->setObjectName(QStringLiteral("actionDeplacement"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        VideoLbl = new QLabel(centralWidget);
        VideoLbl->setObjectName(QStringLiteral("VideoLbl"));
        VideoLbl->setGeometry(QRect(20, 20, 501, 321));
        VideoLbl->setStyleSheet(QStringLiteral("Background-color: #000;"));
        playBtn = new QPushButton(centralWidget);
        playBtn->setObjectName(QStringLiteral("playBtn"));
        playBtn->setGeometry(QRect(500, 360, 51, 21));
        videoSlider = new QSlider(centralWidget);
        videoSlider->setObjectName(QStringLiteral("videoSlider"));
        videoSlider->setGeometry(QRect(40, 360, 321, 20));
        videoSlider->setOrientation(Qt::Horizontal);
        currentLable = new QLabel(centralWidget);
        currentLable->setObjectName(QStringLiteral("currentLable"));
        currentLable->setGeometry(QRect(10, 360, 31, 16));
        totalLable = new QLabel(centralWidget);
        totalLable->setObjectName(QStringLiteral("totalLable"));
        totalLable->setGeometry(QRect(370, 360, 41, 16));
        forwardButton = new QPushButton(centralWidget);
        forwardButton->setObjectName(QStringLiteral("forwardButton"));
        forwardButton->setGeometry(QRect(560, 360, 75, 23));
        backwardButton = new QPushButton(centralWidget);
        backwardButton->setObjectName(QStringLiteral("backwardButton"));
        backwardButton->setGeometry(QRect(410, 360, 75, 23));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 742, 21));
        menuFichier = new QMenu(menuBar);
        menuFichier->setObjectName(QStringLiteral("menuFichier"));
        menuInformation = new QMenu(menuBar);
        menuInformation->setObjectName(QStringLiteral("menuInformation"));
        menuReglage = new QMenu(menuBar);
        menuReglage->setObjectName(QStringLiteral("menuReglage"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFichier->menuAction());
        menuBar->addAction(menuInformation->menuAction());
        menuBar->addAction(menuReglage->menuAction());
        menuFichier->addAction(actionOuvrirVideo);
        menuFichier->addAction(actionSauvegarderVideo);
        menuFichier->addAction(actionSauvegarderDonnees);
        menuFichier->addAction(actionQuitter);
        menuInformation->addAction(actionInformationObjet);
        menuReglage->addAction(actionDeplacement);

        retranslateUi(MainWindow);
        QObject::connect(actionQuitter, SIGNAL(triggered()), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Vid\303\251o", 0));
        actionOuvrirVideo->setText(QApplication::translate("MainWindow", "Ouvrir vid\303\251o", 0));
        actionSauvegarderVideo->setText(QApplication::translate("MainWindow", "Sauvegarder vid\303\251o", 0));
        actionSauvegarderDonnees->setText(QApplication::translate("MainWindow", "Sauvegarder donn\303\251es", 0));
        actionQuitter->setText(QApplication::translate("MainWindow", "Quitter", 0));
        actionInformationObjet->setText(QApplication::translate("MainWindow", "Information objet", 0));
        actionDeplacement->setText(QApplication::translate("MainWindow", "D\303\251placement max", 0));
        VideoLbl->setText(QString());
        playBtn->setText(QApplication::translate("MainWindow", "Play", 0));
        currentLable->setText(QApplication::translate("MainWindow", "0", 0));
        totalLable->setText(QApplication::translate("MainWindow", "0", 0));
        forwardButton->setText(QApplication::translate("MainWindow", "Forward", 0));
        backwardButton->setText(QApplication::translate("MainWindow", "Backward", 0));
        menuFichier->setTitle(QApplication::translate("MainWindow", "Ficher", 0));
        menuInformation->setTitle(QApplication::translate("MainWindow", "Information", 0));
        menuReglage->setTitle(QApplication::translate("MainWindow", "R\303\251glage", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
