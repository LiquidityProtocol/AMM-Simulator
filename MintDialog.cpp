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
        ui->comboBox->addItem(QString::fromStdString(token->name()), QVariant::fromValue(token));
    }
    ui->comboBox->setCurrentIndex(-1);
}

MintDialog::~MintDialog()
{
    delete ui;
}

void MintDialog::on_pushButton_clicked()
{
    if (ui->comboBox->currentIndex() == -1) {
        QMessageBox::about(this, "Mint failed", "Please choose a token!");
    } else if (!ValidNumber(ui->lineEdit->text().toStdString())) {
        QMessageBox::about(this, "Mint failed", "Please enter a valid number!");
    } else {
        emit MintRequest(qvariant_cast<Token *>(ui->comboBox->currentData()), ui->lineEdit->text().toDouble());
    }
}
