#include "Utilities.hpp"
#include "../Protocols/UniswapV2Pool.hpp"

std::pair<Account *, bool> Account::GetAccount(const std::string &name) {
    if (existing_accounts_.count(name)) {
        return {existing_accounts_[name], false};
    } else {
        existing_accounts_in_chronological_order.emplace_back(new Account(name));
        return {existing_accounts_[name] = existing_accounts_in_chronological_order.back(), true};
    }
}

std::string Account::name() const {
    return name_;
}

double Account::total_value() const {
    return total_value_;
}

std::unordered_map<Token *, double> Account::wallet() const {
    return wallet_;
}

std::vector<Operation *> Account::ledger() const {
    return ledger_;
}

double Account::GetQuantity(Token *token) const {
    return wallet_.count(token) ? wallet_.find(token)->second : 0;
}

void Account::Deposit(Token *token, double quantity) {
    wallet_[token] += quantity;
    total_value_ += quantity * token->real_value();
}

void Account::Trade(Token *input_token, Token *output_token, double input_quantity) {
    ledger_.emplace_back(UniswapV2Pool::Swap(this, input_token, output_token, input_quantity));
}

void Account::Provide(Token *token1, Token *token2, double quantity1, double quantity2, double pool_fee = 0) {
    ledger_.emplace_back(UniswapV2Pool::Provide(this, token1, token2, quantity1, quantity2, pool_fee));
}

void Account::Withdraw(Token *pool_token, double surrendered_pool_token_quantity) {
    ledger_.emplace_back(UniswapV2Pool::Withdraw(this, pool_token, surrendered_pool_token_quantity));
}

std::vector<Account *> Account::existing_accounts() {
    return existing_accounts_in_chronological_order;
}
Account::Account(const std::string &name) : name_(name), total_value_(0), wallet_() {}
