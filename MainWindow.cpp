#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "src/Utilities/Utilities.hpp"
#include "AccountListWidgetItem.h"
#include "TokenListWidgetItem.h"
#include <QMessageBox>
#include <tuple>
#include "src/Playground.hpp"
#include "PoolListWidgetItem.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    playground_ = new Playground;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_create_toekn_pushButton_clicked()
{
    std::string token_name = ui->lineEdit_2->text().toStdString();
    double token_price = ui->lineEdit_3->text().toDouble();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    Token *token; bool is_new; std::tie(token, is_new) = playground_->GetToken(token_name, token_price);
    if (!is_new) {
        QMessageBox::about(this, "Adding token failed", "This name has been used by another token!");
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
    ui->lineEdit->clear();
    Account *account; bool is_new; std::tie(account, is_new) = playground_->GetAccount(account_name);
    if (!is_new) {
        QMessageBox::about(this, "Adding account failed", "This name has been used by another account!");
    } else {
        QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
        ui->listWidget->addItem(item);
        AccountListWidgetItem *account_item = new AccountListWidgetItem(this, playground_, account);
        item->setSizeHint(account_item->sizeHint());
        ui->listWidget->setItemWidget(item, account_item);
    }

}

void MainWindow::VerifyAddPoolInfo(PoolInterface* curr_pool) {
    QListWidgetItem *item = new QListWidgetItem(ui->listWidget_pool);
    ui->listWidget_pool->addItem(item);
    PoolListWidgetItem *pool_item = new PoolListWidgetItem(this, curr_pool);
    //item->setSizeHint(account_item->sizeHint());
    ui->listWidget_pool->setItemWidget(item, pool_item);
}
