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
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InformationDialog
{
public:
    QWidget *widget;
    QHBoxLayout *horizontalLayout_4;
    QLabel *bluehistLabel;
    QLabel *greenhistLabel;
    QLabel *redhistLabel;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout_3;
    QLabel *redlabel;
    QLabel *redminLabel;
    QLabel *redmaxLabel;
    QWidget *widget2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *greenlabel;
    QLabel *greenminLabel;
    QLabel *greenmaxLabel;
    QWidget *widget3;
    QHBoxLayout *horizontalLayout;
    QLabel *bluelabel;
    QLabel *blueminLabel;
    QLabel *bluemaxLabel;

    void setupUi(QDialog *InformationDialog)
    {
        if (InformationDialog->objectName().isEmpty())
            InformationDialog->setObjectName(QStringLiteral("InformationDialog"));
        InformationDialog->resize(706, 206);
        widget = new QWidget(InformationDialog);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(20, 30, 691, 121));
        horizontalLayout_4 = new QHBoxLayout(widget);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        bluehistLabel = new QLabel(widget);
        bluehistLabel->setObjectName(QStringLiteral("bluehistLabel"));
        bluehistLabel->setStyleSheet(QStringLiteral("Background-color: #000;"));

        horizontalLayout_4->addWidget(bluehistLabel);

        greenhistLabel = new QLabel(widget);
        greenhistLabel->setObjectName(QStringLiteral("greenhistLabel"));
        greenhistLabel->setStyleSheet(QStringLiteral("Background-color: #000;"));

        horizontalLayout_4->addWidget(greenhistLabel);

        redhistLabel = new QLabel(widget);
        redhistLabel->setObjectName(QStringLiteral("redhistLabel"));
        redhistLabel->setStyleSheet(QStringLiteral("Background-color: #000;"));

        horizontalLayout_4->addWidget(redhistLabel);

        widget1 = new QWidget(InformationDialog);
        widget1->setObjectName(QStringLiteral("widget1"));
        widget1->setGeometry(QRect(500, 160, 201, 16));
        horizontalLayout_3 = new QHBoxLayout(widget1);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        redlabel = new QLabel(widget1);
        redlabel->setObjectName(QStringLiteral("redlabel"));

        horizontalLayout_3->addWidget(redlabel);

        redminLabel = new QLabel(widget1);
        redminLabel->setObjectName(QStringLiteral("redminLabel"));

        horizontalLayout_3->addWidget(redminLabel);

        redmaxLabel = new QLabel(widget1);
        redmaxLabel->setObjectName(QStringLiteral("redmaxLabel"));

        horizontalLayout_3->addWidget(redmaxLabel);

        widget2 = new QWidget(InformationDialog);
        widget2->setObjectName(QStringLiteral("widget2"));
        widget2->setGeometry(QRect(260, 160, 211, 16));
        horizontalLayout_2 = new QHBoxLayout(widget2);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        greenlabel = new QLabel(widget2);
        greenlabel->setObjectName(QStringLiteral("greenlabel"));

        horizontalLayout_2->addWidget(greenlabel);

        greenminLabel = new QLabel(widget2);
        greenminLabel->setObjectName(QStringLiteral("greenminLabel"));

        horizontalLayout_2->addWidget(greenminLabel);

        greenmaxLabel = new QLabel(widget2);
        greenmaxLabel->setObjectName(QStringLiteral("greenmaxLabel"));

        horizontalLayout_2->addWidget(greenmaxLabel);

        widget3 = new QWidget(InformationDialog);
        widget3->setObjectName(QStringLiteral("widget3"));
        widget3->setGeometry(QRect(20, 160, 221, 16));
        horizontalLayout = new QHBoxLayout(widget3);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        bluelabel = new QLabel(widget3);
        bluelabel->setObjectName(QStringLiteral("bluelabel"));

        horizontalLayout->addWidget(bluelabel);

        blueminLabel = new QLabel(widget3);
        blueminLabel->setObjectName(QStringLiteral("blueminLabel"));

        horizontalLayout->addWidget(blueminLabel);

        bluemaxLabel = new QLabel(widget3);
        bluemaxLabel->setObjectName(QStringLiteral("bluemaxLabel"));

        horizontalLayout->addWidget(bluemaxLabel);


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
    } // retranslateUi

};

namespace Ui {
    class InformationDialog: public Ui_InformationDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INFORMATIONDIALOG_H
