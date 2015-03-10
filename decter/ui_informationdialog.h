/********************************************************************************
** Form generated from reading UI file 'informationdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INFORMATIONDIALOG_H
#define UI_INFORMATIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InformationDialog
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_4;
    QLabel *bluehistLabel;
    QLabel *greenhistLabel;
    QLabel *redhistLabel;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_3;
    QLabel *redlabel;
    QLabel *redminLabel;
    QLabel *redmaxLabel;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *greenlabel;
    QLabel *greenminLabel;
    QLabel *greenmaxLabel;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout;
    QLabel *bluelabel;
    QLabel *blueminLabel;
    QLabel *bluemaxLabel;
    QPushButton *showButton;

    void setupUi(QDialog *InformationDialog)
    {
        if (InformationDialog->objectName().isEmpty())
            InformationDialog->setObjectName(QStringLiteral("InformationDialog"));
        InformationDialog->resize(733, 240);
        layoutWidget = new QWidget(InformationDialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 30, 691, 121));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        bluehistLabel = new QLabel(layoutWidget);
        bluehistLabel->setObjectName(QStringLiteral("bluehistLabel"));
        bluehistLabel->setStyleSheet(QStringLiteral("Background-color: #000;"));

        horizontalLayout_4->addWidget(bluehistLabel);

        greenhistLabel = new QLabel(layoutWidget);
        greenhistLabel->setObjectName(QStringLiteral("greenhistLabel"));
        greenhistLabel->setStyleSheet(QStringLiteral("Background-color: #000;"));

        horizontalLayout_4->addWidget(greenhistLabel);

        redhistLabel = new QLabel(layoutWidget);
        redhistLabel->setObjectName(QStringLiteral("redhistLabel"));
        redhistLabel->setStyleSheet(QStringLiteral("Background-color: #000;"));

        horizontalLayout_4->addWidget(redhistLabel);

        layoutWidget1 = new QWidget(InformationDialog);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(500, 160, 201, 16));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        redlabel = new QLabel(layoutWidget1);
        redlabel->setObjectName(QStringLiteral("redlabel"));

        horizontalLayout_3->addWidget(redlabel);

        redminLabel = new QLabel(layoutWidget1);
        redminLabel->setObjectName(QStringLiteral("redminLabel"));

        horizontalLayout_3->addWidget(redminLabel);

        redmaxLabel = new QLabel(layoutWidget1);
        redmaxLabel->setObjectName(QStringLiteral("redmaxLabel"));

        horizontalLayout_3->addWidget(redmaxLabel);

        layoutWidget2 = new QWidget(InformationDialog);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(260, 160, 211, 16));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        greenlabel = new QLabel(layoutWidget2);
        greenlabel->setObjectName(QStringLiteral("greenlabel"));

        horizontalLayout_2->addWidget(greenlabel);

        greenminLabel = new QLabel(layoutWidget2);
        greenminLabel->setObjectName(QStringLiteral("greenminLabel"));

        horizontalLayout_2->addWidget(greenminLabel);

        greenmaxLabel = new QLabel(layoutWidget2);
        greenmaxLabel->setObjectName(QStringLiteral("greenmaxLabel"));

        horizontalLayout_2->addWidget(greenmaxLabel);

        layoutWidget3 = new QWidget(InformationDialog);
        layoutWidget3->setObjectName(QStringLiteral("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(20, 160, 221, 16));
        horizontalLayout = new QHBoxLayout(layoutWidget3);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        bluelabel = new QLabel(layoutWidget3);
        bluelabel->setObjectName(QStringLiteral("bluelabel"));

        horizontalLayout->addWidget(bluelabel);

        blueminLabel = new QLabel(layoutWidget3);
        blueminLabel->setObjectName(QStringLiteral("blueminLabel"));

        horizontalLayout->addWidget(blueminLabel);

        bluemaxLabel = new QLabel(layoutWidget3);
        bluemaxLabel->setObjectName(QStringLiteral("bluemaxLabel"));

        horizontalLayout->addWidget(bluemaxLabel);

        showButton = new QPushButton(InformationDialog);
        showButton->setObjectName(QStringLiteral("showButton"));
        showButton->setGeometry(QRect(30, 200, 75, 23));

        retranslateUi(InformationDialog);

        QMetaObject::connectSlotsByName(InformationDialog);
    } // setupUi

    void retranslateUi(QDialog *InformationDialog)
    {
        InformationDialog->setWindowTitle(QApplication::translate("InformationDialog", "Information object", 0));
        bluehistLabel->setText(QString());
        greenhistLabel->setText(QString());
        redhistLabel->setText(QString());
        redlabel->setText(QApplication::translate("InformationDialog", "Red:", 0));
        redminLabel->setText(QApplication::translate("InformationDialog", "R1", 0));
        redmaxLabel->setText(QApplication::translate("InformationDialog", "R2", 0));
        greenlabel->setText(QApplication::translate("InformationDialog", "Green:", 0));
        greenminLabel->setText(QApplication::translate("InformationDialog", "G1", 0));
        greenmaxLabel->setText(QApplication::translate("InformationDialog", "G2", 0));
        bluelabel->setText(QApplication::translate("InformationDialog", "Blue:", 0));
        blueminLabel->setText(QApplication::translate("InformationDialog", "B1", 0));
        bluemaxLabel->setText(QApplication::translate("InformationDialog", "B2", 0));
        showButton->setText(QApplication::translate("InformationDialog", "Show", 0));
    } // retranslateUi

};

namespace Ui {
    class InformationDialog: public Ui_InformationDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INFORMATIONDIALOG_H
