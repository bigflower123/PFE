/********************************************************************************
** Form generated from reading UI file 'deplacementmaxdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEPLACEMENTMAXDIALOG_H
#define UI_DEPLACEMENTMAXDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_DeplacementMaxDialog
{
public:
    QLabel *label;
    QLineEdit *deplacementlineEdit;
    QPushButton *OkButton;

    void setupUi(QDialog *DeplacementMaxDialog)
    {
        if (DeplacementMaxDialog->objectName().isEmpty())
            DeplacementMaxDialog->setObjectName(QStringLiteral("DeplacementMaxDialog"));
        DeplacementMaxDialog->resize(277, 121);
        label = new QLabel(DeplacementMaxDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(9, 27, 89, 16));
        deplacementlineEdit = new QLineEdit(DeplacementMaxDialog);
        deplacementlineEdit->setObjectName(QStringLiteral("deplacementlineEdit"));
        deplacementlineEdit->setGeometry(QRect(120, 30, 133, 20));
        OkButton = new QPushButton(DeplacementMaxDialog);
        OkButton->setObjectName(QStringLiteral("OkButton"));
        OkButton->setGeometry(QRect(80, 70, 75, 23));

        retranslateUi(DeplacementMaxDialog);

        QMetaObject::connectSlotsByName(DeplacementMaxDialog);
    } // setupUi

    void retranslateUi(QDialog *DeplacementMaxDialog)
    {
        DeplacementMaxDialog->setWindowTitle(QApplication::translate("DeplacementMaxDialog", "D\303\251placement Max", 0));
        label->setText(QApplication::translate("DeplacementMaxDialog", "D\303\251placement Max:", 0));
        OkButton->setText(QApplication::translate("DeplacementMaxDialog", "Confirme", 0));
    } // retranslateUi

};

namespace Ui {
    class DeplacementMaxDialog: public Ui_DeplacementMaxDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEPLACEMENTMAXDIALOG_H
