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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <video_qlabel.h>

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
    video_qlabel *VideoLbl;
    QPushButton *playBtn;
    QSlider *videoSlider;
    QLabel *currentLable;
    QLabel *totalLable;
    QPushButton *forwardButton;
    QPushButton *backwardButton;
    QPushButton *debutButton;
    QPushButton *finButton;
    QCheckBox *trajectoirecheckBox;
    QPushButton *quickbackwardButton;
    QPushButton *quickforwardButton;
    QListView *listView;
    QLabel *commentlabel;
    QTextEdit *commenttextEdit;
    QPushButton *commentButton;
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
        MainWindow->resize(1165, 706);
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
        VideoLbl = new video_qlabel(centralWidget);
        VideoLbl->setObjectName(QStringLiteral("VideoLbl"));
        VideoLbl->setGeometry(QRect(9, 9, 871, 511));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(VideoLbl->sizePolicy().hasHeightForWidth());
        VideoLbl->setSizePolicy(sizePolicy);
        VideoLbl->setStyleSheet(QStringLiteral("Background-color: #000;"));
        playBtn = new QPushButton(centralWidget);
        playBtn->setObjectName(QStringLiteral("playBtn"));
        playBtn->setGeometry(QRect(340, 600, 71, 21));
        playBtn->setStyleSheet(QStringLiteral("width:15px;height:15px;border-radius:7.5px;border:2px groove gray;"));
        videoSlider = new QSlider(centralWidget);
        videoSlider->setObjectName(QStringLiteral("videoSlider"));
        videoSlider->setGeometry(QRect(200, 560, 361, 20));
        videoSlider->setOrientation(Qt::Horizontal);
        currentLable = new QLabel(centralWidget);
        currentLable->setObjectName(QStringLiteral("currentLable"));
        currentLable->setGeometry(QRect(130, 560, 51, 16));
        totalLable = new QLabel(centralWidget);
        totalLable->setObjectName(QStringLiteral("totalLable"));
        totalLable->setGeometry(QRect(610, 560, 41, 16));
        forwardButton = new QPushButton(centralWidget);
        forwardButton->setObjectName(QStringLiteral("forwardButton"));
        forwardButton->setGeometry(QRect(660, 560, 41, 17));
        forwardButton->setStyleSheet(QStringLiteral("border-radius:7.5px;border:2px groove gray;"));
        backwardButton = new QPushButton(centralWidget);
        backwardButton->setObjectName(QStringLiteral("backwardButton"));
        backwardButton->setGeometry(QRect(70, 560, 41, 20));
        backwardButton->setStyleSheet(QStringLiteral("border-radius:7.5px;border:2px groove gray;"));
        debutButton = new QPushButton(centralWidget);
        debutButton->setObjectName(QStringLiteral("debutButton"));
        debutButton->setGeometry(QRect(200, 600, 75, 23));
        finButton = new QPushButton(centralWidget);
        finButton->setObjectName(QStringLiteral("finButton"));
        finButton->setGeometry(QRect(480, 600, 75, 23));
        trajectoirecheckBox = new QCheckBox(centralWidget);
        trajectoirecheckBox->setObjectName(QStringLiteral("trajectoirecheckBox"));
        trajectoirecheckBox->setGeometry(QRect(610, 600, 74, 17));
        quickbackwardButton = new QPushButton(centralWidget);
        quickbackwardButton->setObjectName(QStringLiteral("quickbackwardButton"));
        quickbackwardButton->setGeometry(QRect(20, 560, 41, 17));
        quickbackwardButton->setStyleSheet(QStringLiteral("border-radius:7.5px;border:2px groove gray;"));
        quickforwardButton = new QPushButton(centralWidget);
        quickforwardButton->setObjectName(QStringLiteral("quickforwardButton"));
        quickforwardButton->setGeometry(QRect(720, 560, 51, 20));
        quickforwardButton->setStyleSheet(QStringLiteral("border-radius:7.5px;border:2px groove gray;"));
        listView = new QListView(centralWidget);
        listView->setObjectName(QStringLiteral("listView"));
        listView->setGeometry(QRect(900, 20, 256, 321));
        commentlabel = new QLabel(centralWidget);
        commentlabel->setObjectName(QStringLiteral("commentlabel"));
        commentlabel->setGeometry(QRect(900, 350, 67, 16));
        commenttextEdit = new QTextEdit(centralWidget);
        commenttextEdit->setObjectName(QStringLiteral("commenttextEdit"));
        commenttextEdit->setGeometry(QRect(900, 370, 256, 192));
        commentButton = new QPushButton(centralWidget);
        commentButton->setObjectName(QStringLiteral("commentButton"));
        commentButton->setGeometry(QRect(1000, 600, 75, 23));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1165, 21));
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
        menuBar->addAction(menuReglage->menuAction());
        menuBar->addAction(menuInformation->menuAction());
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
        forwardButton->setText(QApplication::translate("MainWindow", ">", 0));
        backwardButton->setText(QApplication::translate("MainWindow", "<", 0));
        debutButton->setText(QApplication::translate("MainWindow", "D\303\251but", 0));
        finButton->setText(QApplication::translate("MainWindow", "Fin", 0));
        trajectoirecheckBox->setText(QApplication::translate("MainWindow", "Trajectoire", 0));
        quickbackwardButton->setText(QApplication::translate("MainWindow", "<<", 0));
        quickforwardButton->setText(QApplication::translate("MainWindow", ">>", 0));
        commentlabel->setText(QApplication::translate("MainWindow", "Commentaire:", 0));
        commentButton->setText(QApplication::translate("MainWindow", "Confirme", 0));
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
