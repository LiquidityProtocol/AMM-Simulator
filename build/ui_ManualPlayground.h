/********************************************************************************
** Form generated from reading UI file 'ManualPlayground.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MANUALPLAYGROUND_H
#define UI_MANUALPLAYGROUND_H

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

class Ui_ManualPlayground
{
public:
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit;
    QPushButton *create_account_pushButton;
    QListWidget *listWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QPushButton *create_token_pushButton;
    QListWidget *listWidget_2;
    QVBoxLayout *verticalLayout_pool;
    QLabel *label_pool;
    QListWidget *listWidget_pool;

    void setupUi(QWidget *ManualPlayground)
    {
        if (ManualPlayground->objectName().isEmpty())
            ManualPlayground->setObjectName(QStringLiteral("ManualPlayground"));
        ManualPlayground->resize(1006, 701);
        horizontalLayout_3 = new QHBoxLayout(ManualPlayground);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        lineEdit = new QLineEdit(ManualPlayground);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        create_account_pushButton = new QPushButton(ManualPlayground);
        create_account_pushButton->setObjectName(QStringLiteral("create_account_pushButton"));

        horizontalLayout->addWidget(create_account_pushButton);


        verticalLayout_2->addLayout(horizontalLayout);

        listWidget = new QListWidget(ManualPlayground);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setStyleSheet(QStringLiteral(""));

        verticalLayout_2->addWidget(listWidget);


        horizontalLayout_3->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        lineEdit_2 = new QLineEdit(ManualPlayground);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        horizontalLayout_2->addWidget(lineEdit_2);

        lineEdit_3 = new QLineEdit(ManualPlayground);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));

        horizontalLayout_2->addWidget(lineEdit_3);

        create_token_pushButton = new QPushButton(ManualPlayground);
        create_token_pushButton->setObjectName(QStringLiteral("create_token_pushButton"));

        horizontalLayout_2->addWidget(create_token_pushButton);


        verticalLayout->addLayout(horizontalLayout_2);

        listWidget_2 = new QListWidget(ManualPlayground);
        listWidget_2->setObjectName(QStringLiteral("listWidget_2"));
        listWidget_2->setStyleSheet(QStringLiteral(""));

        verticalLayout->addWidget(listWidget_2);


        horizontalLayout_3->addLayout(verticalLayout);

        verticalLayout_pool = new QVBoxLayout();
        verticalLayout_pool->setObjectName(QStringLiteral("verticalLayout_pool"));
        verticalLayout_pool->setContentsMargins(0, -1, -1, -1);
        label_pool = new QLabel(ManualPlayground);
        label_pool->setObjectName(QStringLiteral("label_pool"));

        verticalLayout_pool->addWidget(label_pool);

        listWidget_pool = new QListWidget(ManualPlayground);
        listWidget_pool->setObjectName(QStringLiteral("listWidget_pool"));

        verticalLayout_pool->addWidget(listWidget_pool);


        horizontalLayout_3->addLayout(verticalLayout_pool);


        retranslateUi(ManualPlayground);

        QMetaObject::connectSlotsByName(ManualPlayground);
    } // setupUi

    void retranslateUi(QWidget *ManualPlayground)
    {
        ManualPlayground->setWindowTitle(QApplication::translate("ManualPlayground", "Form", Q_NULLPTR));
        lineEdit->setPlaceholderText(QApplication::translate("ManualPlayground", "Enter account name here", Q_NULLPTR));
        create_account_pushButton->setText(QApplication::translate("ManualPlayground", "Create A New Account", Q_NULLPTR));
        lineEdit_2->setText(QString());
        lineEdit_2->setPlaceholderText(QApplication::translate("ManualPlayground", "Enter token name here", Q_NULLPTR));
        lineEdit_3->setPlaceholderText(QApplication::translate("ManualPlayground", "Enter token price here", Q_NULLPTR));
        create_token_pushButton->setText(QApplication::translate("ManualPlayground", "Create A New Token", Q_NULLPTR));
        label_pool->setText(QApplication::translate("ManualPlayground", "Pool Information", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ManualPlayground: public Ui_ManualPlayground {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MANUALPLAYGROUND_H
