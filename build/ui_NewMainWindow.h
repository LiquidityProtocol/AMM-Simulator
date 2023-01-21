/********************************************************************************
** Form generated from reading UI file 'NewMainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWMAINWINDOW_H
#define UI_NEWMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NewMainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *tab_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_addManualPlayground;
    QPushButton *pushButton_addSimulation;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *NewMainWindow)
    {
        if (NewMainWindow->objectName().isEmpty())
            NewMainWindow->setObjectName(QStringLiteral("NewMainWindow"));
        NewMainWindow->resize(16777193, 16777193);
        centralwidget = new QWidget(NewMainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setUsesScrollButtons(false);
        tabWidget->setDocumentMode(true);
        tabWidget->setTabsClosable(true);
        tabWidget->setMovable(true);
        tabWidget->setTabBarAutoHide(false);
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        tabWidget->addTab(tab_2, QString());

        verticalLayout->addWidget(tabWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_addManualPlayground = new QPushButton(centralwidget);
        pushButton_addManualPlayground->setObjectName(QStringLiteral("pushButton_addManualPlayground"));

        horizontalLayout->addWidget(pushButton_addManualPlayground);

        pushButton_addSimulation = new QPushButton(centralwidget);
        pushButton_addSimulation->setObjectName(QStringLiteral("pushButton_addSimulation"));

        horizontalLayout->addWidget(pushButton_addSimulation);


        verticalLayout->addLayout(horizontalLayout);

        NewMainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(NewMainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 16777193, 24));
        NewMainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(NewMainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        NewMainWindow->setStatusBar(statusbar);

        retranslateUi(NewMainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(NewMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *NewMainWindow)
    {
        NewMainWindow->setWindowTitle(QApplication::translate("NewMainWindow", "Liquidity Protocol", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("NewMainWindow", "Tab 1", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("NewMainWindow", "Tab 2", Q_NULLPTR));
        pushButton_addManualPlayground->setText(QApplication::translate("NewMainWindow", "Add Manual Playground", Q_NULLPTR));
        pushButton_addSimulation->setText(QApplication::translate("NewMainWindow", "Add Simulation Playground", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class NewMainWindow: public Ui_NewMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWMAINWINDOW_H
