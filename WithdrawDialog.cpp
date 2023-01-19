#include "WithdrawDialog.h"
#include "ui_WithdrawDialog.h"
#include "AccountListWidgetItem.h"
#include "src/Protocols/Protocols.hpp"
#include <QMessageBox>

WithdrawDialog::WithdrawDialog(QWidget *parent, Playground *playground, Account *account) :
    QDialog(parent),
    ui(new Ui::WithdrawDialog),
    playground_(playground),
    account_(account)
{
    ui->setupUi(this);
    connect(this, &WithdrawDialog::WithdrawRequest, qobject_cast<AccountListWidgetItem*>(parent), &AccountListWidgetItem::VerifyWithdrawRequest);
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

    ui->lineEdit_withdraw->setHidden(true);

    ui->pushButton_withdraw->setDisabled(true);
}

WithdrawDialog::~WithdrawDialog()
{
    delete ui;
}

void WithdrawDialog::on_comboBox_protocol_activated(int index)
{
    if (index != -1) {
        PROTOCOL protocol = qvariant_cast<PROTOCOL>(ui->comboBox_protocol->currentData());
        ui->comboBox_pool->clear();
        std::unordered_set<PoolInterface *> withdrawable_pools;
        for (auto pool : playground_->GetPools(protocol)) {
            if (account_->GetQuantity(pool->pool_token())) {
                withdrawable_pools.emplace(pool);
            }
        }
        if (withdrawable_pools.empty()) {
            QMessageBox::about(this, "Invalid choice", "This account have no shares in current existing " + ui->comboBox_protocol->currentText() + " pools!");
            ui->comboBox_protocol->setCurrentIndex(-1);
            ui->label_pool->setHidden(true);
            ui->comboBox_pool->setHidden(true);
        } else {
            for (auto pool : withdrawable_pools) {
                QString pool_name = QString::fromStdString(std::to_string(reinterpret_cast<uint64_t>(pool)));
                ui->comboBox_pool->addItem(pool_name, QVariant::fromValue(pool));
            }
            ui->comboBox_pool->setCurrentIndex(-1);
            ui->label_pool->setHidden(false);
            ui->comboBox_pool->setHidden(false);
        }

        ui->tableWidget_pool->setHidden(true);

        ui->lineEdit_withdraw->setHidden(true);

        ui->pushButton_withdraw->setDisabled(true);
    }
}

void WithdrawDialog::on_comboBox_pool_activated(int index)
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

        ui->lineEdit_withdraw->clear();
        ui->lineEdit_withdraw->setHidden(false);

        ui->pushButton_withdraw->setDisabled(false);
    }
}

void WithdrawDialog::on_lineEdit_withdraw_textChanged(const QString &text)
{
    UNUSED(text);
    PoolInterface *curr_pool = qvariant_cast<PoolInterface *>(ui->comboBox_pool->currentData());

    double withdrawal_percentage = ui->lineEdit_withdraw->text().toDouble();

    if (withdrawal_percentage > 0 && withdrawal_percentage <= 100) {
        Token *pool_token = curr_pool->pool_token();
        double withdrawal_quantity = account_->GetQuantity(pool_token) * withdrawal_percentage / 100;
        std::unordered_map<Token *, double> quantities = playground_->SimulateWithdrawal(pool_token, withdrawal_quantity);

        for (int row = 0; row < ui->tableWidget_pool->rowCount(); ++row) {
            Token *token = playground_->GetToken(ui->tableWidget_pool->item(row, 0)->text().toStdString()).first;
            double token_withdrawal = quantities[token];
            ui->tableWidget_pool->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(std::to_string(token_withdrawal))));
        }
    } else if (withdrawal_percentage == 0) {
        for (int row = 0; row < ui->tableWidget_pool->rowCount(); ++row) {
            ui->tableWidget_pool->setItem(row, 2, new QTableWidgetItem("0"));
        }
    } else {
        QMessageBox::about(this, "Invalid withdrawal", "Please enter a valid percentage!");
    }
}

void WithdrawDialog::on_pushButton_withdraw_clicked()
{
    PoolInterface *curr_pool = qvariant_cast<PoolInterface *>(ui->comboBox_pool->currentData());
    Token *pool_token = curr_pool->pool_token();

    double withdrawal_percentage = ui->lineEdit_withdraw->text().toDouble();
    double withdrawal_quantity = account_->GetQuantity(pool_token)*withdrawal_percentage/100;

    emit WithdrawRequest(pool_token, withdrawal_quantity);
}
