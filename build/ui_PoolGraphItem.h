/********************************************************************************
** Form generated from reading UI file 'PoolGraphItem.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POOLGRAPHITEM_H
#define UI_POOLGRAPHITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_PoolGraphItem
{
public:
    QGridLayout *gridLayout;
    QCustomPlot *widget;

    void setupUi(QWidget *PoolGraphItem)
    {
        if (PoolGraphItem->objectName().isEmpty())
            PoolGraphItem->setObjectName(QStringLiteral("PoolGraphItem"));
        PoolGraphItem->setWindowModality(Qt::NonModal);
        PoolGraphItem->setEnabled(true);
        PoolGraphItem->resize(433, 414);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PoolGraphItem->sizePolicy().hasHeightForWidth());
        PoolGraphItem->setSizePolicy(sizePolicy);
        PoolGraphItem->setMinimumSize(QSize(0, 400));
        gridLayout = new QGridLayout(PoolGraphItem);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        widget = new QCustomPlot(PoolGraphItem);
        widget->setObjectName(QStringLiteral("widget"));
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        widget->setMinimumSize(QSize(0, 300));

        gridLayout->addWidget(widget, 0, 0, 1, 1);


        retranslateUi(PoolGraphItem);

        QMetaObject::connectSlotsByName(PoolGraphItem);
    } // setupUi

    void retranslateUi(QWidget *PoolGraphItem)
    {
        PoolGraphItem->setWindowTitle(QApplication::translate("PoolGraphItem", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PoolGraphItem: public Ui_PoolGraphItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POOLGRAPHITEM_H
