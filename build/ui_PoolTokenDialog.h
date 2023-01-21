/********************************************************************************
** Form generated from reading UI file 'PoolTokenDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POOLTOKENDIALOG_H
#define UI_POOLTOKENDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_PoolTokenDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_share;
    QLineEdit *lineEdit_share;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_totalValue;
    QLineEdit *lineEdit_totalValue;

    void setupUi(QDialog *PoolTokenDialog)
    {
        if (PoolTokenDialog->objectName().isEmpty())
            PoolTokenDialog->setObjectName(QStringLiteral("PoolTokenDialog"));
        PoolTokenDialog->resize(223, 80);
        verticalLayout = new QVBoxLayout(PoolTokenDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_share = new QLabel(PoolTokenDialog);
        label_share->setObjectName(QStringLiteral("label_share"));

        horizontalLayout->addWidget(label_share);

        lineEdit_share = new QLineEdit(PoolTokenDialog);
        lineEdit_share->setObjectName(QStringLiteral("lineEdit_share"));
        lineEdit_share->setReadOnly(true);

        horizontalLayout->addWidget(lineEdit_share);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_totalValue = new QLabel(PoolTokenDialog);
        label_totalValue->setObjectName(QStringLiteral("label_totalValue"));

        horizontalLayout_2->addWidget(label_totalValue);

        lineEdit_totalValue = new QLineEdit(PoolTokenDialog);
        lineEdit_totalValue->setObjectName(QStringLiteral("lineEdit_totalValue"));
        lineEdit_totalValue->setReadOnly(true);

        horizontalLayout_2->addWidget(lineEdit_totalValue);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(PoolTokenDialog);

        QMetaObject::connectSlotsByName(PoolTokenDialog);
    } // setupUi

    void retranslateUi(QDialog *PoolTokenDialog)
    {
        PoolTokenDialog->setWindowTitle(QApplication::translate("PoolTokenDialog", "Dialog", Q_NULLPTR));
        label_share->setText(QApplication::translate("PoolTokenDialog", "Share (%)", Q_NULLPTR));
        label_totalValue->setText(QApplication::translate("PoolTokenDialog", "Total value", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PoolTokenDialog: public Ui_PoolTokenDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POOLTOKENDIALOG_H
