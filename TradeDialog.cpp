#include "TradeDialog.h"
#include "ui_TradeDialog.h"
#include "AccountListWidgetItem.h"
#include "src/Protocols/Protocols.hpp"
#include <QMessageBox>

TradeDialog::TradeDialog(QWidget *parent, Playground *playground, Account *account) :
    QDialog(parent),
    ui(new Ui::TradeDialog),
    playground_(playground),
    account_(account),
    selection_()
{
    ui->setupUi(this);
    connect(this, &TradeDialog::TradeRequest, qobject_cast<AccountListWidgetItem*>(parent), &AccountListWidgetItem::VerifyTradeRequest);
    for (const auto &[token, quantity] : account_->wallet()) {
        if (!token->pool()) {
            ui->input_token_comboBox->addItem(QString::fromStdString(token->name()), QVariant::fromValue(token));
        }
    }
    ui->input_token_comboBox->setCurrentIndex(-1);
    for (const auto &[protocol, protocol_name] : PROTOCOL_NAME) {
        ui->protocol_comboBox->addItem(QString::fromStdString(protocol_name), protocol);
    }
    ui->protocol_comboBox->setCurrentIndex(-1);
    QSizePolicy sp_retain = ui->label_outputToken->sizePolicy();
    sp_retain.setRetainSizeWhenHidden(true);
    ui->label_outputToken->setSizePolicy(sp_retain);
    ui->label_outputToken->setHidden(true);
    ui->output_token_comboBox->setHidden(true);
    sp_retain = ui->label_protocol->sizePolicy();
    sp_retain.setRetainSizeWhenHidden(true);
    ui->label_protocol->setSizePolicy(sp_retain);
    ui->label_protocol->setHidden(true);
    ui->protocol_comboBox->setHidden(true);
    sp_retain = ui->label_pool->sizePolicy();
    sp_retain.setRetainSizeWhenHidden(true);
    ui->label_pool->setSizePolicy(sp_retain);
    ui->label_pool->setHidden(true);
    ui->pool_comboBox->setHidden(true);
    sp_retain = ui->input_quantity_lineEdit->sizePolicy();
    sp_retain.setRetainSizeWhenHidden(true);
    ui->input_quantity_lineEdit->setSizePolicy(sp_retain);
    ui->input_quantity_lineEdit->setHidden(true);
    sp_retain = ui->label_outputQuantity->sizePolicy();
    sp_retain.setRetainSizeWhenHidden(true);
    ui->label_outputQuantity->setSizePolicy(sp_retain);
    ui->label_outputQuantity->setHidden(true);
    ui->output_quantity_lineEdit->setHidden(true);
    sp_retain = ui->label_slippage->sizePolicy();
    sp_retain.setRetainSizeWhenHidden(true);
    ui->label_slippage->setSizePolicy(sp_retain);
    ui->label_slippage->setHidden(true);
    ui->lineEdit_slippage->setHidden(true);
    ui->pushButton->setDisabled(true);
}

TradeDialog::~TradeDialog()
{
    delete ui;
}

void TradeDialog::on_input_token_comboBox_activated(int index)
{
    UNUSED(index);
    ui->output_token_comboBox->clear();
    for (auto token : playground_->existing_tokens()) {
        if (token->name() != ui->input_token_comboBox->currentText().toStdString()) {
            ui->output_token_comboBox->addItem(QString::fromStdString(token->name()), QVariant::fromValue(token));
        }
    }
    ui->output_token_comboBox->setCurrentIndex(-1);
    ui->protocol_comboBox->setCurrentIndex(-1);
    UpdateSelection();
    ui->label_outputToken->setHidden(false);
    ui->output_token_comboBox->setHidden(false);
    ui->label_protocol->setHidden(true);
    ui->protocol_comboBox->setHidden(true);
}

void TradeDialog::on_output_token_comboBox_activated(int index)
{
    UNUSED(index);
    ui->protocol_comboBox->setCurrentIndex(-1);
    UpdateSelection();
    ui->label_protocol->setHidden(false);
    ui->protocol_comboBox->setHidden(false);
}

void TradeDialog::on_protocol_comboBox_currentIndexChanged(int index)
{
    if (index == -1) {
        ui->pool_comboBox->clear();
        ui->input_quantity_lineEdit->clear();
        ui->label_pool->setHidden(true);
        ui->pool_comboBox->setHidden(true);
        ui->input_quantity_lineEdit->setHidden(true);
        ui->label_outputQuantity->setHidden(true);
        ui->output_quantity_lineEdit->setHidden(true);
        ui->label_slippage->setHidden(true);
        ui->lineEdit_slippage->setHidden(true);
        ui->pushButton->setDisabled(true);
    }
    UpdateSelection();
    UpdateOutputQuantity();
}

void TradeDialog::on_protocol_comboBox_activated(int index)
{
    if (index != -1) {
        ui->pool_comboBox->clear();
        PROTOCOL protocol = qvariant_cast<PROTOCOL>(ui->protocol_comboBox->currentData());
        std::unordered_set<PoolInterface *> pools = playground_->GetPools(protocol, selection_.input_token_, selection_.output_token_);
        if (pools.empty()) {
            QMessageBox::about(this, "Invalid choice", "There are no " + ui->protocol_comboBox->currentText() + " pools supporting trade between the two chosen tokens!");
            ui->protocol_comboBox->setCurrentIndex(-1);
            return;
        }
        for (auto pool : pools) {
            QString pool_name = QString::fromStdString(pool->name());
            ui->pool_comboBox->addItem(pool_name, QVariant::fromValue(pool));
        }
        ui->label_pool->setHidden(false);
        ui->pool_comboBox->setHidden(false);
        ui->input_quantity_lineEdit->setHidden(false);
        ui->label_outputQuantity->setHidden(false);
        ui->output_quantity_lineEdit->setHidden(false);
        ui->label_slippage->setHidden(false);
        ui->lineEdit_slippage->setHidden(false);
        ui->pushButton->setDisabled(false);
    }
    UpdateSelection();
    UpdateOutputQuantity();
}

void TradeDialog::on_pool_comboBox_currentIndexChanged(int index)
{
    UNUSED(index);
    UpdateSelection();
    UpdateOutputQuantity();
}

void TradeDialog::on_input_quantity_lineEdit_textChanged(const QString &input_quantity_string)
{
    UNUSED(input_quantity_string);
    UpdateSelection();
    UpdateOutputQuantity();
}

void TradeDialog::on_pushButton_clicked()
{
    if (!ValidNumber(ui->input_quantity_lineEdit->text().toStdString())) {
        QMessageBox::about(this, "Trade failed", "Please provide a valid input quantity!");
    } else {
        if (selection_.Valid()) {
            emit TradeRequest(selection_.pool_, selection_.input_token_, selection_.output_token_, selection_.input_quantity_);
        }
        else {
            QMessageBox::about(this, "Trade failed", "Please enter all required informations!");
        }
    }
}

void TradeDialog::UpdateSelection()
{
    selection_.Reset();
    if (ui->input_token_comboBox->currentIndex() != -1) {
        selection_.input_token_ = qvariant_cast<Token *>(ui->input_token_comboBox->currentData());
    }
    if (ui->output_token_comboBox->currentIndex() != -1) {
        selection_.output_token_ = qvariant_cast<Token *>(ui->output_token_comboBox->currentData());
    }
    if (ui->pool_comboBox->currentIndex() != -1) {
        selection_.pool_ = qvariant_cast<PoolInterface *>(ui->pool_comboBox->currentData());
    }
    if (ui->input_quantity_lineEdit->text().toDouble() > 0) {
        selection_.input_quantity_ = ui->input_quantity_lineEdit->text().toDouble();
    }
}

void TradeDialog::UpdateOutputQuantity()
{
    if (selection_.Valid()) {
        double output_quantity = playground_->SimulateSwap(selection_.pool_, selection_.input_token_, selection_.output_token_, selection_.input_quantity_);
        ui->output_quantity_lineEdit->setText(QString::number(output_quantity));

        double slippage = selection_.pool_->GetSlippage(selection_.input_token_, selection_.output_token_, selection_.input_quantity_);
        ui->lineEdit_slippage->setText(QString::number(slippage*100));

    } else {
        ui->output_quantity_lineEdit->clear();
        ui->lineEdit_slippage->clear();
    }
}

Selection::Selection()
{
    pool_ = nullptr;
    input_token_ = nullptr;
    output_token_ = nullptr;
    input_quantity_ = 0;
}

bool Selection::Valid() const
{
    return pool_ && input_token_ && output_token_ && input_quantity_;
}

void Selection::Reset()
{
    pool_ = nullptr;
    input_token_ = nullptr;
    output_token_ = nullptr;
    input_quantity_ = 0;
}
