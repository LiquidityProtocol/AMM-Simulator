/********************************************************************************
** Form generated from reading UI file 'MintDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MINTDIALOG_H
#define UI_MINTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_MintDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *comboBox;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QPushButton *pushButton;

    void setupUi(QDialog *MintDialog)
    {
        if (MintDialog->objectName().isEmpty())
            MintDialog->setObjectName(QStringLiteral("MintDialog"));
        MintDialog->resize(210, 123);
        MintDialog->setStyleSheet(QStringLiteral(""));
        MintDialog->setModal(true);
        verticalLayout = new QVBoxLayout(MintDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(MintDialog);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        comboBox = new QComboBox(MintDialog);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setStyleSheet(QStringLiteral(""));

        horizontalLayout->addWidget(comboBox);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(MintDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        lineEdit = new QLineEdit(MintDialog);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setStyleSheet(QStringLiteral(""));

        horizontalLayout_2->addWidget(lineEdit);


        verticalLayout->addLayout(horizontalLayout_2);

        pushButton = new QPushButton(MintDialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setStyleSheet(QStringLiteral(""));

        verticalLayout->addWidget(pushButton);


        retranslateUi(MintDialog);

        QMetaObject::connectSlotsByName(MintDialog);
    } // setupUi

    void retranslateUi(QDialog *MintDialog)
    {
        MintDialog->setWindowTitle(QApplication::translate("MintDialog", "Mint", Q_NULLPTR));
        label->setText(QApplication::translate("MintDialog", "Token", Q_NULLPTR));
        label_2->setText(QApplication::translate("MintDialog", "Quantity", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MintDialog", "Mint", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MintDialog: public Ui_MintDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MINTDIALOG_H
