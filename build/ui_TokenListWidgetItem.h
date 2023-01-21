/********************************************************************************
** Form generated from reading UI file 'TokenListWidgetItem.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TOKENLISTWIDGETITEM_H
#define UI_TOKENLISTWIDGETITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TokenListWidgetItem
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineEdit_2;

    void setupUi(QWidget *TokenListWidgetItem)
    {
        if (TokenListWidgetItem->objectName().isEmpty())
            TokenListWidgetItem->setObjectName(QStringLiteral("TokenListWidgetItem"));
        TokenListWidgetItem->resize(223, 72);
        verticalLayout = new QVBoxLayout(TokenListWidgetItem);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(TokenListWidgetItem);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(TokenListWidgetItem);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setReadOnly(true);

        horizontalLayout->addWidget(lineEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(TokenListWidgetItem);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        lineEdit_2 = new QLineEdit(TokenListWidgetItem);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setReadOnly(true);

        horizontalLayout_2->addWidget(lineEdit_2);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(TokenListWidgetItem);

        QMetaObject::connectSlotsByName(TokenListWidgetItem);
    } // setupUi

    void retranslateUi(QWidget *TokenListWidgetItem)
    {
        TokenListWidgetItem->setWindowTitle(QApplication::translate("TokenListWidgetItem", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("TokenListWidgetItem", "Token name", Q_NULLPTR));
        label_2->setText(QApplication::translate("TokenListWidgetItem", "Price", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class TokenListWidgetItem: public Ui_TokenListWidgetItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TOKENLISTWIDGETITEM_H
