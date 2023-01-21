/********************************************************************************
** Form generated from reading UI file 'SimulationPlayground.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMULATIONPLAYGROUND_H
#define UI_SIMULATIONPLAYGROUND_H

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
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SimulationPlayground
{
public:
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QComboBox *Arbs_Options;
    QLabel *label_4;
    QComboBox *View_Options;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_initial;
    QTextEdit *textEdit_initial_scenario;
    QPushButton *pushButton_load_scenario;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QComboBox *pool_comboBox;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *tab_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *runButton;
    QPushButton *pushButton_reset_market;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit;
    QPushButton *pushButton_customEpoch;
    QPushButton *pushButton_stop;

    void setupUi(QDialog *SimulationPlayground)
    {
        if (SimulationPlayground->objectName().isEmpty())
            SimulationPlayground->setObjectName(QStringLiteral("SimulationPlayground"));
        SimulationPlayground->resize(754, 606);
        horizontalLayout_3 = new QHBoxLayout(SimulationPlayground);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_2 = new QLabel(SimulationPlayground);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout_2->addWidget(label_2);

        Arbs_Options = new QComboBox(SimulationPlayground);
        Arbs_Options->setObjectName(QStringLiteral("Arbs_Options"));

        verticalLayout_2->addWidget(Arbs_Options);

        label_4 = new QLabel(SimulationPlayground);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout_2->addWidget(label_4);

        View_Options = new QComboBox(SimulationPlayground);
        View_Options->setObjectName(QStringLiteral("View_Options"));

        verticalLayout_2->addWidget(View_Options);


        verticalLayout_4->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_initial = new QLabel(SimulationPlayground);
        label_initial->setObjectName(QStringLiteral("label_initial"));

        verticalLayout_3->addWidget(label_initial);

        textEdit_initial_scenario = new QTextEdit(SimulationPlayground);
        textEdit_initial_scenario->setObjectName(QStringLiteral("textEdit_initial_scenario"));

        verticalLayout_3->addWidget(textEdit_initial_scenario);

        pushButton_load_scenario = new QPushButton(SimulationPlayground);
        pushButton_load_scenario->setObjectName(QStringLiteral("pushButton_load_scenario"));

        verticalLayout_3->addWidget(pushButton_load_scenario);


        verticalLayout_4->addLayout(verticalLayout_3);


        horizontalLayout_3->addLayout(verticalLayout_4);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(SimulationPlayground);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        pool_comboBox = new QComboBox(SimulationPlayground);
        pool_comboBox->setObjectName(QStringLiteral("pool_comboBox"));

        verticalLayout->addWidget(pool_comboBox);

        tabWidget = new QTabWidget(SimulationPlayground);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        tabWidget->addTab(tab_2, QString());

        verticalLayout->addWidget(tabWidget);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        runButton = new QPushButton(SimulationPlayground);
        runButton->setObjectName(QStringLiteral("runButton"));

        horizontalLayout_2->addWidget(runButton);

        pushButton_reset_market = new QPushButton(SimulationPlayground);
        pushButton_reset_market->setObjectName(QStringLiteral("pushButton_reset_market"));

        horizontalLayout_2->addWidget(pushButton_reset_market);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        lineEdit = new QLineEdit(SimulationPlayground);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        pushButton_customEpoch = new QPushButton(SimulationPlayground);
        pushButton_customEpoch->setObjectName(QStringLiteral("pushButton_customEpoch"));

        horizontalLayout->addWidget(pushButton_customEpoch);

        pushButton_stop = new QPushButton(SimulationPlayground);
        pushButton_stop->setObjectName(QStringLiteral("pushButton_stop"));

        horizontalLayout->addWidget(pushButton_stop);


        verticalLayout->addLayout(horizontalLayout);


        horizontalLayout_3->addLayout(verticalLayout);


        retranslateUi(SimulationPlayground);

        QMetaObject::connectSlotsByName(SimulationPlayground);
    } // setupUi

    void retranslateUi(QDialog *SimulationPlayground)
    {
        SimulationPlayground->setWindowTitle(QApplication::translate("SimulationPlayground", "Dialog", Q_NULLPTR));
        label_2->setText(QApplication::translate("SimulationPlayground", "Arbitrageur", Q_NULLPTR));
        Arbs_Options->setPlaceholderText(QApplication::translate("SimulationPlayground", "Select Behavior", Q_NULLPTR));
        label_4->setText(QApplication::translate("SimulationPlayground", "View Method", Q_NULLPTR));
        label_initial->setText(QApplication::translate("SimulationPlayground", "Initial scenario", Q_NULLPTR));
        pushButton_load_scenario->setText(QApplication::translate("SimulationPlayground", "Load", Q_NULLPTR));
        label->setText(QApplication::translate("SimulationPlayground", "Market Pools Information", Q_NULLPTR));
        pool_comboBox->setPlaceholderText(QApplication::translate("SimulationPlayground", "Select Pool", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("SimulationPlayground", "Tab 1", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("SimulationPlayground", "Tab 2", Q_NULLPTR));
        runButton->setText(QApplication::translate("SimulationPlayground", "Run Epoch", Q_NULLPTR));
        pushButton_reset_market->setText(QApplication::translate("SimulationPlayground", "Reset Market", Q_NULLPTR));
        lineEdit->setPlaceholderText(QApplication::translate("SimulationPlayground", "Enter number of epochs", Q_NULLPTR));
        pushButton_customEpoch->setText(QApplication::translate("SimulationPlayground", "Run Custom Epoch", Q_NULLPTR));
        pushButton_stop->setText(QApplication::translate("SimulationPlayground", "Stop", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SimulationPlayground: public Ui_SimulationPlayground {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMULATIONPLAYGROUND_H
