/********************************************************************************
** Form generated from reading UI file 'ArbitrageurSimulationGraphItem.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ARBITRAGEURSIMULATIONGRAPHITEM_H
#define UI_ARBITRAGEURSIMULATIONGRAPHITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_ArbitrageurSimulationGraphItem
{
public:
    QGridLayout *gridLayout;
    QCustomPlot *widget;

    void setupUi(QWidget *ArbitrageurSimulationGraphItem)
    {
        if (ArbitrageurSimulationGraphItem->objectName().isEmpty())
            ArbitrageurSimulationGraphItem->setObjectName(QStringLiteral("ArbitrageurSimulationGraphItem"));
        ArbitrageurSimulationGraphItem->setWindowModality(Qt::NonModal);
        ArbitrageurSimulationGraphItem->setEnabled(true);
        ArbitrageurSimulationGraphItem->resize(433, 414);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ArbitrageurSimulationGraphItem->sizePolicy().hasHeightForWidth());
        ArbitrageurSimulationGraphItem->setSizePolicy(sizePolicy);
        ArbitrageurSimulationGraphItem->setMinimumSize(QSize(0, 400));
        gridLayout = new QGridLayout(ArbitrageurSimulationGraphItem);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        widget = new QCustomPlot(ArbitrageurSimulationGraphItem);
        widget->setObjectName(QStringLiteral("widget"));
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        widget->setMinimumSize(QSize(0, 300));

        gridLayout->addWidget(widget, 0, 0, 1, 1);


        retranslateUi(ArbitrageurSimulationGraphItem);

        QMetaObject::connectSlotsByName(ArbitrageurSimulationGraphItem);
    } // setupUi

    void retranslateUi(QWidget *ArbitrageurSimulationGraphItem)
    {
        ArbitrageurSimulationGraphItem->setWindowTitle(QApplication::translate("ArbitrageurSimulationGraphItem", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ArbitrageurSimulationGraphItem: public Ui_ArbitrageurSimulationGraphItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ARBITRAGEURSIMULATIONGRAPHITEM_H
