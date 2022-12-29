#include "NewPoolProvisionDialog.h"
#include "ui_NewPoolProvisionDialog.h"
#include "src/Protocols/Protocols.hpp"

NewPoolProvisionDialog::NewPoolProvisionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewPoolProvisionDialog)
{
    ui->setupUi(this);
    for (const auto &[protocol, protocol_name] : PROTOCOL_NAME) {
        ui->comboBox_protocol->addItem(QString::fromStdString(protocol_name), protocol);
    }
    ui->comboBox_protocol->setCurrentIndex(-1);
    ui->tableWidget_tokens->setHidden(true);
//    for (int row = 0; row < ui->tableWidget_tokens->rowCount() - 1; ++row) {
//        ui->tableWidget_tokens->setCellWidget(row, 0, new QComboBox);
//    }
    ui->label_poolFee->setHidden(true);
    ui->comboBox_poolFee->setHidden(true);
    ui->label_slippageController->setHidden(true);
    ui->lineEdit_slippageController->setHidden(true);
    ui->pushButton_provide->setDisabled(true);
}

NewPoolProvisionDialog::~NewPoolProvisionDialog()
{
    delete ui;
}

void NewPoolProvisionDialog::on_comboBox_protocol_activated(int index)
{
    if (index != -1) {
        PROTOCOL protocol = qvariant_cast<PROTOCOL>(ui->comboBox_protocol->currentData());
        ui->tableWidget_tokens->clearContents();
        ui->tableWidget_tokens->setHidden(false);
        if (protocol == PROTOCOL::CONSTANT_SUM || protocol == PROTOCOL::BALANCER) {
            ui->tableWidget_tokens->setColumnHidden(2, false);
        } else {
            ui->tableWidget_tokens->setColumnHidden(2, true);
        }
        ui->comboBox_poolFee->setCurrentIndex(-1);
        ui->label_poolFee->setHidden(false);
        ui->comboBox_poolFee->setHidden(false);
        ui->lineEdit_slippageController->clear();
        if (protocol == PROTOCOL::UNISWAP_V3 || protocol == PROTOCOL::CURVE) {
            ui->label_slippageController->setHidden(false);
            ui->lineEdit_slippageController->setHidden(false);
        } else {
            ui->label_slippageController->setHidden(true);
            ui->lineEdit_slippageController->setHidden(true);
        }
    }
}

void NewPoolProvisionDialog::on_tableWidget_tokens_cellClicked(int row, int column)
{
    std::cerr << row << ' ' << column << '\n';
}

