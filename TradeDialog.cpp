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
    for(const auto &[protocol_name, protocol]: playground_->protocols){
        ui->protocol_comboBox->addItem(QString::fromStdString(protocol_name));
    }
    ui->protocol_comboBox->setCurrentIndex(-1);

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


//void TradeDialog::on_output_token_comboBox_currentTextChanged(const QString &output_token)
//{
//    ui->pool_comboBox->clear();
//    Token *input = playground_->GetToken(ui->input_token_comboBox->currentText().toStdString()).first;
//    Token *output = playground_->GetToken(output_token.toStdString()).first;
//    PROTOCOL protocol = playground_->protocols[ui->protocol_comboBox->currentText().toStdString()];
//    std::unordered_set<PoolInterface*> pools = playground_->GetPools(protocol, input, output);
//    for(auto pool: pools){
//        QString pool_name = QString::fromStdString(std::to_string(reinterpret_cast<uint64_t>(pool)));
//        ui->pool_comboBox->addItem(pool_name);
//    }
//}

void TradeDialog::on_output_token_comboBox_currentTextChanged(const QString &output_token)
{
    ui->protocol_comboBox->setCurrentIndex(-1);
}


void TradeDialog::on_protocol_comboBox_currentIndexChanged(int index)
{
    if (index != -1){
        ui->pool_comboBox->clear();
            Token *input = playground_->GetToken(ui->input_token_comboBox->currentText().toStdString()).first;
            Token *output = playground_->GetToken(ui->output_token_comboBox->currentText().toStdString()).first;
            PROTOCOL protocol = playground_->protocols[ui->protocol_comboBox->itemText(index).toStdString()];
            std::unordered_set<PoolInterface*> pools = playground_->GetPools(protocol, input, output);
//            for(auto pool: pools){
//                QString pool_name = QString::fromStdString(std::to_string(reinterpret_cast<uint64_t>(pool)));
//                ui->pool_comboBox->addItem(pool_name);
//            }
    }
}

