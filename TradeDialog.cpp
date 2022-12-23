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
        ui->input_token_comboBox->addItem(QString::fromStdString(token->name()), QVariant::fromValue(token));
    }
    for(const auto &[protocol_name, protocol]: playground_->protocols){
        ui->protocol_comboBox->addItem(QString::fromStdString(protocol_name), protocol);
    }
    ui->protocol_comboBox->setCurrentIndex(-1);

}

TradeDialog::~TradeDialog()
{
    delete ui;
}

void TradeDialog::on_input_token_comboBox_currentTextChanged(const QString &currentText)
{
    input_token_ = playground_->GetToken(currentText.toStdString()).first;
    ui->output_token_comboBox->clear();
    for(auto token: playground_->existing_tokens()){
        if (token->name() != currentText.toStdString()){
            ui->output_token_comboBox->addItem(QString::fromStdString(token->name()), QVariant::fromValue(token));
        }
    }
}

void TradeDialog::on_output_token_comboBox_currentTextChanged(const QString &output_token)
{
    output_token_ = playground_->GetToken(output_token.toStdString()).first;
    ui->protocol_comboBox->setCurrentIndex(-1);
}


void TradeDialog::on_protocol_comboBox_currentIndexChanged(int index)
{
    if (index != -1){
        ui->pool_comboBox->clear();
        protocol_ = qvariant_cast<PROTOCOL>(ui->protocol_comboBox->itemData(index));
        std::unordered_set<PoolInterface*> pools = playground_->GetPools(protocol_, input_token_, output_token_);
        for(const auto &pool: pools){
            QString pool_name = QString::fromStdString(std::to_string(reinterpret_cast<uint64_t>(pool)));
            ui->pool_comboBox->addItem(pool_name, QVariant::fromValue(pool));
        }
    }
}


void TradeDialog::on_pool_comboBox_currentIndexChanged(int index)
{
    if(index != -1){
        current_pool_ = ui->pool_comboBox->itemData(index).value<PoolInterface*>();
        double input_quantity = ui->input_token_comboBox->currentText().toDouble();
        if(input_quantity > 0){
            double output_quantity = playground_->SimulateSwap(current_pool_, input_token_, output_token_, input_quantity);
            ui->output_quantity_lineEdit->setText(QString::number(output_quantity));
        }
    }
}


void TradeDialog::on_input_quantity_lineEdit_textChanged(const QString &input_quantity_string)
{
    double input_quantity = input_quantity_string.toDouble();
    if(ui->pool_comboBox->currentIndex() != -1 && input_quantity > 0){
        double output_quantity = playground_->SimulateSwap(current_pool_, input_token_, output_token_, input_quantity);
        ui->output_quantity_lineEdit->setText(QString::number(output_quantity));
    }
}

