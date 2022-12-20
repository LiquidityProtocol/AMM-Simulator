#include "TradeDialog.h"
#include "ui_TradeDialog.h"

TradeDialog::TradeDialog(QWidget *parent, Playground *playground, Account *account) :
    QDialog(parent),
    ui(new Ui::TradeDialog),
    playground_(playground),
    account_(account)
{
    ui->setupUi(this);
    for(const auto &[token, quantity]: account_->wallet()){
        ui->input_token_comboBox->addItem(QString::fromStdString(token->name()));
    }
}

TradeDialog::~TradeDialog()
{
    delete ui;
}

void TradeDialog::on_input_token_comboBox_currentTextChanged(const QString &currentText)
{
    ui->output_token_comboBox->clear();
    for(auto token: playground_->existing_tokens()){
        if (token->name() != currentText.toStdString()){
            ui->output_token_comboBox->addItem(QString::fromStdString(token->name()));
        }
    }
}

