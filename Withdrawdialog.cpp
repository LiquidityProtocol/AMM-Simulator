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
    emit WithdrawRequest(selection_.pool_, selection_.input_token_, account_->GetQuantity(selection_.input_token_));
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
    if (selection_.Valid()) {
        double output_quantity = 0;
        ui->output_quantity_lineEdit->setText(QString::number(output_quantity));
    } else {
        ui->output_quantity_lineEdit->clear();
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
