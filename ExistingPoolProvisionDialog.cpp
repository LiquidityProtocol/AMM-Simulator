#include "ExistingPoolProvisionDialog.h"
#include "ui_ExistingPoolProvisionDialog.h"

ExistingPoolProvisionDialog::ExistingPoolProvisionDialog(QWidget *parent, Playground *playground) :
    QDialog(parent),
    ui(new Ui::ExistingPoolProvisionDialog),
    playground_(playground)
{
    ui->setupUi(this);
    std::unordered_set<PoolInterface *> pools = playground_->existing_pools();
    for (auto pool : pools) {
        QString pool_name = QString::fromStdString(std::to_string(reinterpret_cast<uint64_t>(pool)));
        ui->comboBox_pool->addItem(pool_name, QVariant::fromValue(pool));
    }
    ui->comboBox_input_token->setHidden(true);
    ui->label_input_token->setHidden(true);
    ui->lineEdit_input_token->setHidden(true);
    ui->pushButton_provide->setHidden(true);
}

ExistingPoolProvisionDialog::~ExistingPoolProvisionDialog()
{
    delete ui;
}


void ExistingPoolProvisionDialog::on_pushButton_pool_select_clicked()
{
    PoolInterface *curr_pool = qvariant_cast<PoolInterface *>(ui->comboBox_pool->currentData());
    if (curr_pool) {
    ui->pushButton_pool_select->setHidden(true);

    ui->comboBox_input_token->setHidden(false);
    ui->label_input_token->setHidden(false);
    ui->lineEdit_input_token->setHidden(false);
    ui->pushButton_provide->setHidden(false);
    }
    else {
    std::cout << "I am working" << std::endl;
    }
}




