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
   QString userinput = ui->lineEdit->text();
   int flag = 0;
   int error = 0;
   QList<QChar> digits = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
   for (int i = 0; i < userinput.size(); i++) {
      if (userinput[i] == '.') {
          flag += 1;
      }
      else if ( (std::find(digits.begin(), digits.end(), userinput[i]) != digits.end()) != true ) {
          error += 1;
      }
   }

   if (flag > 1 || error != 0) {
       QMessageBox::about(this, "Minting token failed", "Please mint a number of tokens!");
       ui->lineEdit->clear();
   }
   else {
       emit SendData(playground_->GetToken(ui->comboBox->currentText().toStdString()).first, ui->lineEdit->text().toDouble());
   }
}
