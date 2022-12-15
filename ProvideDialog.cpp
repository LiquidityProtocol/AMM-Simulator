#include "ProvideDialog.h"
#include "ui_ProvideDialog.h"
#include "AccountListWidgetItem.h"

std::vector<std::string> protocols{ "Balancer", "ConstantSum", "UniswapV2", "UniswapV3" };

ProvideDialog::ProvideDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProvideDialog)
{
    ui->setupUi(this);
//    connect(this, &ProvideDialog::SendData, qobject_cast<AccountListWidgetItem *>(parent), &MetricsTable::VerifyData);

    for (auto token : Token::existing_tokens()) {
        ui->comboBox->addItem(QString::fromStdString(token->name()));
    }

    for (auto token : Token::existing_tokens()) {
        if (token != Token::existing_tokens()[ui->comboBox->currentIndex()]){
        ui->comboBox_2->addItem(QString::fromStdString(token->name()));
        }
    }

    for (auto protocol : protocols) {
        ui->comboBox_3->addItem(QString::fromStdString(protocol));
    }
}

ProvideDialog::~ProvideDialog()
{
    delete ui;
}

void ProvideDialog::on_pushButton_clicked()
{
    emit SendData(Token::existing_tokens()[ui->comboBox->currentIndex()], ui->lineEdit->text().toDouble(), Token::existing_tokens()[ui->comboBox_2->currentIndex()], ui->lineEdit->text().toDouble(), protocols[ui->comboBox_3->currentIndex()]);
}

void ProvideDialog::display_other_token()
{
    std::string used_protocol = protocols[ui->comboBox_2->currentIndex()];

    emit SendData(Token::existing_tokens()[ui->comboBox_2->currentIndex()], ui->lineEdit->text().toDouble(),Token::existing_tokens()[ui->comboBox_2->currentIndex()], ui->lineEdit->text().toDouble(), protocols[ui->comboBox_3->currentIndex()]);
}

