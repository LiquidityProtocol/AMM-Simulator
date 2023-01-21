/********************************************************************************
** Form generated from reading UI file 'TradeDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRADEDIALOG_H
#define UI_TRADEDIALOG_H

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
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_TradeDialog
{
public:
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QComboBox *input_token_comboBox;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_outputToken;
    QComboBox *output_token_comboBox;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_protocol;
    QComboBox *protocol_comboBox;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_pool;
    QComboBox *pool_comboBox;
    QLineEdit *input_quantity_lineEdit;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_outputQuantity;
    QLineEdit *output_quantity_lineEdit;
    QHBoxLayout *horizontalLayout_slippage;
    QLabel *label_slippage;
    QLineEdit *lineEdit_slippage;
    QPushButton *pushButton;

    void setupUi(QDialog *TradeDialog)
    {
        if (TradeDialog->objectName().isEmpty())
            TradeDialog->setObjectName(QStringLiteral("TradeDialog"));
        TradeDialog->resize(313, 296);
        verticalLayout_3 = new QVBoxLayout(TradeDialog);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(TradeDialog);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label, 0, Qt::AlignHCenter);

        input_token_comboBox = new QComboBox(TradeDialog);
        input_token_comboBox->setObjectName(QStringLiteral("input_token_comboBox"));

        verticalLayout->addWidget(input_token_comboBox);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_outputToken = new QLabel(TradeDialog);
        label_outputToken->setObjectName(QStringLiteral("label_outputToken"));

        verticalLayout_2->addWidget(label_outputToken, 0, Qt::AlignHCenter);

        output_token_comboBox = new QComboBox(TradeDialog);
        output_token_comboBox->setObjectName(QStringLiteral("output_token_comboBox"));

        verticalLayout_2->addWidget(output_token_comboBox);


        horizontalLayout->addLayout(verticalLayout_2);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_protocol = new QLabel(TradeDialog);
        label_protocol->setObjectName(QStringLiteral("label_protocol"));

        horizontalLayout_2->addWidget(label_protocol);

        protocol_comboBox = new QComboBox(TradeDialog);
        protocol_comboBox->setObjectName(QStringLiteral("protocol_comboBox"));

        horizontalLayout_2->addWidget(protocol_comboBox);


        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_pool = new QLabel(TradeDialog);
        label_pool->setObjectName(QStringLiteral("label_pool"));

        horizontalLayout_4->addWidget(label_pool);

        pool_comboBox = new QComboBox(TradeDialog);
        pool_comboBox->setObjectName(QStringLiteral("pool_comboBox"));

        horizontalLayout_4->addWidget(pool_comboBox);


        verticalLayout_3->addLayout(horizontalLayout_4);

        input_quantity_lineEdit = new QLineEdit(TradeDialog);
        input_quantity_lineEdit->setObjectName(QStringLiteral("input_quantity_lineEdit"));

        verticalLayout_3->addWidget(input_quantity_lineEdit);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_outputQuantity = new QLabel(TradeDialog);
        label_outputQuantity->setObjectName(QStringLiteral("label_outputQuantity"));

        horizontalLayout_3->addWidget(label_outputQuantity);

        output_quantity_lineEdit = new QLineEdit(TradeDialog);
        output_quantity_lineEdit->setObjectName(QStringLiteral("output_quantity_lineEdit"));
        output_quantity_lineEdit->setReadOnly(true);

        horizontalLayout_3->addWidget(output_quantity_lineEdit);


        verticalLayout_3->addLayout(horizontalLayout_3);

        horizontalLayout_slippage = new QHBoxLayout();
        horizontalLayout_slippage->setObjectName(QStringLiteral("horizontalLayout_slippage"));
        horizontalLayout_slippage->setContentsMargins(-1, -1, -1, 0);
        label_slippage = new QLabel(TradeDialog);
        label_slippage->setObjectName(QStringLiteral("label_slippage"));

        horizontalLayout_slippage->addWidget(label_slippage);

        lineEdit_slippage = new QLineEdit(TradeDialog);
        lineEdit_slippage->setObjectName(QStringLiteral("lineEdit_slippage"));
        lineEdit_slippage->setEnabled(false);
        lineEdit_slippage->setReadOnly(true);

        horizontalLayout_slippage->addWidget(lineEdit_slippage);


        verticalLayout_3->addLayout(horizontalLayout_slippage);

        pushButton = new QPushButton(TradeDialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout_3->addWidget(pushButton);


        retranslateUi(TradeDialog);

        QMetaObject::connectSlotsByName(TradeDialog);
    } // setupUi

    void retranslateUi(QDialog *TradeDialog)
    {
        TradeDialog->setWindowTitle(QApplication::translate("TradeDialog", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("TradeDialog", "Input Token", Q_NULLPTR));
        label_outputToken->setText(QApplication::translate("TradeDialog", "Output Token", Q_NULLPTR));
        label_protocol->setText(QApplication::translate("TradeDialog", "Protocol", Q_NULLPTR));
        label_pool->setText(QApplication::translate("TradeDialog", "Pool", Q_NULLPTR));
        input_quantity_lineEdit->setPlaceholderText(QApplication::translate("TradeDialog", "Enter input quantity here", Q_NULLPTR));
        label_outputQuantity->setText(QApplication::translate("TradeDialog", "Output quantity:", Q_NULLPTR));
        label_slippage->setText(QApplication::translate("TradeDialog", "Slippage (%): ", Q_NULLPTR));
        pushButton->setText(QApplication::translate("TradeDialog", "Trade", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class TradeDialog: public Ui_TradeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRADEDIALOG_H
