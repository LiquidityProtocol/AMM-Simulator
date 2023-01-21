/********************************************************************************
** Form generated from reading UI file 'ChangeModeDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHANGEMODEDIALOG_H
#define UI_CHANGEMODEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPlainTextEdit>

QT_BEGIN_NAMESPACE

class Ui_ChangeModeDialog
{
public:
    QDialogButtonBox *buttonBox;
    QPlainTextEdit *plainTextEdit;

    void setupUi(QDialog *ChangeModeDialog)
    {
        if (ChangeModeDialog->objectName().isEmpty())
            ChangeModeDialog->setObjectName(QStringLiteral("ChangeModeDialog"));
        ChangeModeDialog->resize(400, 300);
        buttonBox = new QDialogButtonBox(ChangeModeDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(100, 230, 161, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        plainTextEdit = new QPlainTextEdit(ChangeModeDialog);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(90, 60, 191, 151));
        plainTextEdit->setReadOnly(true);

        retranslateUi(ChangeModeDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), ChangeModeDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ChangeModeDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(ChangeModeDialog);
    } // setupUi

    void retranslateUi(QDialog *ChangeModeDialog)
    {
        ChangeModeDialog->setWindowTitle(QApplication::translate("ChangeModeDialog", "Dialog", Q_NULLPTR));
        plainTextEdit->setPlainText(QApplication::translate("ChangeModeDialog", "Go to Simulation Playground?", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ChangeModeDialog: public Ui_ChangeModeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHANGEMODEDIALOG_H
