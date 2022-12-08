#include "Playground.h"
#include <string>
#include <iostream>

Playground::Playground(QObject *parent)
    : QObject{parent},
      tokens({Token::GetToken("token1"), Token::GetToken("token2")}),
      accounts({Account::GetAccount("Alice"), Account::GetAccount("Bob")})
{

}

void Playground::callMe()
{
    static int count = 2;
    tokens.emplace(Token::GetToken("token" + std::to_string(++count)));
    std::cerr << "Tokens: ";
    for (auto token : tokens) {
        std::cerr << token->name() << ' ';
    }
    std::cerr << '\n';
    std::cerr << "Accounts: ";
    for (auto account : accounts) {
        std::cerr << account->name() << ' ';
    }
    std::cerr << '\n';

}
