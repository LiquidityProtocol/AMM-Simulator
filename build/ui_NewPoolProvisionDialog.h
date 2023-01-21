/********************************************************************************
** Form generated from reading UI file 'NewPoolProvisionDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWPOOLPROVISIONDIALOG_H
#define UI_NEWPOOLPROVISIONDIALOG_H

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
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_NewPoolProvisionDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_protocol;
    QLabel *label_protocol;
    QComboBox *comboBox_protocol;
    QTableWidget *tableWidget_tokens;
    QHBoxLayout *horizontalLayout_poolFee;
    QLabel *label_poolFee;
    QComboBox *comboBox_poolFee;
    QHBoxLayout *horizontalLayout_slippageController;
    QLabel *label_slippageController;
    QLineEdit *lineEdit_slippageController;
    QPushButton *pushButton_provide;

    void setupUi(QDialog *NewPoolProvisionDialog)
    {
        if (NewPoolProvisionDialog->objectName().isEmpty())
            NewPoolProvisionDialog->setObjectName(QStringLiteral("NewPoolProvisionDialog"));
        NewPoolProvisionDialog->resize(362, 367);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(NewPoolProvisionDialog->sizePolicy().hasHeightForWidth());
        NewPoolProvisionDialog->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(NewPoolProvisionDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_protocol = new QHBoxLayout();
        horizontalLayout_protocol->setObjectName(QStringLiteral("horizontalLayout_protocol"));
        label_protocol = new QLabel(NewPoolProvisionDialog);
        label_protocol->setObjectName(QStringLiteral("label_protocol"));

        horizontalLayout_protocol->addWidget(label_protocol);

        comboBox_protocol = new QComboBox(NewPoolProvisionDialog);
        comboBox_protocol->setObjectName(QStringLiteral("comboBox_protocol"));

        horizontalLayout_protocol->addWidget(comboBox_protocol);


        verticalLayout->addLayout(horizontalLayout_protocol);

        tableWidget_tokens = new QTableWidget(NewPoolProvisionDialog);
        if (tableWidget_tokens->columnCount() < 3)
            tableWidget_tokens->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_tokens->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_tokens->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_tokens->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        if (tableWidget_tokens->rowCount() < 3)
            tableWidget_tokens->setRowCount(3);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_tokens->setVerticalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget_tokens->setVerticalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget_tokens->setVerticalHeaderItem(2, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        __qtablewidgetitem6->setFlags(Qt::NoItemFlags);
        tableWidget_tokens->setItem(2, 0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        __qtablewidgetitem7->setFlags(Qt::NoItemFlags);
        tableWidget_tokens->setItem(2, 1, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        __qtablewidgetitem8->setFlags(Qt::NoItemFlags);
        tableWidget_tokens->setItem(2, 2, __qtablewidgetitem8);
        tableWidget_tokens->setObjectName(QStringLiteral("tableWidget_tokens"));

        verticalLayout->addWidget(tableWidget_tokens);

        horizontalLayout_poolFee = new QHBoxLayout();
        horizontalLayout_poolFee->setObjectName(QStringLiteral("horizontalLayout_poolFee"));
        label_poolFee = new QLabel(NewPoolProvisionDialog);
        label_poolFee->setObjectName(QStringLiteral("label_poolFee"));

        horizontalLayout_poolFee->addWidget(label_poolFee);

        comboBox_poolFee = new QComboBox(NewPoolProvisionDialog);
        comboBox_poolFee->setObjectName(QStringLiteral("comboBox_poolFee"));

        horizontalLayout_poolFee->addWidget(comboBox_poolFee);


        verticalLayout->addLayout(horizontalLayout_poolFee);

        horizontalLayout_slippageController = new QHBoxLayout();
        horizontalLayout_slippageController->setObjectName(QStringLiteral("horizontalLayout_slippageController"));
        label_slippageController = new QLabel(NewPoolProvisionDialog);
        label_slippageController->setObjectName(QStringLiteral("label_slippageController"));

        horizontalLayout_slippageController->addWidget(label_slippageController);

        lineEdit_slippageController = new QLineEdit(NewPoolProvisionDialog);
        lineEdit_slippageController->setObjectName(QStringLiteral("lineEdit_slippageController"));

        horizontalLayout_slippageController->addWidget(lineEdit_slippageController);


        verticalLayout->addLayout(horizontalLayout_slippageController);

        pushButton_provide = new QPushButton(NewPoolProvisionDialog);
        pushButton_provide->setObjectName(QStringLiteral("pushButton_provide"));

        verticalLayout->addWidget(pushButton_provide);


        retranslateUi(NewPoolProvisionDialog);

        comboBox_poolFee->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(NewPoolProvisionDialog);
    } // setupUi

    void retranslateUi(QDialog *NewPoolProvisionDialog)
    {
        NewPoolProvisionDialog->setWindowTitle(QApplication::translate("NewPoolProvisionDialog", "Dialog", Q_NULLPTR));
        label_protocol->setText(QApplication::translate("NewPoolProvisionDialog", "Protocol", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_tokens->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("NewPoolProvisionDialog", "Token", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_tokens->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("NewPoolProvisionDialog", "Quantity", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_tokens->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("NewPoolProvisionDialog", "Weight", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_tokens->verticalHeaderItem(0);
        ___qtablewidgetitem3->setText(QApplication::translate("NewPoolProvisionDialog", "-", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_tokens->verticalHeaderItem(1);
        ___qtablewidgetitem4->setText(QApplication::translate("NewPoolProvisionDialog", "-", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_tokens->verticalHeaderItem(2);
        ___qtablewidgetitem5->setText(QApplication::translate("NewPoolProvisionDialog", "+", Q_NULLPTR));

        const bool __sortingEnabled = tableWidget_tokens->isSortingEnabled();
        tableWidget_tokens->setSortingEnabled(false);
        tableWidget_tokens->setSortingEnabled(__sortingEnabled);

        label_poolFee->setText(QApplication::translate("NewPoolProvisionDialog", "Pool fee (%)", Q_NULLPTR));
        comboBox_poolFee->clear();
        comboBox_poolFee->insertItems(0, QStringList()
         << QApplication::translate("NewPoolProvisionDialog", "0", Q_NULLPTR)
         << QApplication::translate("NewPoolProvisionDialog", "0.25", Q_NULLPTR)
         << QApplication::translate("NewPoolProvisionDialog", "0.5", Q_NULLPTR)
         << QApplication::translate("NewPoolProvisionDialog", "0.75", Q_NULLPTR)
         << QApplication::translate("NewPoolProvisionDialog", "1", Q_NULLPTR)
        );
        label_slippageController->setText(QApplication::translate("NewPoolProvisionDialog", "Slippage controller", Q_NULLPTR));
        pushButton_provide->setText(QApplication::translate("NewPoolProvisionDialog", "Provide", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class NewPoolProvisionDialog: public Ui_NewPoolProvisionDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWPOOLPROVISIONDIALOG_H
