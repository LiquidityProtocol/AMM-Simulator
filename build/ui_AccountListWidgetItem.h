/********************************************************************************
** Form generated from reading UI file 'AccountListWidgetItem.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ACCOUNTLISTWIDGETITEM_H
#define UI_ACCOUNTLISTWIDGETITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AccountListWidgetItem
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit_2;
    QListWidget *listWidget;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *mint_pushButton;
    QPushButton *trade_pushButton;
    QPushButton *provide_pushButton;
    QPushButton *withdraw_pushButton;

    void setupUi(QWidget *AccountListWidgetItem)
    {
        if (AccountListWidgetItem->objectName().isEmpty())
            AccountListWidgetItem->setObjectName(QStringLiteral("AccountListWidgetItem"));
        AccountListWidgetItem->resize(280, 189);
        AccountListWidgetItem->setMinimumSize(QSize(280, 0));
        AccountListWidgetItem->setStyleSheet(QStringLiteral(""));
        verticalLayout = new QVBoxLayout(AccountListWidgetItem);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(AccountListWidgetItem);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setStyleSheet(QStringLiteral(""));

        horizontalLayout_2->addWidget(label_2);

        lineEdit = new QLineEdit(AccountListWidgetItem);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setStyleSheet(QStringLiteral(""));
        lineEdit->setFrame(true);
        lineEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEdit->setReadOnly(true);

        horizontalLayout_2->addWidget(lineEdit);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(AccountListWidgetItem);
        label->setObjectName(QStringLiteral("label"));
        label->setStyleSheet(QStringLiteral(""));

        horizontalLayout->addWidget(label);

        lineEdit_2 = new QLineEdit(AccountListWidgetItem);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setStyleSheet(QStringLiteral(""));
        lineEdit_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEdit_2->setReadOnly(true);

        horizontalLayout->addWidget(lineEdit_2);


        verticalLayout->addLayout(horizontalLayout);

        listWidget = new QListWidget(AccountListWidgetItem);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setMinimumSize(QSize(244, 57));
        listWidget->setStyleSheet(QStringLiteral(""));

        verticalLayout->addWidget(listWidget);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        mint_pushButton = new QPushButton(AccountListWidgetItem);
        mint_pushButton->setObjectName(QStringLiteral("mint_pushButton"));
        mint_pushButton->setStyleSheet(QStringLiteral("color: rgb(255, 0, 8);"));

        horizontalLayout_3->addWidget(mint_pushButton);

        trade_pushButton = new QPushButton(AccountListWidgetItem);
        trade_pushButton->setObjectName(QStringLiteral("trade_pushButton"));
        trade_pushButton->setStyleSheet(QStringLiteral("color: rgb(255, 0, 8);"));

        horizontalLayout_3->addWidget(trade_pushButton);

        provide_pushButton = new QPushButton(AccountListWidgetItem);
        provide_pushButton->setObjectName(QStringLiteral("provide_pushButton"));
        provide_pushButton->setStyleSheet(QStringLiteral("color: rgb(255, 0, 8);"));

        horizontalLayout_3->addWidget(provide_pushButton);

        withdraw_pushButton = new QPushButton(AccountListWidgetItem);
        withdraw_pushButton->setObjectName(QStringLiteral("withdraw_pushButton"));
        withdraw_pushButton->setStyleSheet(QStringLiteral("color: rgb(255, 0, 8);"));

        horizontalLayout_3->addWidget(withdraw_pushButton);


        verticalLayout->addLayout(horizontalLayout_3);

        QWidget::setTabOrder(lineEdit_2, lineEdit);
        QWidget::setTabOrder(lineEdit, listWidget);

        retranslateUi(AccountListWidgetItem);

        QMetaObject::connectSlotsByName(AccountListWidgetItem);
    } // setupUi

    void retranslateUi(QWidget *AccountListWidgetItem)
    {
        AccountListWidgetItem->setWindowTitle(QApplication::translate("AccountListWidgetItem", "Form", Q_NULLPTR));
        label_2->setText(QApplication::translate("AccountListWidgetItem", "Account name", Q_NULLPTR));
        lineEdit->setText(QString());
        label->setText(QApplication::translate("AccountListWidgetItem", "$", Q_NULLPTR));
        lineEdit_2->setText(QString());
        mint_pushButton->setText(QApplication::translate("AccountListWidgetItem", "Mint", Q_NULLPTR));
        trade_pushButton->setText(QApplication::translate("AccountListWidgetItem", "Trade", Q_NULLPTR));
        provide_pushButton->setText(QApplication::translate("AccountListWidgetItem", "Provide", Q_NULLPTR));
        withdraw_pushButton->setText(QApplication::translate("AccountListWidgetItem", "Withdraw", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class AccountListWidgetItem: public Ui_AccountListWidgetItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ACCOUNTLISTWIDGETITEM_H
