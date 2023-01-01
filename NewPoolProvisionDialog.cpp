#include "NewPoolProvisionDialog.h"
#include "ui_NewPoolProvisionDialog.h"
#include "src/Protocols/Protocols.hpp"
#include "AccountListWidgetItem.h"
#include <QMessageBox>

NewPoolProvisionDialog::NewPoolProvisionDialog(QWidget *parent, Playground *playground) :
    QDialog(parent),
    ui(new Ui::NewPoolProvisionDialog),
    playground_(playground)
{
    ui->setupUi(this);
    connect(this, &NewPoolProvisionDialog::ProvideRequest1, qobject_cast<AccountListWidgetItem *>(parent), &AccountListWidgetItem::VerifyProvideRequest1);
    connect(this, &NewPoolProvisionDialog::ProvideRequest2, qobject_cast<AccountListWidgetItem *>(parent), &AccountListWidgetItem::VerifyProvideRequest2);
    connect(this, &NewPoolProvisionDialog::ProvideRequest3, qobject_cast<AccountListWidgetItem *>(parent), &AccountListWidgetItem::VerifyProvideRequest3);
    for (const auto &[protocol, protocol_name] : PROTOCOL_NAME) {
        ui->comboBox_protocol->addItem(QString::fromStdString(protocol_name), protocol);
    }
    ui->comboBox_protocol->setCurrentIndex(-1);
    QSizePolicy sp_retain = ui->tableWidget_tokens->sizePolicy();
    sp_retain.setRetainSizeWhenHidden(true);
    ui->tableWidget_tokens->setSizePolicy(sp_retain);
    for (int row = 0; row < ui->tableWidget_tokens->rowCount() - 1; ++row) {
        comboBoxes_tokens_.emplace_back(new QComboBox(this));
        for (auto token : playground_->existing_tokens()) {
            comboBoxes_tokens_.back()->addItem(QString::fromStdString(token->name()), QVariant::fromValue(token));
        }
        comboBoxes_tokens_.back()->setCurrentIndex(-1);
        ui->tableWidget_tokens->setCellWidget(row, 0, comboBoxes_tokens_.back());
        lineEdits_quantities_.emplace_back(new QLineEdit(this));
        ui->tableWidget_tokens->setCellWidget(row, 1, lineEdits_quantities_.back());
        lineEdits_weights_.emplace_back(new QLineEdit(this));
        ui->tableWidget_tokens->setCellWidget(row, 2, lineEdits_weights_.back());
    }
    connect(ui->tableWidget_tokens->verticalHeader(), &QHeaderView::sectionClicked, this, &NewPoolProvisionDialog::on_tableWidget_tokens_rowClicked);
    ui->tableWidget_tokens->setHidden(true);
    ui->label_poolFee->setHidden(true);
    ui->comboBox_poolFee->setHidden(true);
    ui->label_slippageController->setHidden(true);
    ui->lineEdit_slippageController->setHidden(true);
}

NewPoolProvisionDialog::~NewPoolProvisionDialog()
{
    delete ui;
}

void NewPoolProvisionDialog::on_comboBox_protocol_activated(int index)
{
    if (index != -1) {
        PROTOCOL protocol = qvariant_cast<PROTOCOL>(ui->comboBox_protocol->currentData());
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

void NewPoolProvisionDialog::on_tableWidget_tokens_rowClicked(int row)
{
    if (row < ui->tableWidget_tokens->rowCount() - 1) {
        ui->tableWidget_tokens->removeRow(row);
        comboBoxes_tokens_.erase(comboBoxes_tokens_.begin() + row);
        lineEdits_quantities_.erase(lineEdits_quantities_.begin() + row);
        lineEdits_weights_.erase(lineEdits_weights_.begin() + row);
    } else {
        ui->tableWidget_tokens->insertRow(row);
        ui->tableWidget_tokens->setVerticalHeaderItem(row, new QTableWidgetItem("-"));
        comboBoxes_tokens_.emplace_back(new QComboBox(this));
        for (auto token : playground_->existing_tokens()) {
            comboBoxes_tokens_.back()->addItem(QString::fromStdString(token->name()), QVariant::fromValue(token));
        }
        comboBoxes_tokens_.back()->setCurrentIndex(-1);
        ui->tableWidget_tokens->setCellWidget(row, 0, comboBoxes_tokens_.back());
        lineEdits_quantities_.emplace_back(new QLineEdit(this));
        ui->tableWidget_tokens->setCellWidget(row, 1, lineEdits_quantities_.back());
        lineEdits_weights_.emplace_back(new QLineEdit(this));
        ui->tableWidget_tokens->setCellWidget(row, 2, lineEdits_weights_.back());
    }
}

void NewPoolProvisionDialog::on_pushButton_provide_clicked()
{
    if (ui->comboBox_protocol->currentIndex() == -1) {
        QMessageBox::about(this, "Provide failed", "Please choose protocol!");
        return;
    }
    PROTOCOL protocol = qvariant_cast<PROTOCOL>(ui->comboBox_protocol->currentData());
    std::unordered_map<Token *, double> quantities;
    for (int i = 0; i < (int)comboBoxes_tokens_.size(); ++i) {
        if (comboBoxes_tokens_[i]->currentIndex() == -1) {
            continue;
        }
        Token *token = qvariant_cast<Token *>(comboBoxes_tokens_[i]->currentData());
        if (quantities.count(token)) {
            QMessageBox::about(this, "Provide failed", "Duplicate tokens are not allowed!");
            return;
        }
        quantities[token] = lineEdits_quantities_[i]->text().toDouble();
    }
    if (ui->comboBox_poolFee->currentIndex() == -1) {
        QMessageBox::about(this, "Provide failed", "Please choose pool fee!");
        return;
    }
    double pool_fee = ui->comboBox_poolFee->currentText().toDouble() / 100;
    if (protocol == PROTOCOL::UNISWAP_V2) {
        emit ProvideRequest1(protocol, quantities, pool_fee);
    } else if (protocol == PROTOCOL::UNISWAP_V3 || protocol == PROTOCOL::CURVE) {
        double slippage_controller = ui->lineEdit_slippageController->text().toDouble();
        emit ProvideRequest2(protocol, quantities, pool_fee, slippage_controller);
    } else if (protocol == PROTOCOL::CONSTANT_SUM || protocol == PROTOCOL::BALANCER) {
        std::unordered_map<Token *, double> weights;
        for (int i = 0; i < (int)comboBoxes_tokens_.size(); ++i) {
            if (comboBoxes_tokens_[i]->currentIndex() == -1) {
                continue;
            }
            Token *token = qvariant_cast<Token *>(comboBoxes_tokens_[i]->currentData());
            weights[token] = lineEdits_weights_[i]->text().toDouble();
        }
        emit ProvideRequest3(protocol, quantities, pool_fee, weights);
    }
}
