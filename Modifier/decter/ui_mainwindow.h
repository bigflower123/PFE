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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
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
    QListWidget *listWidget;
    QLabel *label_4;
    QLabel *debutLabel;
    QLabel *label_5;
    QLabel *finLabel;
    QPushButton *savefinButton;
    QGroupBox *groupBox;
    QRadioButton *visualiserButton;
    QRadioButton *traiterButton;
    QPushButton *ouvrirButton;
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
        MainWindow->resize(1248, 685);
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
        VideoLbl->setGeometry(QRect(9, 19, 901, 501));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(VideoLbl->sizePolicy().hasHeightForWidth());
        VideoLbl->setSizePolicy(sizePolicy);
        VideoLbl->setStyleSheet(QStringLiteral("Background-color: #000;"));
        playBtn = new QPushButton(centralWidget);
        playBtn->setObjectName(QStringLiteral("playBtn"));
        playBtn->setGeometry(QRect(390, 580, 71, 21));
        playBtn->setStyleSheet(QStringLiteral("width:15px;height:15px;border-radius:7.5px;border:2px groove gray;"));
        videoSlider = new QSlider(centralWidget);
        videoSlider->setObjectName(QStringLiteral("videoSlider"));
        videoSlider->setGeometry(QRect(190, 550, 481, 20));
        videoSlider->setMinimum(1);
        videoSlider->setValue(1);
        videoSlider->setOrientation(Qt::Horizontal);
        currentLable = new QLabel(centralWidget);
        currentLable->setObjectName(QStringLiteral("currentLable"));
        currentLable->setGeometry(QRect(120, 550, 61, 16));
        totalLable = new QLabel(centralWidget);
        totalLable->setObjectName(QStringLiteral("totalLable"));
        totalLable->setGeometry(QRect(700, 550, 61, 16));
        forwardButton = new QPushButton(centralWidget);
        forwardButton->setObjectName(QStringLiteral("forwardButton"));
        forwardButton->setGeometry(QRect(760, 550, 40, 20));
        forwardButton->setStyleSheet(QStringLiteral("border-radius:7.5px;border:2px groove gray;"));
        backwardButton = new QPushButton(centralWidget);
        backwardButton->setObjectName(QStringLiteral("backwardButton"));
        backwardButton->setGeometry(QRect(70, 550, 40, 20));
        backwardButton->setStyleSheet(QStringLiteral("border-radius:7.5px;border:2px groove gray;"));
        debutButton = new QPushButton(centralWidget);
        debutButton->setObjectName(QStringLiteral("debutButton"));
        debutButton->setGeometry(QRect(190, 580, 75, 23));
        finButton = new QPushButton(centralWidget);
        finButton->setObjectName(QStringLiteral("finButton"));
        finButton->setGeometry(QRect(620, 580, 75, 23));
        trajectoirecheckBox = new QCheckBox(centralWidget);
        trajectoirecheckBox->setObjectName(QStringLiteral("trajectoirecheckBox"));
        trajectoirecheckBox->setGeometry(QRect(90, 580, 74, 17));
        quickbackwardButton = new QPushButton(centralWidget);
        quickbackwardButton->setObjectName(QStringLiteral("quickbackwardButton"));
        quickbackwardButton->setGeometry(QRect(10, 550, 50, 20));
        quickbackwardButton->setStyleSheet(QStringLiteral("border-radius:7.5px;border:2px groove gray;"));
        quickforwardButton = new QPushButton(centralWidget);
        quickforwardButton->setObjectName(QStringLiteral("quickforwardButton"));
        quickforwardButton->setGeometry(QRect(820, 550, 50, 20));
        quickforwardButton->setStyleSheet(QStringLiteral("border-radius:7.5px;border:2px groove gray;"));
        listWidget = new QListWidget(centralWidget);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(940, 80, 291, 431));
        listWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(150, 610, 46, 13));
        debutLabel = new QLabel(centralWidget);
        debutLabel->setObjectName(QStringLiteral("debutLabel"));
        debutLabel->setGeometry(QRect(210, 610, 71, 16));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(580, 610, 46, 13));
        finLabel = new QLabel(centralWidget);
        finLabel->setObjectName(QStringLiteral("finLabel"));
        finLabel->setGeometry(QRect(640, 610, 46, 13));
        savefinButton = new QPushButton(centralWidget);
        savefinButton->setObjectName(QStringLiteral("savefinButton"));
        savefinButton->setGeometry(QRect(1130, 550, 91, 23));
        savefinButton->setStyleSheet(QStringLiteral("width:15px;height:15px;border-radius:7.5px;border:2px groove gray;"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(940, 20, 241, 51));
        visualiserButton = new QRadioButton(groupBox);
        visualiserButton->setObjectName(QStringLiteral("visualiserButton"));
        visualiserButton->setGeometry(QRect(10, 20, 82, 17));
        visualiserButton->setChecked(false);
        traiterButton = new QRadioButton(groupBox);
        traiterButton->setObjectName(QStringLiteral("traiterButton"));
        traiterButton->setGeometry(QRect(110, 20, 82, 17));
        traiterButton->setChecked(true);
        ouvrirButton = new QPushButton(centralWidget);
        ouvrirButton->setObjectName(QStringLiteral("ouvrirButton"));
        ouvrirButton->setGeometry(QRect(950, 550, 81, 23));
        ouvrirButton->setStyleSheet(QStringLiteral("width:15px;height:15px;border-radius:7.5px;border:2px groove gray;"));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1248, 21));
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
        menuFichier->addSeparator();
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
        label_4->setText(QApplication::translate("MainWindow", "D\303\251but:", 0));
        debutLabel->setText(QApplication::translate("MainWindow", "0", 0));
        label_5->setText(QApplication::translate("MainWindow", "Fin:", 0));
        finLabel->setText(QApplication::translate("MainWindow", "0", 0));
        savefinButton->setText(QApplication::translate("MainWindow", "Sauvegarde ", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Modalit\303\251", 0));
        visualiserButton->setText(QApplication::translate("MainWindow", "Visualiser", 0));
        traiterButton->setText(QApplication::translate("MainWindow", "Traiter", 0));
        ouvrirButton->setText(QApplication::translate("MainWindow", "Ouvrir", 0));
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
