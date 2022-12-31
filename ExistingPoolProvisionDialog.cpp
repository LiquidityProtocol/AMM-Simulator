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
    //connect(this, &ExistingPoolProvisionDialog::ExistingProvideRequest2, qobject_cast<MainWindow *>(parent), &MainWindow::VerifyExistingProvideRequest);
    ui->comboBox_pool->setCurrentIndex(-1);
    std::unordered_set<PoolInterface *> pools = playground_->existing_pools();
    for (auto pool : pools) {
        QString pool_name = QString::fromStdString(std::to_string(reinterpret_cast<uint64_t>(pool)));
        ui->comboBox_pool->addItem(pool_name, QVariant::fromValue(pool));
    }
    ui->tableWidget_pool->setHidden(true);

    ui->label_Protocol->setHidden(true);
    ui->lineEdit_Protocol->setHidden(true);

    ui->label_poolFee->setHidden(true);
    ui->lineEdit_poolFee->setHidden(true);

    ui->comboBox_input_token->setHidden(true);
    ui->label_input_token->setHidden(true);
    ui->lineEdit_input_token->setHidden(true);
    ui->pushButton_provide->setHidden(true);
}

ExistingPoolProvisionDialog::~ExistingPoolProvisionDialog()
{
    delete ui;
}


void ExistingPoolProvisionDialog::on_comboBox_pool_activated(int index)
{
    if (index != -1) {
        //clear token list in comboBox_input_token
        ui->comboBox_input_token->clear();

        PoolInterface *curr_pool = qvariant_cast<PoolInterface *>(ui->comboBox_pool->currentData());
        PROTOCOL curr_protocol = GetPoolType(curr_pool);

        std::string prot_name = PROTOCOL_NAME.at(curr_protocol);
        ui->lineEdit_Protocol->setText(QString::fromStdString(prot_name));

        ui->lineEdit_poolFee->setText(QString::fromStdString(std::to_string(curr_pool->pool_fee()*100)));

        ui->tableWidget_pool->setHidden(false);

        ui->label_Protocol->setHidden(false);
        ui->lineEdit_Protocol->setHidden(false);

        ui->label_poolFee->setHidden(false);
        ui->lineEdit_poolFee->setHidden(false);

        ui->comboBox_input_token->setHidden(false);
        ui->label_input_token->setHidden(false);
        ui->lineEdit_input_token->setHidden(false);
        ui->pushButton_provide->setHidden(false);


        std::unordered_map<Token *, double> pool_tokens = curr_pool->quantities();
        int token_count = 0;
        for (auto [token, quantity] : pool_tokens) {
            int row_count = ui->tableWidget_pool->rowCount();
            if (token_count >= row_count) {
            ui->tableWidget_pool->insertRow(token_count);
            }
            ui->tableWidget_pool->setItem(token_count, 0, new QTableWidgetItem(QString::fromStdString(token->name())));
            ui->tableWidget_pool->setItem(token_count, 1, new QTableWidgetItem(QString::fromStdString(std::to_string(quantity))));
            token_count+=1;
        }

        std::unordered_set<Token *> tokens = curr_pool->tokens();
        for (auto token : tokens) {
            QString token_name = QString::fromStdString(token->name());
            ui->comboBox_input_token->addItem(token_name, QVariant::fromValue(token));
        }


    }
}


void ExistingPoolProvisionDialog::on_lineEdit_input_token_textChanged(const QString &inp_prov)
{
    PoolInterface *curr_pool = qvariant_cast<PoolInterface *>(ui->comboBox_pool->currentData());

    Token *input_token = qvariant_cast<Token *>(ui->comboBox_input_token->currentData());
    double input_token_quantity = curr_pool->GetQuantity(input_token);
    double input_token_provision = inp_prov.toDouble();

    if (input_token_provision>0) {


        for (auto [token, quantity] : curr_pool->quantities()) {
            double token_ratio = quantity/input_token_quantity;
            for (int i = 0 ; i < ui->tableWidget_pool->rowCount() ; ++i) {
                if (QString::fromStdString(token->name()) == ui->tableWidget_pool->item(i,0)->text()) {
                    ui->tableWidget_pool->setItem(i,2, new QTableWidgetItem(QString::fromStdString(std::to_string(input_token_provision*token_ratio))));
                }
            }

        }
    }
    else {
        std::string invalid = "Invalid input";

        for (auto token : curr_pool->tokens()) {
            for (int i = 0 ; i < ui->tableWidget_pool->rowCount() ; ++i) {
                if (QString::fromStdString(token->name()) == ui->tableWidget_pool->item(i,0)->text()) {
                    ui->tableWidget_pool->setItem(i,2, new QTableWidgetItem(QString::fromStdString(invalid)));
                }
            }
        }
    }
    }

void ExistingPoolProvisionDialog::on_pushButton_provide_clicked()
{
    if (ui->comboBox_pool->currentIndex() == -1) {
        QMessageBox::about(this, "Provide failed", "Please choose pool!");
        return;
    }

    PoolInterface *curr_pool = qvariant_cast<PoolInterface *>(ui->comboBox_pool->currentData());
    PROTOCOL curr_protocol = GetPoolType(curr_pool);
    QString invalid = QString("Invalid input");

    std::unordered_map<Token *, double> input_quantities;
    for (int i = 0 ; i < ui->tableWidget_pool->rowCount() ; ++i) {
        QString input_provision = ui->tableWidget_pool->item(i,2)->text();
        if (input_provision == invalid || input_provision.isEmpty()) {
            QMessageBox::about(this, "Provide failed", "Please submit valid input token quantity!");
            input_quantities.clear();
            return;
        }
        for (auto token : curr_pool->tokens()) {
            if (QString::fromStdString(token->name()) == ui->tableWidget_pool->item(i,0)->text()) {
                input_quantities[token] = input_provision.toDouble();
            }
        }
    }
    emit ExistingProvideRequest(curr_protocol, input_quantities);
    //emit ExistingProvideRequest2(curr_protocol, input_quantities);
}


