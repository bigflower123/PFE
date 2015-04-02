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
#include <QtWidgets/QListWidget>
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
    QLabel *commentlabel;
    QTextEdit *commenttextEdit;
    QPushButton *commentButton;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *R1label;
    QLabel *R2label;
    QLabel *V1label;
    QLabel *V2label;
    QLabel *B1label;
    QLabel *B2label;
    QListWidget *listWidget;
    QLabel *label_4;
    QLabel *debutLabel;
    QLabel *label_5;
    QLabel *finLabel;
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
        MainWindow->resize(1185, 706);
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
        playBtn->setGeometry(QRect(390, 590, 71, 21));
        playBtn->setStyleSheet(QStringLiteral("width:15px;height:15px;border-radius:7.5px;border:2px groove gray;"));
        videoSlider = new QSlider(centralWidget);
        videoSlider->setObjectName(QStringLiteral("videoSlider"));
        videoSlider->setGeometry(QRect(200, 560, 481, 20));
        videoSlider->setOrientation(Qt::Horizontal);
        currentLable = new QLabel(centralWidget);
        currentLable->setObjectName(QStringLiteral("currentLable"));
        currentLable->setGeometry(QRect(130, 560, 61, 16));
        totalLable = new QLabel(centralWidget);
        totalLable->setObjectName(QStringLiteral("totalLable"));
        totalLable->setGeometry(QRect(700, 560, 61, 16));
        forwardButton = new QPushButton(centralWidget);
        forwardButton->setObjectName(QStringLiteral("forwardButton"));
        forwardButton->setGeometry(QRect(770, 560, 40, 20));
        forwardButton->setStyleSheet(QStringLiteral("border-radius:7.5px;border:2px groove gray;"));
        backwardButton = new QPushButton(centralWidget);
        backwardButton->setObjectName(QStringLiteral("backwardButton"));
        backwardButton->setGeometry(QRect(80, 560, 40, 20));
        backwardButton->setStyleSheet(QStringLiteral("border-radius:7.5px;border:2px groove gray;"));
        debutButton = new QPushButton(centralWidget);
        debutButton->setObjectName(QStringLiteral("debutButton"));
        debutButton->setGeometry(QRect(200, 590, 75, 23));
        finButton = new QPushButton(centralWidget);
        finButton->setObjectName(QStringLiteral("finButton"));
        finButton->setGeometry(QRect(630, 580, 75, 23));
        trajectoirecheckBox = new QCheckBox(centralWidget);
        trajectoirecheckBox->setObjectName(QStringLiteral("trajectoirecheckBox"));
        trajectoirecheckBox->setGeometry(QRect(100, 590, 74, 17));
        quickbackwardButton = new QPushButton(centralWidget);
        quickbackwardButton->setObjectName(QStringLiteral("quickbackwardButton"));
        quickbackwardButton->setGeometry(QRect(20, 560, 50, 20));
        quickbackwardButton->setStyleSheet(QStringLiteral("border-radius:7.5px;border:2px groove gray;"));
        quickforwardButton = new QPushButton(centralWidget);
        quickforwardButton->setObjectName(QStringLiteral("quickforwardButton"));
        quickforwardButton->setGeometry(QRect(820, 560, 50, 20));
        quickforwardButton->setStyleSheet(QStringLiteral("border-radius:7.5px;border:2px groove gray;"));
        commentlabel = new QLabel(centralWidget);
        commentlabel->setObjectName(QStringLiteral("commentlabel"));
        commentlabel->setGeometry(QRect(900, 350, 67, 16));
        commenttextEdit = new QTextEdit(centralWidget);
        commenttextEdit->setObjectName(QStringLiteral("commenttextEdit"));
        commenttextEdit->setGeometry(QRect(900, 370, 261, 111));
        commentButton = new QPushButton(centralWidget);
        commentButton->setObjectName(QStringLiteral("commentButton"));
        commentButton->setGeometry(QRect(1070, 500, 75, 23));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(900, 540, 46, 13));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(900, 570, 46, 13));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(900, 600, 46, 13));
        R1label = new QLabel(centralWidget);
        R1label->setObjectName(QStringLiteral("R1label"));
        R1label->setGeometry(QRect(950, 540, 46, 13));
        R2label = new QLabel(centralWidget);
        R2label->setObjectName(QStringLiteral("R2label"));
        R2label->setGeometry(QRect(1020, 540, 46, 13));
        V1label = new QLabel(centralWidget);
        V1label->setObjectName(QStringLiteral("V1label"));
        V1label->setGeometry(QRect(950, 570, 46, 13));
        V2label = new QLabel(centralWidget);
        V2label->setObjectName(QStringLiteral("V2label"));
        V2label->setGeometry(QRect(1020, 570, 46, 13));
        B1label = new QLabel(centralWidget);
        B1label->setObjectName(QStringLiteral("B1label"));
        B1label->setGeometry(QRect(950, 600, 46, 13));
        B2label = new QLabel(centralWidget);
        B2label->setObjectName(QStringLiteral("B2label"));
        B2label->setGeometry(QRect(1020, 600, 46, 13));
        listWidget = new QListWidget(centralWidget);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(900, 10, 271, 321));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(160, 620, 46, 13));
        debutLabel = new QLabel(centralWidget);
        debutLabel->setObjectName(QStringLiteral("debutLabel"));
        debutLabel->setGeometry(QRect(220, 620, 71, 16));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(600, 620, 46, 13));
        finLabel = new QLabel(centralWidget);
        finLabel->setObjectName(QStringLiteral("finLabel"));
        finLabel->setGeometry(QRect(660, 620, 46, 13));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1185, 21));
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
        label->setText(QApplication::translate("MainWindow", "Rouge:", 0));
        label_2->setText(QApplication::translate("MainWindow", "Vert:", 0));
        label_3->setText(QApplication::translate("MainWindow", "Bleu:", 0));
        R1label->setText(QApplication::translate("MainWindow", "R1", 0));
        R2label->setText(QApplication::translate("MainWindow", "R2", 0));
        V1label->setText(QApplication::translate("MainWindow", "V1", 0));
        V2label->setText(QApplication::translate("MainWindow", "V2", 0));
        B1label->setText(QApplication::translate("MainWindow", "B1", 0));
        B2label->setText(QApplication::translate("MainWindow", "B2", 0));
        label_4->setText(QApplication::translate("MainWindow", "D\303\251but:", 0));
        debutLabel->setText(QApplication::translate("MainWindow", "0", 0));
        label_5->setText(QApplication::translate("MainWindow", "Fin:", 0));
        finLabel->setText(QApplication::translate("MainWindow", "0", 0));
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
