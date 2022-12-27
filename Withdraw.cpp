#include "Withdraw.h"
#include "ui_Withdraw.h"
#include "AccountListWidgetItem.h"
#include "src/Playground.hpp"
#include <QMessageBox>

Withdraw::Withdraw(QWidget *parent, Playground *playground) :
    QDialog(parent),
    ui(new Ui::Withdraw),
    playground_(playground)
{
    ui->setupUi(this);
    connect(this, &Withdraw::SendData, qobject_cast<AccountListWidgetItem *>(parent), &AccountListWidgetItem::VerifyData);

    for (auto token : playground_->existing_tokens()) {
        ui->comboBox->addItem(QString::fromStdString(token->name()));
    }
}

Withdraw::~Withdraw()
{
    delete ui;
}
