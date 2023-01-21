#include "ProvideDialog.h"
#include "ui_ProvideDialog.h"
#include "AccountListWidgetItem.h"

ProvideDialog::ProvideDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProvideDialog)
{
    ui->setupUi(this);
    connect(this, &ProvideDialog::ProvisionTypeDeclaration, qobject_cast<AccountListWidgetItem *>(parent), &AccountListWidgetItem::VerifyProvisionTypeDeclaration);
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
