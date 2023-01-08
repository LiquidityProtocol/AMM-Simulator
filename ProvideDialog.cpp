#include "ProvideDialog.h"
#include "ui_ProvideDialog.h"
#include "AccountListWidgetItem.h"
#include <QMessageBox>


ProvideDialog::ProvideDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProvideDialog)
{
    ui->setupUi(this);
    connect(this, &ProvideDialog::ProvisionTypeDeclaration, qobject_cast<AccountListWidgetItem *>(parent), &AccountListWidgetItem::VerifyProvisionTypeDeclaration);
    int ret;

    QMessageBox msgBox;
    msgBox.setStyleSheet("background-color: rgb(176, 196, 222);");
            msgBox.setText("The document has been modified.");
            msgBox.setInformativeText("Do you want to provide to an existing pool?");
            msgBox.setStandardButtons(QMessageBox::Yes |
                                      QMessageBox::No);
            msgBox.setDefaultButton(QMessageBox::No);
    ret = msgBox.exec();

    switch (ret) {
         case QMessageBox::Yes:
             // Yes was clicked
             emit ProvisionTypeDeclaration(false);
             break;
         case QMessageBox::No:
             // No
             emit ProvisionTypeDeclaration(true);
             break;
         default:
             // should never be reached
             break;
       }
}



ProvideDialog::~ProvideDialog()
{

    delete ui;
}


void ProvideDialog::on_pushButton_newPool_clicked()

{
    emit ProvisionTypeDeclaration(true);
}

void ProvideDialog::on_pushButton_existingPool_clicked()
{
    emit ProvisionTypeDeclaration(false);
}
