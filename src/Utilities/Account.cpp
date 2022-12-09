#include "Utilities.hpp"

Account * Account::GetAccount(const std::string &name) {
    if (!existing_accounts_.count(name)) {
        existing_accounts_[name] = new Account(name);
        existing_accounts_in_chronological_order.emplace_back(existing_accounts_[name]);
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

double Account::Trade(PoolInterface *pool, Token *input_token, Token *output_token, double input_quantity) {
    ledger_.emplace_back(pool->Swap(this, input_token, output_token, input_quantity));
    return ledger_.back()->output()[output_token];
}

double Account::Provide(PoolInterface *pool, std::unordered_map<Token *, double> provided_quantities) {
    ledger_.emplace_back(pool->Provide(this, provided_quantities));
    return ledger_.back()->output()[pool->pool_token()];
}

std::unordered_map<Token *, double> Account::Withdraw(PoolInterface *pool, double surrendered_quantity) {
    ledger_.emplace_back(pool->Withdraw(this, surrendered_quantity));
    return ledger_.back()->output();
}

std::vector<Operation *> Account::ledger() const {
    return ledger_;
}

std::vector<Account *> Account::existing_accounts() {
    return existing_accounts_in_chronological_order;
}
