/********************************************************************************
** Form generated from reading UI file 'WithdrawDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WITHDRAWDIALOG_H
#define UI_WITHDRAWDIALOG_H

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

class Ui_WithdrawDialog
{
public:
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_Protocol;
    QLabel *label_protocol;
    QComboBox *comboBox_protocol;
    QHBoxLayout *horizontalLayout_pool;
    QLabel *label_pool;
    QComboBox *comboBox_pool;
    QTableWidget *tableWidget_pool;
    QLineEdit *lineEdit_withdraw;
    QPushButton *pushButton_withdraw;

    void setupUi(QDialog *WithdrawDialog)
    {
        if (WithdrawDialog->objectName().isEmpty())
            WithdrawDialog->setObjectName(QStringLiteral("WithdrawDialog"));
        WithdrawDialog->resize(362, 359);
        verticalLayout_3 = new QVBoxLayout(WithdrawDialog);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_Protocol = new QHBoxLayout();
        horizontalLayout_Protocol->setObjectName(QStringLiteral("horizontalLayout_Protocol"));
        label_protocol = new QLabel(WithdrawDialog);
        label_protocol->setObjectName(QStringLiteral("label_protocol"));

        horizontalLayout_Protocol->addWidget(label_protocol);

        comboBox_protocol = new QComboBox(WithdrawDialog);
        comboBox_protocol->setObjectName(QStringLiteral("comboBox_protocol"));

        horizontalLayout_Protocol->addWidget(comboBox_protocol);


        verticalLayout_3->addLayout(horizontalLayout_Protocol);

        horizontalLayout_pool = new QHBoxLayout();
        horizontalLayout_pool->setObjectName(QStringLiteral("horizontalLayout_pool"));
        label_pool = new QLabel(WithdrawDialog);
        label_pool->setObjectName(QStringLiteral("label_pool"));

        horizontalLayout_pool->addWidget(label_pool);

        comboBox_pool = new QComboBox(WithdrawDialog);
        comboBox_pool->setObjectName(QStringLiteral("comboBox_pool"));

        horizontalLayout_pool->addWidget(comboBox_pool);


        verticalLayout_3->addLayout(horizontalLayout_pool);

        tableWidget_pool = new QTableWidget(WithdrawDialog);
        if (tableWidget_pool->columnCount() < 3)
            tableWidget_pool->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_pool->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_pool->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QFont font;
        font.setItalic(true);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setFont(font);
        tableWidget_pool->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget_pool->setObjectName(QStringLiteral("tableWidget_pool"));

        verticalLayout_3->addWidget(tableWidget_pool);

        lineEdit_withdraw = new QLineEdit(WithdrawDialog);
        lineEdit_withdraw->setObjectName(QStringLiteral("lineEdit_withdraw"));

        verticalLayout_3->addWidget(lineEdit_withdraw);

        pushButton_withdraw = new QPushButton(WithdrawDialog);
        pushButton_withdraw->setObjectName(QStringLiteral("pushButton_withdraw"));

        verticalLayout_3->addWidget(pushButton_withdraw);


        retranslateUi(WithdrawDialog);

        QMetaObject::connectSlotsByName(WithdrawDialog);
    } // setupUi

    void retranslateUi(QDialog *WithdrawDialog)
    {
        WithdrawDialog->setWindowTitle(QApplication::translate("WithdrawDialog", "Dialog", Q_NULLPTR));
        label_protocol->setText(QApplication::translate("WithdrawDialog", "Protocol", Q_NULLPTR));
        label_pool->setText(QApplication::translate("WithdrawDialog", "Pool", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_pool->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("WithdrawDialog", "Token", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_pool->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("WithdrawDialog", "Quantity", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_pool->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("WithdrawDialog", "Withdrawal", Q_NULLPTR));
        lineEdit_withdraw->setText(QString());
        lineEdit_withdraw->setPlaceholderText(QApplication::translate("WithdrawDialog", "% to withdraw", Q_NULLPTR));
        pushButton_withdraw->setText(QApplication::translate("WithdrawDialog", "Withdraw", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class WithdrawDialog: public Ui_WithdrawDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WITHDRAWDIALOG_H
