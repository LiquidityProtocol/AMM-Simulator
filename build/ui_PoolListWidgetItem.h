/********************************************************************************
** Form generated from reading UI file 'PoolListWidgetItem.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POOLLISTWIDGETITEM_H
#define UI_POOLLISTWIDGETITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_PoolListWidgetItem
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_poolName;
    QLabel *label_poolName;
    QHBoxLayout *horizontalLayout_protocol_fee;
    QLabel *label_protocol;
    QLineEdit *lineEdit_protocol;
    QLabel *label_poolFee;
    QLineEdit *lineEdit_poolFee;
    QVBoxLayout *verticalLayout_slippage;
    QLabel *label_slippage_title;
    QTableWidget *tableWidget_slippage;
    QHBoxLayout *horizontalLayout_slippage;
    QLabel *label_slippage;
    QLineEdit *lineEdit_slippage;
    QHBoxLayout *horizontalLayout_spotPrice;
    QLabel *label_spotPrice;
    QComboBox *comboBox_spotPrice;
    QHBoxLayout *horizontalLayout_poolTable;
    QTableWidget *tableWidget_poolInformation;
    QHBoxLayout *horizontalLayout_secondToken;
    QLabel *label_secondToken;
    QComboBox *comboBox_secondToken;
    QVBoxLayout *verticalLayout_2;
    QCustomPlot *widgetGraph;

    void setupUi(QWidget *PoolListWidgetItem)
    {
        if (PoolListWidgetItem->objectName().isEmpty())
            PoolListWidgetItem->setObjectName(QStringLiteral("PoolListWidgetItem"));
        PoolListWidgetItem->resize(400, 700);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PoolListWidgetItem->sizePolicy().hasHeightForWidth());
        PoolListWidgetItem->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(PoolListWidgetItem);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_poolName = new QHBoxLayout();
        horizontalLayout_poolName->setObjectName(QStringLiteral("horizontalLayout_poolName"));
        label_poolName = new QLabel(PoolListWidgetItem);
        label_poolName->setObjectName(QStringLiteral("label_poolName"));

        horizontalLayout_poolName->addWidget(label_poolName);


        verticalLayout->addLayout(horizontalLayout_poolName);

        horizontalLayout_protocol_fee = new QHBoxLayout();
        horizontalLayout_protocol_fee->setObjectName(QStringLiteral("horizontalLayout_protocol_fee"));
        horizontalLayout_protocol_fee->setSizeConstraint(QLayout::SetMinimumSize);
        label_protocol = new QLabel(PoolListWidgetItem);
        label_protocol->setObjectName(QStringLiteral("label_protocol"));

        horizontalLayout_protocol_fee->addWidget(label_protocol);

        lineEdit_protocol = new QLineEdit(PoolListWidgetItem);
        lineEdit_protocol->setObjectName(QStringLiteral("lineEdit_protocol"));
        lineEdit_protocol->setEnabled(false);

        horizontalLayout_protocol_fee->addWidget(lineEdit_protocol);

        label_poolFee = new QLabel(PoolListWidgetItem);
        label_poolFee->setObjectName(QStringLiteral("label_poolFee"));

        horizontalLayout_protocol_fee->addWidget(label_poolFee);

        lineEdit_poolFee = new QLineEdit(PoolListWidgetItem);
        lineEdit_poolFee->setObjectName(QStringLiteral("lineEdit_poolFee"));
        lineEdit_poolFee->setEnabled(false);

        horizontalLayout_protocol_fee->addWidget(lineEdit_poolFee);


        verticalLayout->addLayout(horizontalLayout_protocol_fee);

        verticalLayout_slippage = new QVBoxLayout();
        verticalLayout_slippage->setObjectName(QStringLiteral("verticalLayout_slippage"));
        verticalLayout_slippage->setContentsMargins(-1, -1, -1, 0);
        label_slippage_title = new QLabel(PoolListWidgetItem);
        label_slippage_title->setObjectName(QStringLiteral("label_slippage_title"));

        verticalLayout_slippage->addWidget(label_slippage_title);

        tableWidget_slippage = new QTableWidget(PoolListWidgetItem);
        if (tableWidget_slippage->columnCount() < 1)
            tableWidget_slippage->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_slippage->setHorizontalHeaderItem(0, __qtablewidgetitem);
        if (tableWidget_slippage->rowCount() < 2)
            tableWidget_slippage->setRowCount(2);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_slippage->setVerticalHeaderItem(0, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_slippage->setVerticalHeaderItem(1, __qtablewidgetitem2);
        tableWidget_slippage->setObjectName(QStringLiteral("tableWidget_slippage"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tableWidget_slippage->sizePolicy().hasHeightForWidth());
        tableWidget_slippage->setSizePolicy(sizePolicy1);
        tableWidget_slippage->setMaximumSize(QSize(16777215, 90));

        verticalLayout_slippage->addWidget(tableWidget_slippage);

        horizontalLayout_slippage = new QHBoxLayout();
        horizontalLayout_slippage->setObjectName(QStringLiteral("horizontalLayout_slippage"));
        horizontalLayout_slippage->setContentsMargins(-1, -1, -1, 0);
        label_slippage = new QLabel(PoolListWidgetItem);
        label_slippage->setObjectName(QStringLiteral("label_slippage"));

        horizontalLayout_slippage->addWidget(label_slippage);

        lineEdit_slippage = new QLineEdit(PoolListWidgetItem);
        lineEdit_slippage->setObjectName(QStringLiteral("lineEdit_slippage"));
        lineEdit_slippage->setEnabled(false);
        lineEdit_slippage->setReadOnly(true);

        horizontalLayout_slippage->addWidget(lineEdit_slippage);


        verticalLayout_slippage->addLayout(horizontalLayout_slippage);


        verticalLayout->addLayout(verticalLayout_slippage);

        horizontalLayout_spotPrice = new QHBoxLayout();
        horizontalLayout_spotPrice->setObjectName(QStringLiteral("horizontalLayout_spotPrice"));
        horizontalLayout_spotPrice->setContentsMargins(-1, 0, -1, -1);
        label_spotPrice = new QLabel(PoolListWidgetItem);
        label_spotPrice->setObjectName(QStringLiteral("label_spotPrice"));

        horizontalLayout_spotPrice->addWidget(label_spotPrice);

        comboBox_spotPrice = new QComboBox(PoolListWidgetItem);
        comboBox_spotPrice->setObjectName(QStringLiteral("comboBox_spotPrice"));

        horizontalLayout_spotPrice->addWidget(comboBox_spotPrice);


        verticalLayout->addLayout(horizontalLayout_spotPrice);

        horizontalLayout_poolTable = new QHBoxLayout();
        horizontalLayout_poolTable->setObjectName(QStringLiteral("horizontalLayout_poolTable"));
        horizontalLayout_poolTable->setSizeConstraint(QLayout::SetMaximumSize);
        tableWidget_poolInformation = new QTableWidget(PoolListWidgetItem);
        if (tableWidget_poolInformation->columnCount() < 3)
            tableWidget_poolInformation->setColumnCount(3);
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::NoBrush);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setBackground(QColor(100, 0, 0));
        __qtablewidgetitem3->setForeground(brush);
        tableWidget_poolInformation->setHorizontalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget_poolInformation->setHorizontalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        __qtablewidgetitem5->setBackground(QColor(128, 28, 176));
        tableWidget_poolInformation->setHorizontalHeaderItem(2, __qtablewidgetitem5);
        tableWidget_poolInformation->setObjectName(QStringLiteral("tableWidget_poolInformation"));
        tableWidget_poolInformation->setEnabled(true);
        tableWidget_poolInformation->setEditTriggers(QAbstractItemView::NoEditTriggers);

        horizontalLayout_poolTable->addWidget(tableWidget_poolInformation);


        verticalLayout->addLayout(horizontalLayout_poolTable);

        horizontalLayout_secondToken = new QHBoxLayout();
        horizontalLayout_secondToken->setObjectName(QStringLiteral("horizontalLayout_secondToken"));
        horizontalLayout_secondToken->setContentsMargins(-1, 0, -1, -1);
        label_secondToken = new QLabel(PoolListWidgetItem);
        label_secondToken->setObjectName(QStringLiteral("label_secondToken"));

        horizontalLayout_secondToken->addWidget(label_secondToken);

        comboBox_secondToken = new QComboBox(PoolListWidgetItem);
        comboBox_secondToken->setObjectName(QStringLiteral("comboBox_secondToken"));

        horizontalLayout_secondToken->addWidget(comboBox_secondToken);


        verticalLayout->addLayout(horizontalLayout_secondToken);

        verticalLayout_2 = new QVBoxLayout();
#ifndef Q_OS_MAC
        verticalLayout_2->setSpacing(-1);
#endif
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetMaximumSize);
        verticalLayout_2->setContentsMargins(-1, 0, -1, -1);
        widgetGraph = new QCustomPlot(PoolListWidgetItem);
        widgetGraph->setObjectName(QStringLiteral("widgetGraph"));
        widgetGraph->setEnabled(true);
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(widgetGraph->sizePolicy().hasHeightForWidth());
        widgetGraph->setSizePolicy(sizePolicy2);
        widgetGraph->setBaseSize(QSize(0, 400));

        verticalLayout_2->addWidget(widgetGraph);


        verticalLayout->addLayout(verticalLayout_2);


        retranslateUi(PoolListWidgetItem);

        QMetaObject::connectSlotsByName(PoolListWidgetItem);
    } // setupUi

    void retranslateUi(QWidget *PoolListWidgetItem)
    {
        PoolListWidgetItem->setWindowTitle(QApplication::translate("PoolListWidgetItem", "Form", Q_NULLPTR));
        label_poolName->setText(QApplication::translate("PoolListWidgetItem", "Pool", Q_NULLPTR));
        label_protocol->setText(QApplication::translate("PoolListWidgetItem", "Protocol:", Q_NULLPTR));
        lineEdit_protocol->setText(QString());
        label_poolFee->setText(QApplication::translate("PoolListWidgetItem", "Pool fee (%):", Q_NULLPTR));
        label_slippage_title->setText(QApplication::translate("PoolListWidgetItem", "Slippage Metrics from Latest Trade:", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_slippage->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("PoolListWidgetItem", "Trade", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_slippage->verticalHeaderItem(0);
        ___qtablewidgetitem1->setText(QApplication::translate("PoolListWidgetItem", "Input token", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_slippage->verticalHeaderItem(1);
        ___qtablewidgetitem2->setText(QApplication::translate("PoolListWidgetItem", "Output token", Q_NULLPTR));
        label_slippage->setText(QApplication::translate("PoolListWidgetItem", "Slippage (%):", Q_NULLPTR));
        label_spotPrice->setText(QApplication::translate("PoolListWidgetItem", "Spot price against input token: ", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_poolInformation->horizontalHeaderItem(0);
        ___qtablewidgetitem3->setText(QApplication::translate("PoolListWidgetItem", "Current Values", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_poolInformation->horizontalHeaderItem(1);
        ___qtablewidgetitem4->setText(QApplication::translate("PoolListWidgetItem", "Delta", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_poolInformation->horizontalHeaderItem(2);
        ___qtablewidgetitem5->setText(QApplication::translate("PoolListWidgetItem", "Last", Q_NULLPTR));
        label_secondToken->setText(QApplication::translate("PoolListWidgetItem", "Graph 2nd token against input token:", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PoolListWidgetItem: public Ui_PoolListWidgetItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POOLLISTWIDGETITEM_H
