/********************************************************************************
** Form generated from reading UI file 'WalletListWidgetItem.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WALLETLISTWIDGETITEM_H
#define UI_WALLETLISTWIDGETITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WalletListWidgetItem
{
public:
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit_token;
    QLineEdit *lineEdit_quantity;

    void setupUi(QWidget *WalletListWidgetItem)
    {
        if (WalletListWidgetItem->objectName().isEmpty())
            WalletListWidgetItem->setObjectName(QStringLiteral("WalletListWidgetItem"));
        WalletListWidgetItem->resize(286, 47);
        WalletListWidgetItem->setStyleSheet(QStringLiteral(""));
        horizontalLayout_2 = new QHBoxLayout(WalletListWidgetItem);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        lineEdit_token = new QLineEdit(WalletListWidgetItem);
        lineEdit_token->setObjectName(QStringLiteral("lineEdit_token"));
        lineEdit_token->setStyleSheet(QStringLiteral(""));
        lineEdit_token->setReadOnly(true);

        horizontalLayout->addWidget(lineEdit_token);

        lineEdit_quantity = new QLineEdit(WalletListWidgetItem);
        lineEdit_quantity->setObjectName(QStringLiteral("lineEdit_quantity"));
        lineEdit_quantity->setStyleSheet(QStringLiteral(""));
        lineEdit_quantity->setReadOnly(true);

        horizontalLayout->addWidget(lineEdit_quantity);


        horizontalLayout_2->addLayout(horizontalLayout);


        retranslateUi(WalletListWidgetItem);

        QMetaObject::connectSlotsByName(WalletListWidgetItem);
    } // setupUi

    void retranslateUi(QWidget *WalletListWidgetItem)
    {
        WalletListWidgetItem->setWindowTitle(QApplication::translate("WalletListWidgetItem", "Form", Q_NULLPTR));
        lineEdit_token->setText(QApplication::translate("WalletListWidgetItem", "Token", Q_NULLPTR));
        lineEdit_quantity->setText(QApplication::translate("WalletListWidgetItem", "100000", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class WalletListWidgetItem: public Ui_WalletListWidgetItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WALLETLISTWIDGETITEM_H
