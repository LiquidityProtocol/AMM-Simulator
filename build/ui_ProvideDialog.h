/********************************************************************************
** Form generated from reading UI file 'ProvideDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROVIDEDIALOG_H
#define UI_PROVIDEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ProvideDialog
{
public:
    QVBoxLayout *verticalLayout;
    QTextEdit *textEdit;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_newPool;
    QPushButton *pushButton_existingPool;

    void setupUi(QDialog *ProvideDialog)
    {
        if (ProvideDialog->objectName().isEmpty())
            ProvideDialog->setObjectName(QStringLiteral("ProvideDialog"));
        ProvideDialog->resize(280, 258);
        verticalLayout = new QVBoxLayout(ProvideDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        textEdit = new QTextEdit(ProvideDialog);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setReadOnly(true);

        verticalLayout->addWidget(textEdit);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButton_newPool = new QPushButton(ProvideDialog);
        pushButton_newPool->setObjectName(QStringLiteral("pushButton_newPool"));

        horizontalLayout->addWidget(pushButton_newPool);

        pushButton_existingPool = new QPushButton(ProvideDialog);
        pushButton_existingPool->setObjectName(QStringLiteral("pushButton_existingPool"));

        horizontalLayout->addWidget(pushButton_existingPool);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(ProvideDialog);

        QMetaObject::connectSlotsByName(ProvideDialog);
    } // setupUi

    void retranslateUi(QDialog *ProvideDialog)
    {
        ProvideDialog->setWindowTitle(QApplication::translate("ProvideDialog", "Dialog", Q_NULLPTR));
        textEdit->setHtml(QApplication::translate("ProvideDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'.AppleSystemUIFont'; font-size:13pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:18pt;\">Do you want to provide to a new pool or an existing pool?</span></p></body></html>", Q_NULLPTR));
        pushButton_newPool->setText(QApplication::translate("ProvideDialog", "New Pool", Q_NULLPTR));
        pushButton_existingPool->setText(QApplication::translate("ProvideDialog", "Existing Pool", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ProvideDialog: public Ui_ProvideDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROVIDEDIALOG_H
