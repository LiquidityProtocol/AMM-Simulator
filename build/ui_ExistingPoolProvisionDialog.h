/********************************************************************************
** Form generated from reading UI file 'ExistingPoolProvisionDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXISTINGPOOLPROVISIONDIALOG_H
#define UI_EXISTINGPOOLPROVISIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ExistingPoolProvisionDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_protocol;
    QLabel *label_protocol;
    QComboBox *comboBox_protocol;
    QHBoxLayout *horizontalLayout_pool;
    QLabel *label_pool;
    QComboBox *comboBox_pool;
    QTableWidget *tableWidget_pool;
    QHBoxLayout *horizontalLayoutpoolFee;
    QLabel *label_poolFee;
    QLineEdit *lineEdit_poolFee;
    QHBoxLayout *horizontalLayout_input_token;
    QLabel *label_input_token;
    QComboBox *comboBox_input_token;
    QLineEdit *lineEdit_input_token;
    QPushButton *pushButton_provide;

    void setupUi(QWidget *ExistingPoolProvisionDialog)
    {
        if (ExistingPoolProvisionDialog->objectName().isEmpty())
            ExistingPoolProvisionDialog->setObjectName(QStringLiteral("ExistingPoolProvisionDialog"));
        ExistingPoolProvisionDialog->resize(366, 434);
        verticalLayout = new QVBoxLayout(ExistingPoolProvisionDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_protocol = new QHBoxLayout();
        horizontalLayout_protocol->setObjectName(QStringLiteral("horizontalLayout_protocol"));
        horizontalLayout_protocol->setContentsMargins(-1, 0, -1, -1);
        label_protocol = new QLabel(ExistingPoolProvisionDialog);
        label_protocol->setObjectName(QStringLiteral("label_protocol"));

        horizontalLayout_protocol->addWidget(label_protocol);

        comboBox_protocol = new QComboBox(ExistingPoolProvisionDialog);
        comboBox_protocol->setObjectName(QStringLiteral("comboBox_protocol"));

        horizontalLayout_protocol->addWidget(comboBox_protocol);


        verticalLayout->addLayout(horizontalLayout_protocol);

        horizontalLayout_pool = new QHBoxLayout();
        horizontalLayout_pool->setObjectName(QStringLiteral("horizontalLayout_pool"));
        label_pool = new QLabel(ExistingPoolProvisionDialog);
        label_pool->setObjectName(QStringLiteral("label_pool"));

        horizontalLayout_pool->addWidget(label_pool);

        comboBox_pool = new QComboBox(ExistingPoolProvisionDialog);
        comboBox_pool->setObjectName(QStringLiteral("comboBox_pool"));

        horizontalLayout_pool->addWidget(comboBox_pool);


        verticalLayout->addLayout(horizontalLayout_pool);

        tableWidget_pool = new QTableWidget(ExistingPoolProvisionDialog);
        if (tableWidget_pool->columnCount() < 4)
            tableWidget_pool->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_pool->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_pool->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QFont font;
        font.setBold(false);
        font.setItalic(true);
        font.setUnderline(false);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setFont(font);
        tableWidget_pool->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_pool->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidget_pool->setObjectName(QStringLiteral("tableWidget_pool"));
        tableWidget_pool->setEnabled(true);
        tableWidget_pool->setEditTriggers(QAbstractItemView::NoEditTriggers);

        verticalLayout->addWidget(tableWidget_pool);

        horizontalLayoutpoolFee = new QHBoxLayout();
        horizontalLayoutpoolFee->setObjectName(QStringLiteral("horizontalLayoutpoolFee"));
        horizontalLayoutpoolFee->setContentsMargins(-1, 0, -1, 0);
        label_poolFee = new QLabel(ExistingPoolProvisionDialog);
        label_poolFee->setObjectName(QStringLiteral("label_poolFee"));

        horizontalLayoutpoolFee->addWidget(label_poolFee);

        lineEdit_poolFee = new QLineEdit(ExistingPoolProvisionDialog);
        lineEdit_poolFee->setObjectName(QStringLiteral("lineEdit_poolFee"));
        lineEdit_poolFee->setEnabled(false);
        lineEdit_poolFee->setMaximumSize(QSize(200, 22));
        lineEdit_poolFee->setReadOnly(true);

        horizontalLayoutpoolFee->addWidget(lineEdit_poolFee);


        verticalLayout->addLayout(horizontalLayoutpoolFee);

        horizontalLayout_input_token = new QHBoxLayout();
        horizontalLayout_input_token->setObjectName(QStringLiteral("horizontalLayout_input_token"));
        label_input_token = new QLabel(ExistingPoolProvisionDialog);
        label_input_token->setObjectName(QStringLiteral("label_input_token"));

        horizontalLayout_input_token->addWidget(label_input_token);

        comboBox_input_token = new QComboBox(ExistingPoolProvisionDialog);
        comboBox_input_token->setObjectName(QStringLiteral("comboBox_input_token"));

        horizontalLayout_input_token->addWidget(comboBox_input_token);


        verticalLayout->addLayout(horizontalLayout_input_token);

        lineEdit_input_token = new QLineEdit(ExistingPoolProvisionDialog);
        lineEdit_input_token->setObjectName(QStringLiteral("lineEdit_input_token"));

        verticalLayout->addWidget(lineEdit_input_token);

        pushButton_provide = new QPushButton(ExistingPoolProvisionDialog);
        pushButton_provide->setObjectName(QStringLiteral("pushButton_provide"));

        verticalLayout->addWidget(pushButton_provide);


        retranslateUi(ExistingPoolProvisionDialog);

        QMetaObject::connectSlotsByName(ExistingPoolProvisionDialog);
    } // setupUi

    void retranslateUi(QWidget *ExistingPoolProvisionDialog)
    {
        ExistingPoolProvisionDialog->setWindowTitle(QApplication::translate("ExistingPoolProvisionDialog", "Form", Q_NULLPTR));
        label_protocol->setText(QApplication::translate("ExistingPoolProvisionDialog", "Protocol", Q_NULLPTR));
        label_pool->setText(QApplication::translate("ExistingPoolProvisionDialog", "Pool", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_pool->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("ExistingPoolProvisionDialog", "Token", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_pool->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("ExistingPoolProvisionDialog", "Quantity", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_pool->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("ExistingPoolProvisionDialog", "Provision", Q_NULLPTR));
        label_poolFee->setText(QApplication::translate("ExistingPoolProvisionDialog", "Pool fee (%)", Q_NULLPTR));
        label_input_token->setText(QApplication::translate("ExistingPoolProvisionDialog", "Input Token", Q_NULLPTR));
        lineEdit_input_token->setText(QString());
        lineEdit_input_token->setPlaceholderText(QApplication::translate("ExistingPoolProvisionDialog", "Input token quantity", Q_NULLPTR));
        pushButton_provide->setText(QApplication::translate("ExistingPoolProvisionDialog", "Provide", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ExistingPoolProvisionDialog: public Ui_ExistingPoolProvisionDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXISTINGPOOLPROVISIONDIALOG_H
