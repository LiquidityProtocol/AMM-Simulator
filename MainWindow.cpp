#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "src/Utilities/Utilities.hpp"
#include "AccountListWidgetItem.h"
#include <QMessageBox>
#include <tuple>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Token::GetToken("Token1")->set_real_value(10);
    Token::GetToken("Token2")->set_real_value(20);
    Token::GetToken("Token4")->set_real_value(40);
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
