#include "Utilities.hpp"

std::string Account::name() const {
    return name_;
}

double Account::budget() const {
    return budget_;
}
double Account::total_value() const {
    return total_value_ + budget_;
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
    total_value_ += quantity * token->real_value();
}

void Account::buy(Token *token, double quantity) {
    if (GetQuantity(token) < quantity) {
        throw std::invalid_argument("Not enough token to sell");
    } else {
        Deposit(token, -quantity);
        budget_ += quantity * token->real_value();
    }
}
void Account::sell(Token *token, double quantity) {
    if (budget_ < token->real_value() * quantity) {
        throw std::invalid_argument("Not enough cash to buy token");
    } else {
        Deposit(token, quantity);
        budget_ -= quantity * token->real_value();
    }
}

Account::Account(const std::string &name)
    : name_(name)
    , total_value_(0) {}

Account::Account(const std::string &name, double budget)
    : name_(name)
    , total_value_(0)
    , budget_(budget) {}

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
