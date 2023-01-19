#include "ExistingPoolProvisionDialog.h"
#include "ui_ExistingPoolProvisionDialog.h"
#include "src/Protocols/Protocols.hpp"
#include "AccountListWidgetItem.h"
#include "QMessageBox"

ExistingPoolProvisionDialog::ExistingPoolProvisionDialog(QWidget *parent, Playground *playground) :
    QDialog(parent),
    ui(new Ui::ExistingPoolProvisionDialog),
    playground_(playground)
{
    ui->setupUi(this);
    connect(this, &ExistingPoolProvisionDialog::ExistingProvideRequest, qobject_cast<AccountListWidgetItem *>(parent), &AccountListWidgetItem::VerifyExistingProvideRequest);

    for (const auto &[protocol, protocol_name] : PROTOCOL_NAME) {
        ui->comboBox_protocol->addItem(QString::fromStdString(protocol_name), protocol);
    }
    ui->comboBox_protocol->setCurrentIndex(-1);

    ui->label_pool->setHidden(true);
    ui->comboBox_pool->setHidden(true);

    QSizePolicy sp_retain = ui->tableWidget_pool->sizePolicy();
    sp_retain.setRetainSizeWhenHidden(true);
    ui->tableWidget_pool->setSizePolicy(sp_retain);
    ui->tableWidget_pool->setHidden(true);

    ui->label_poolFee->setHidden(true);
    ui->lineEdit_poolFee->setHidden(true);

    ui->comboBox_input_token->setHidden(true);
    ui->label_input_token->setHidden(true);
    ui->lineEdit_input_token->setHidden(true);

    ui->pushButton_provide->setDisabled(true);
}

ExistingPoolProvisionDialog::~ExistingPoolProvisionDialog()
{
    delete ui;
}

void ExistingPoolProvisionDialog::on_comboBox_protocol_activated(int index)
{
    if (index != -1) {
        PROTOCOL protocol = qvariant_cast<PROTOCOL>(ui->comboBox_protocol->currentData());
        ui->comboBox_pool->clear();
        std::unordered_set<PoolInterface *> pools = playground_->GetPools(protocol);
        for (auto pool : pools) {
            QString pool_name = QString::fromStdString(std::to_string(reinterpret_cast<uint64_t>(pool)));
            ui->comboBox_pool->addItem(pool_name, QVariant::fromValue(pool));
        }
        ui->comboBox_pool->setCurrentIndex(-1);
        ui->label_pool->setHidden(false);
        ui->comboBox_pool->setHidden(false);

        ui->tableWidget_pool->setHidden(true);

        ui->label_poolFee->setHidden(true);
        ui->lineEdit_poolFee->setHidden(true);

        ui->comboBox_input_token->setHidden(true);
        ui->label_input_token->setHidden(true);
        ui->lineEdit_input_token->setHidden(true);

        ui->pushButton_provide->setDisabled(true);
    }
}

void ExistingPoolProvisionDialog::on_comboBox_pool_activated(int index)
{
    if (index != -1) {
        PoolInterface *curr_pool = qvariant_cast<PoolInterface *>(ui->comboBox_pool->currentData());

        ui->tableWidget_pool->setRowCount(0);
        for (auto [token, quantity] : curr_pool->quantities()) {
            int row = ui->tableWidget_pool->rowCount();
            ui->tableWidget_pool->insertRow(row);
            ui->tableWidget_pool->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(token->name())));
            ui->tableWidget_pool->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(std::to_string(quantity))));
            ui->tableWidget_pool->setItem(row, 2, new QTableWidgetItem("0"));
        }
        ui->tableWidget_pool->setHidden(false);

        ui->lineEdit_poolFee->setText(QString::fromStdString(std::to_string(curr_pool->pool_fee() * 100)));
        ui->label_poolFee->setHidden(false);
        ui->lineEdit_poolFee->setHidden(false);

        ui->comboBox_input_token->clear();
        for (auto token : curr_pool->tokens()) {
            QString token_name = QString::fromStdString(token->name());
            ui->comboBox_input_token->addItem(token_name, QVariant::fromValue(token));
        }
        ui->comboBox_input_token->setCurrentIndex(-1);
        ui->lineEdit_input_token->clear();
        ui->label_input_token->setHidden(false);
        ui->comboBox_input_token->setHidden(false);
        ui->lineEdit_input_token->setHidden(false);

        ui->pushButton_provide->setDisabled(false);
    }
}

void ExistingPoolProvisionDialog::on_comboBox_input_token_activated(int index)
{
    UNUSED(index);
    UpdateProvision();
}

void ExistingPoolProvisionDialog::on_lineEdit_input_token_textChanged(const QString &input_token_provision_text)
{
    UNUSED(input_token_provision_text);
    UpdateProvision();
}

void ExistingPoolProvisionDialog::on_pushButton_provide_clicked()
{
    if (ui->comboBox_pool->currentIndex() == -1) {
        QMessageBox::about(this, "Provide failed", "Please choose pool!");
        return;
    }

    PROTOCOL curr_protocol = qvariant_cast<PROTOCOL>(ui->comboBox_protocol->currentData());

    std::unordered_map<Token *, double> input_quantities;
    for (int row = 0; row < ui->tableWidget_pool->rowCount(); ++row) {
        Token *token = playground_->GetToken(ui->tableWidget_pool->item(row, 0)->text().toStdString()).first;
        double token_provision = ui->tableWidget_pool->item(row, 2)->text().toDouble();
        input_quantities[token] = token_provision;
    }

    emit ExistingProvideRequest(curr_protocol, input_quantities);
}

void ExistingPoolProvisionDialog::UpdateProvision()
{
    PoolInterface *curr_pool = qvariant_cast<PoolInterface *>(ui->comboBox_pool->currentData());

    Token *input_token = qvariant_cast<Token *>(ui->comboBox_input_token->currentData());
    double input_token_quantity = curr_pool->GetQuantity(input_token);
    double input_token_provision = ui->lineEdit_input_token->text().toDouble();

    if (input_token && input_token_provision > 0) {
        double ratio = input_token_provision / input_token_quantity;
        for (int row = 0; row < ui->tableWidget_pool->rowCount(); ++row) {
            Token *token = playground_->GetToken(ui->tableWidget_pool->item(row, 0)->text().toStdString()).first;
            double token_provision = curr_pool->GetQuantity(token) * ratio;
            ui->tableWidget_pool->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(std::to_string(token_provision))));
        }
    }
    else {
        for (int row = 0; row < ui->tableWidget_pool->rowCount(); ++row) {
            ui->tableWidget_pool->setItem(row, 2, new QTableWidgetItem("0"));
        }
    }
}
