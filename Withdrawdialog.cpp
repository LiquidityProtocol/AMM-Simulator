#include "Withdrawdialog.h"
#include "ui_Withdrawdialog.h"
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
        ui->protocol_comboBox->addItem(QString::fromStdString(protocol_name), protocol);
    }
    ui->protocol_comboBox->setCurrentIndex(-1);
}

WithdrawDialog::~WithdrawDialog()
{
    delete ui;
}

void WithdrawDialog::on_protocol_comboBox_currentIndexChanged(int index)
{
    if (index == -1) {
        ui->pool_comboBox->clear();
    } else {
        ui->pool_comboBox->clear();
        PROTOCOL protocol = qvariant_cast<PROTOCOL>(ui->protocol_comboBox->currentData());
        std::unordered_set<PoolInterface *> pools = playground_->GetPoolsbyProtocol(protocol);
        for (auto pool : pools) {
            QString pool_name = QString::fromStdString(std::to_string(reinterpret_cast<uint64_t>(pool)));
            ui->pool_comboBox->addItem(pool_name, QVariant::fromValue(pool));
        }
    }
    UpdateSelection();
    UpdateOutputQuantity();
}


void WithdrawDialog::on_pool_comboBox_currentIndexChanged(int index)
{
    UpdateSelection();
    UpdateOutputQuantity();
}


void WithdrawDialog::on_pushButton_clicked()
{
    std::vector<Operation *> ledger = account_->ledger();
    std::unordered_map<Token *, double> Pool_token;
    for (int i = 0; i < ledger.size(); i++) {
       if (ledger[i]->account_name() == account_->name()) {
           if (ledger[i]->pool() == selection_.pool_) {
               Pool_token = ledger[i]->input();
           }
       }
    }
    for (auto& x: Pool_token) {
        emit WithdrawRequest(x.first, x.second);
    }
}

void WithdrawDialog::UpdateSelection()
{
    selection_.Reset();
    if (ui->pool_comboBox->currentIndex() != -1) {
        selection_.pool_ = qvariant_cast<PoolInterface *>(ui->pool_comboBox->currentData());
    }
}

void WithdrawDialog::UpdateOutputQuantity()
{
    std::vector<Operation *> ledger = account_->ledger();
    std::unordered_map<Token *, double> Pool_token;
    for (int i = 0; i < ledger.size(); i++) {
       if (ledger[i]->account_name() == account_->name()) {
           if (ledger[i]->pool() == selection_.pool_) {
               Pool_token = ledger[i]->input();
           }
       }
    }
    for (auto& x: Pool_token) {
        if (selection_.Valid()) {
            std::unordered_map<Token *, double> Output = playground_->SimulateWithdrawal(x.first, x.second);
            auto it = Output.begin();
            auto it2 = Output.end();
            ui->output_1_name_lineEdit->setText(QString::fromStdString((it->first)->name()));
            ui->output_1_quantity_lineEdit->setText(QString::number(it->second));
            ui->output_2_name_lineEdit->setText(QString::fromStdString((it2->first)->name()));
            ui->output_2_quantity_lineEdit->setText(QString::number(it2->second));
        } else {
            ui->output_1_name_lineEdit->clear();
            ui->output_1_quantity_lineEdit->clear();
            ui->output_2_name_lineEdit->clear();
            ui->output_2_quantity_lineEdit->clear();
        }
    }
}

Selection_2::Selection_2()
{
    pool_ = nullptr;
    input_token_ = nullptr;
}

bool Selection_2::Valid() const
{
    return pool_ && input_token_;
}

void Selection_2::Reset()
{
    pool_ = nullptr;
    input_token_ = nullptr;
}
