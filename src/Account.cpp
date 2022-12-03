#include "Account.hpp"

Account * Account::GetAccount(const std::string &name)  {
    if (!existing_accounts_.count(name)) {
        existing_accounts_[name] = new Account(name);
    }
    return existing_accounts_[name];
}
std::string Account::name() const {
    return name_;
}
double Account::total_value() const {
    return total_value_;
}

double Account::GetQuantity(Token *token) const {
    return wallet_.count(token) ? wallet_.find(token)->second : 0;
}

double Account::GetValue(Token *token) const {
    return GetQuantity(token) * token->real_value();
}

void Account::Deposit(Token *token, double quantity) {
    wallet_[token] += quantity;
    total_value_ += quantity * token->real_value();
}

std::unordered_map<std::string, Account *> Account::existing_accounts_ = std::unordered_map<std::string, Account *>();