#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "src/Utilities/Utilities.hpp"
#include "AccountListWidgetItem.h"
#include "TokenListWidgetItem.h"
#include "PoolListWidgetItem.h"
#include <QMessageBox>
#include <tuple>
#include "src/Playground.hpp"
#include "ChangeModeDialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    playground_ = new Playground;
    ChangeModeDialog* change = new ChangeModeDialog;
    change->exec();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_create_toekn_pushButton_clicked()
{
    if (!ValidNumber(ui->lineEdit_3->text().toStdString())) {
        QMessageBox::about(this, "Add token failed", "Please put a number as the price of the token!");
        return;
    }
    std::string token_name = ui->lineEdit_2->text().toStdString();
    if (token_name == ""){
        QMessageBox::about(this, "Add token failed", "Enter token name to create a new token!");
        return;
    }
    double token_price = ui->lineEdit_3->text().toDouble();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    Token *token; bool is_new; std::tie(token, is_new) = playground_->GetToken(token_name, token_price);
    if (!is_new) {
        QMessageBox::about(this, "Add token failed", "This name has been used by another token!");
    } else {
        QListWidgetItem *item = new QListWidgetItem(ui->listWidget_2);
        ui->listWidget_2->addItem(item);
        TokenListWidgetItem *token_item = new TokenListWidgetItem(this, token);
        item->setSizeHint(token_item->sizeHint());
        ui->listWidget_2->setItemWidget(item, token_item);
    }
}

void MainWindow::on_create_account_pushButton_clicked()
{
    std::string account_name = ui->lineEdit->text().toStdString();
    if (account_name == ""){
        QMessageBox::about(this, "Add account failed", "Enter account name to create a new account!");
        return;
    }
    ui->lineEdit->clear();
    Account *account; bool is_new; std::tie(account, is_new) = playground_->GetAccount(account_name);
    if (!is_new) {
        QMessageBox::about(this, "Add account failed", "This name has been used by another account!");
    } else {
        QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
        ui->listWidget->addItem(item);
        AccountListWidgetItem *account_item = new AccountListWidgetItem(this, playground_, account);
        item->setSizeHint(account_item->sizeHint());
        ui->listWidget->setItemWidget(item, account_item);
    }
}

void MainWindow::VerifyUpdatePoolDisplayRequest(PoolInterface *pool, double slippage) {
    for (int i = 0; i < ui->listWidget_pool->count(); ++i) {
        QListWidgetItem *item = ui->listWidget_pool->item(i);
        QWidget *item_widget = ui->listWidget_pool->itemWidget(item);
        PoolListWidgetItem *old_pool_item = qobject_cast<PoolListWidgetItem *>(item_widget);
        if (old_pool_item->pool() == pool) {
            if (!playground_->Existing(GetPoolType(pool), pool->tokens())) {
                ui->listWidget_pool->takeItem(i);
            } else {
                int input_token_idx = old_pool_item->get_comboBox_spotPrice_index();
                int second_token_idx = old_pool_item->get_comboBox_secondToken_index();
                PoolListWidgetItem *pool_item = new PoolListWidgetItem(this, playground_, pool, old_pool_item->curr_quantities(), old_pool_item->curr_spot_prices());
                pool_item->set_comboBox_spotPrice_index(input_token_idx);
                pool_item->set_comboBox_secondToken_index(second_token_idx);
                pool_item->set_slippage(slippage);
                item->setSizeHint(pool_item->sizeHint());
                ui->listWidget_pool->setItemWidget(item, pool_item);
            }
            return;
        }
    }
    QListWidgetItem *item = new QListWidgetItem(ui->listWidget_pool);
    ui->listWidget_pool->addItem(item);
    PoolListWidgetItem *pool_item = new PoolListWidgetItem(this, playground_, pool);
    item->setSizeHint(pool_item->sizeHint());
    ui->listWidget_pool->setItemWidget(item, pool_item);
}
