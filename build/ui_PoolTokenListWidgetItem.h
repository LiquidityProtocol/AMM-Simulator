/********************************************************************************
** Form generated from reading UI file 'PoolTokenListWidgetItem.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POOLTOKENLISTWIDGETITEM_H
#define UI_POOLTOKENLISTWIDGETITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PoolTokenListWidgetItem
{
public:
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit;
    QPushButton *pushButton;

    void setupUi(QWidget *PoolTokenListWidgetItem)
    {
        if (PoolTokenListWidgetItem->objectName().isEmpty())
            PoolTokenListWidgetItem->setObjectName(QStringLiteral("PoolTokenListWidgetItem"));
        PoolTokenListWidgetItem->resize(244, 45);
        horizontalLayout = new QHBoxLayout(PoolTokenListWidgetItem);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        lineEdit = new QLineEdit(PoolTokenListWidgetItem);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setReadOnly(true);

        horizontalLayout->addWidget(lineEdit);

        pushButton = new QPushButton(PoolTokenListWidgetItem);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);


        retranslateUi(PoolTokenListWidgetItem);

        QMetaObject::connectSlotsByName(PoolTokenListWidgetItem);
    } // setupUi

    void retranslateUi(QWidget *PoolTokenListWidgetItem)
    {
        PoolTokenListWidgetItem->setWindowTitle(QApplication::translate("PoolTokenListWidgetItem", "Form", Q_NULLPTR));
        pushButton->setText(QApplication::translate("PoolTokenListWidgetItem", "See more", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PoolTokenListWidgetItem: public Ui_PoolTokenListWidgetItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POOLTOKENLISTWIDGETITEM_H
