#include "MintDialog.h"
#include "ui_MintDialog.h"
#include "AccountListWidgetItem.h"
#include <QMessageBox>

MintDialog::MintDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MintDialog)
{
    ui->setupUi(this);
    connect(this, &MintDialog::SendData, qobject_cast<AccountListWidgetItem *>(parent), &AccountListWidgetItem::VerifyData);

    for (auto token : Token::existing_tokens()) {
        ui->comboBox->addItem(QString::fromStdString(token->name()));
    }
}

MintDialog::~MintDialog()
{
    delete ui;
}

void MintDialog::on_pushButton_clicked()
{
    QString userinput = ui->lineEdit->text();
    int flag = 0;
    int error = 0;
    /*QList<QChar> chars;
    for (QChar c: userinput) {
        chars.push_back(c);
     }*/
    QList<QChar> digits = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    /*for (int k=0; k < 10; k++) {
        digits.push_back(char(k));
    }
    for (auto const &i: digits) {
        std::cout << &i << std::endl;
    }*/
    for (int i = 0; i < userinput.size(); i++) {
       if (userinput[i] == '.') {
           flag += 1;
       }
       else if ( (std::find(digits.begin(), digits.end(), userinput[i]) != digits.end()) != true ) {
           error += 1;
       }
    }

    if (flag > 1 || error != 0) {
        /*QMessageBox::about(this, "Minting failed", "Invalid input!");*/
        QMessageBox::about(this, "Minting token failed", "Please mint a number of tokens!");
    }
    else {
        emit SendData(Token::existing_tokens()[ui->comboBox->currentIndex()], ui->lineEdit->text().toDouble());
    }
}
