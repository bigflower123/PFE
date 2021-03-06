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
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
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
    QGraphicsView *graphicsView;
    QPushButton *pauseBtn;
    QProgressBar *progressBar;
    QSlider *videoSlider;
    QLabel *currentLbl;
    QLabel *TotalLbl;
    QMenuBar *menuBar;
    QMenu *menuFichier;
    QMenu *menuInformation;
    QMenu *menuR_glage;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(750, 483);
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
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(20, 10, 511, 330));
        pauseBtn = new QPushButton(centralWidget);
        pauseBtn->setObjectName(QStringLiteral("pauseBtn"));
        pauseBtn->setGeometry(QRect(580, 130, 61, 31));
        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(0, 350, 551, 21));
        progressBar->setValue(24);
        videoSlider = new QSlider(centralWidget);
        videoSlider->setObjectName(QStringLiteral("videoSlider"));
        videoSlider->setGeometry(QRect(70, 380, 451, 19));
        videoSlider->setOrientation(Qt::Horizontal);
        currentLbl = new QLabel(centralWidget);
        currentLbl->setObjectName(QStringLiteral("currentLbl"));
        currentLbl->setGeometry(QRect(10, 380, 46, 13));
        TotalLbl = new QLabel(centralWidget);
        TotalLbl->setObjectName(QStringLiteral("TotalLbl"));
        TotalLbl->setGeometry(QRect(530, 380, 46, 13));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 750, 21));
        menuFichier = new QMenu(menuBar);
        menuFichier->setObjectName(QStringLiteral("menuFichier"));
        menuInformation = new QMenu(menuBar);
        menuInformation->setObjectName(QStringLiteral("menuInformation"));
        menuR_glage = new QMenu(menuBar);
        menuR_glage->setObjectName(QStringLiteral("menuR_glage"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFichier->menuAction());
        menuBar->addAction(menuInformation->menuAction());
        menuBar->addAction(menuR_glage->menuAction());
        menuFichier->addAction(actionOuvrirVideo);
        menuFichier->addAction(actionSauvegarderVideo);
        menuFichier->addAction(actionSauvegarderDonnees);
        menuFichier->addAction(actionQuitter);
        menuInformation->addAction(actionInformationObjet);
        menuR_glage->addAction(actionDeplacement);

        retranslateUi(MainWindow);
        QObject::connect(actionQuitter, SIGNAL(triggered()), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionOuvrirVideo->setText(QApplication::translate("MainWindow", "Ouvrir vid\303\251o", 0));
        actionSauvegarderVideo->setText(QApplication::translate("MainWindow", "Sauvegarder vid\303\251o", 0));
        actionSauvegarderDonnees->setText(QApplication::translate("MainWindow", "Sauvegarder donn\303\251es", 0));
        actionQuitter->setText(QApplication::translate("MainWindow", "Quitter", 0));
        actionInformationObjet->setText(QApplication::translate("MainWindow", "Information objet", 0));
        actionDeplacement->setText(QApplication::translate("MainWindow", "D\303\251placement max", 0));
        pauseBtn->setText(QApplication::translate("MainWindow", "Pause", 0));
        currentLbl->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        TotalLbl->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        menuFichier->setTitle(QApplication::translate("MainWindow", "Fichier", 0));
        menuInformation->setTitle(QApplication::translate("MainWindow", "Information", 0));
        menuR_glage->setTitle(QApplication::translate("MainWindow", "R\303\251glage", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
