#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "src/Utilities/Utilities.hpp"
#include "AccountListWidgetItem.h"
#include "TokenListWidgetItem.h"
#include "MetricsTable.h"
#include <QMessageBox>
#include <tuple>
#include "cassert"

#include "src/Protocols/UniswapV2Pool.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Token::GetToken("Token1").first->set_real_value(10);
    Token::GetToken("Token2").first->set_real_value(20);
    Token::GetToken("Token4").first->set_real_value(40);

    /*
    UniswapV2Pool* pool_init;
    pool_init -> ({{Token::GetToken("Token1").first, 20}, {Token::GetToken("Token2").first, 10}});
    */

    QListWidgetItem *item = new QListWidgetItem(ui->listWidget_3);
    ui->listWidget_3->addItem(item);
    MetricsTable *table_item = new MetricsTable(this, nullptr);
    item->setSizeHint(table_item->sizeHint());
    ui->listWidget_3->setItemWidget(item, table_item);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    std::string account_name = ui->lineEdit->text().toStdString();
    ui->lineEdit->clear();
    Account *account; bool is_new; std::tie(account, is_new) = Account::GetAccount(account_name);
    if (!is_new) {
        QMessageBox::about(this, "Adding account failed", "This name has been used by another account!");
    } else {
        QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
        ui->listWidget->addItem(item);
        AccountListWidgetItem *account_item = new AccountListWidgetItem(this, account);
        item->setSizeHint(account_item->sizeHint());
        ui->listWidget->setItemWidget(item, account_item);
    }

}

void MainWindow::on_pushButton_2_clicked()
{
    std::string token_name = ui->lineEdit_2->text().toStdString();
    ui->lineEdit_2->clear();
    Token *token; bool is_new; std::tie(token, is_new) = Token::GetToken(token_name);
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

