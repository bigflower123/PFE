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
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_InformationDialog
{
public:

    void setupUi(QDialog *InformationDialog)
    {
        if (InformationDialog->objectName().isEmpty())
            InformationDialog->setObjectName(QStringLiteral("InformationDialog"));
        InformationDialog->resize(400, 300);

        retranslateUi(InformationDialog);

        QMetaObject::connectSlotsByName(InformationDialog);
    } // setupUi

    void retranslateUi(QDialog *InformationDialog)
    {
        InformationDialog->setWindowTitle(QApplication::translate("InformationDialog", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class InformationDialog: public Ui_InformationDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INFORMATIONDIALOG_H
