#include "Withdraw.h"
#include "ui_Withdraw.h"
#include "AccountListWidgetItem.h"
#include "src/Playground.hpp"
#include <QMessageBox>

Withdraw::Withdraw(QWidget *parent, Playground *playground, Account *account) :
    QDialog(parent),
    ui(new Ui::Withdraw),
    playground_(playground),
    account_(account)
{
    ui->setupUi(this);
}

Withdraw::~Withdraw()
{
    delete ui;
}

void Withdraw::on_pushButton_clicked()
{

}
