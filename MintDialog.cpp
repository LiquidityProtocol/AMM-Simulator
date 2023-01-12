#include "MintDialog.h"
#include "ui_MintDialog.h"
#include "AccountListWidgetItem.h"
#include "src/Playground.hpp"
#include <QMessageBox>

MintDialog::MintDialog(QWidget *parent, Playground *playground) :
    QDialog(parent),
    ui(new Ui::MintDialog),
    playground_(playground)
{
    ui->setupUi(this);
    connect(this, &MintDialog::MintRequest, qobject_cast<AccountListWidgetItem *>(parent), &AccountListWidgetItem::VerifyMintRequest);

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
    if (!ValidNumber(ui->lineEdit->text().toStdString())) {
        QMessageBox::about(this, "Mint failed", "Please provide a valid number of tokens!");
    } else {
        emit MintRequest(playground_->GetToken(ui->comboBox->currentText().toStdString()).first, ui->lineEdit->text().toDouble());
    }
}
