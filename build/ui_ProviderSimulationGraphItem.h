/********************************************************************************
** Form generated from reading UI file 'ProviderSimulationGraphItem.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROVIDERSIMULATIONGRAPHITEM_H
#define UI_PROVIDERSIMULATIONGRAPHITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_ProviderSimulationGraphItem
{
public:
    QVBoxLayout *verticalLayout;
    QCustomPlot *widget;

    void setupUi(QWidget *ProviderSimulationGraphItem)
    {
        if (ProviderSimulationGraphItem->objectName().isEmpty())
            ProviderSimulationGraphItem->setObjectName(QStringLiteral("ProviderSimulationGraphItem"));
        ProviderSimulationGraphItem->resize(400, 300);
        verticalLayout = new QVBoxLayout(ProviderSimulationGraphItem);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        widget = new QCustomPlot(ProviderSimulationGraphItem);
        widget->setObjectName(QStringLiteral("widget"));

        verticalLayout->addWidget(widget);


        retranslateUi(ProviderSimulationGraphItem);

        QMetaObject::connectSlotsByName(ProviderSimulationGraphItem);
    } // setupUi

    void retranslateUi(QWidget *ProviderSimulationGraphItem)
    {
        ProviderSimulationGraphItem->setWindowTitle(QApplication::translate("ProviderSimulationGraphItem", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ProviderSimulationGraphItem: public Ui_ProviderSimulationGraphItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROVIDERSIMULATIONGRAPHITEM_H
