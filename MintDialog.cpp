#include "MintDialog.h"
#include "ui_MintDialog.h"
#include "AccountListWidgetItem.h"
#include "src/Playground.hpp"

MintDialog::MintDialog(QWidget *parent, Playground *playground) :
    QDialog(parent),
    ui(new Ui::MintDialog),
    playground_(playground)
{
    ui->setupUi(this);
    connect(this, &MintDialog::SendData, qobject_cast<AccountListWidgetItem *>(parent), &AccountListWidgetItem::VerifyData);

    for (auto token : playground_->existing_tokens()) {
        ui->comboBox->addItem(QString::fromStdString(token->name()));
    }
}

MintDialog::~MintDialog()
{
    delete ui;
}

void MintDialog::on_pushButton_clicked()
{
    emit SendData(playground_->GetToken(ui->comboBox->currentText().toStdString()).first, ui->lineEdit->text().toDouble());
}
