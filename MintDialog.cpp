#include "MintDialog.h"
#include "ui_MintDialog.h"
#include "AccountListWidgetItem.h"

MintDialog::MintDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MintDialog)
{
    ui->setupUi(this);
    connect(this, &MintDialog::SendData, qobject_cast<AccountListWidgetItem *>(parent), &AccountListWidgetItem::VerifyData);

    for (auto token : Token::existing_tokens()) {
        ui->comboBox->addItem(QString::fromStdString(token->name()));
    }
}

MintDialog::~MintDialog()
{
    delete ui;
}

void MintDialog::on_pushButton_clicked()
{
    emit SendData(Token::existing_tokens()[ui->comboBox->currentIndex()], ui->lineEdit->text().toDouble());
}
