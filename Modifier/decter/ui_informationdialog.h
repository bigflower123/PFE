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
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_3;
    QLabel *redlabel;
    QLabel *redminLabel;
    QLabel *redmaxLabel;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QLabel *greenlabel;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout;
    QLabel *bluelabel;
    QLabel *blueminLabel;
    QLabel *bluemaxLabel;
    QLabel *greenminLabel;
    QLabel *greenmaxLabel;
    QLabel *bluehistLabel;
    QLabel *greenhistLabel;
    QLabel *redhistLabel;

    void setupUi(QDialog *InformationDialog)
    {
        if (InformationDialog->objectName().isEmpty())
            InformationDialog->setObjectName(QStringLiteral("InformationDialog"));
        InformationDialog->resize(735, 298);
        layoutWidget = new QWidget(InformationDialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(510, 260, 201, 16));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        redlabel = new QLabel(layoutWidget);
        redlabel->setObjectName(QStringLiteral("redlabel"));

        horizontalLayout_3->addWidget(redlabel);

        redminLabel = new QLabel(layoutWidget);
        redminLabel->setObjectName(QStringLiteral("redminLabel"));

        horizontalLayout_3->addWidget(redminLabel);

        redmaxLabel = new QLabel(layoutWidget);
        redmaxLabel->setObjectName(QStringLiteral("redmaxLabel"));

        horizontalLayout_3->addWidget(redmaxLabel);

        layoutWidget1 = new QWidget(InformationDialog);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(270, 260, 211, 16));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        greenlabel = new QLabel(layoutWidget1);
        greenlabel->setObjectName(QStringLiteral("greenlabel"));

        horizontalLayout_2->addWidget(greenlabel);

        layoutWidget2 = new QWidget(InformationDialog);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(20, 260, 221, 16));
        horizontalLayout = new QHBoxLayout(layoutWidget2);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        bluelabel = new QLabel(layoutWidget2);
        bluelabel->setObjectName(QStringLiteral("bluelabel"));

        horizontalLayout->addWidget(bluelabel);

        blueminLabel = new QLabel(layoutWidget2);
        blueminLabel->setObjectName(QStringLiteral("blueminLabel"));

        horizontalLayout->addWidget(blueminLabel);

        bluemaxLabel = new QLabel(layoutWidget2);
        bluemaxLabel->setObjectName(QStringLiteral("bluemaxLabel"));

        horizontalLayout->addWidget(bluemaxLabel);

        greenminLabel = new QLabel(InformationDialog);
        greenminLabel->setObjectName(QStringLiteral("greenminLabel"));
        greenminLabel->setGeometry(QRect(330, 260, 65, 14));
        greenmaxLabel = new QLabel(InformationDialog);
        greenmaxLabel->setObjectName(QStringLiteral("greenmaxLabel"));
        greenmaxLabel->setGeometry(QRect(400, 260, 101, 14));
        bluehistLabel = new QLabel(InformationDialog);
        bluehistLabel->setObjectName(QStringLiteral("bluehistLabel"));
        bluehistLabel->setGeometry(QRect(21, 31, 212, 150));
        bluehistLabel->setStyleSheet(QStringLiteral("Background-color: #000;"));
        greenhistLabel = new QLabel(InformationDialog);
        greenhistLabel->setObjectName(QStringLiteral("greenhistLabel"));
        greenhistLabel->setGeometry(QRect(256, 31, 212, 150));
        greenhistLabel->setStyleSheet(QStringLiteral("Background-color: #000;"));
        redhistLabel = new QLabel(InformationDialog);
        redhistLabel->setObjectName(QStringLiteral("redhistLabel"));
        redhistLabel->setGeometry(QRect(491, 31, 212, 150));
        redhistLabel->setStyleSheet(QStringLiteral("Background-color: #000;"));

        retranslateUi(InformationDialog);

        QMetaObject::connectSlotsByName(InformationDialog);
    } // setupUi

    void retranslateUi(QDialog *InformationDialog)
    {
        InformationDialog->setWindowTitle(QApplication::translate("InformationDialog", "Information object", 0));
        redlabel->setText(QApplication::translate("InformationDialog", "Red:", 0));
        redminLabel->setText(QApplication::translate("InformationDialog", "R1", 0));
        redmaxLabel->setText(QApplication::translate("InformationDialog", "R2", 0));
        greenlabel->setText(QApplication::translate("InformationDialog", "Green:", 0));
        bluelabel->setText(QApplication::translate("InformationDialog", "Blue:", 0));
        blueminLabel->setText(QApplication::translate("InformationDialog", "B1", 0));
        bluemaxLabel->setText(QApplication::translate("InformationDialog", "B2", 0));
        greenminLabel->setText(QApplication::translate("InformationDialog", "G1", 0));
        greenmaxLabel->setText(QApplication::translate("InformationDialog", "G2", 0));
        bluehistLabel->setText(QString());
        greenhistLabel->setText(QString());
        redhistLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class InformationDialog: public Ui_InformationDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INFORMATIONDIALOG_H
