#include "Utilities.hpp"

std::string Account::name() const {
    return name_;
}

double Account::total_asset() const {
    double total_value = 0;
    for (auto [token, quantity] : wallet_) {
        total_value += quantity * token->real_value();
    }
    return total_value;
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
    if (token->pool()) {
        throw std::invalid_argument("pool token deposition is not allowed");
    }
    wallet_[token] += quantity;
    if (!wallet_[token]) {
        wallet_.erase(token);
    }
}

Account::Account(const std::string &name)
    : name_(name) {}

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
