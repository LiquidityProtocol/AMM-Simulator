#include "Utilities.hpp"

Account * Account::GetAccount(const std::string &name) {
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

double Account::Trade(PoolInterface *pool, Token *input_token, Token *output_token, double input_quantity) {
    double output_quantity = pool->Swap(this, input_token, output_token, input_quantity);
    Operation* operation = new Operation("TRADE", name(), pool, {{input_token, input_quantity}}, {{output_token, output_quantity}});
    ledger_.push_back(operation);
    return output_quantity;
}

double Account::Provide(PoolInterface *pool, std::unordered_map<Token *, double> provided_quantities) {
    double output_quantity = pool->Provide(this, provided_quantities);
    Operation* operation = new Operation("PROVIDE", name(), pool, provided_quantities, {{pool->pool_token(), output_quantity}});
    ledger_.push_back(operation);
    return output_quantity;
}

std::unordered_map<Token *, double> Account::Withdraw(PoolInterface *pool, double surrendered_quantity) {
    std::unordered_map<Token *, double> output_quantities = pool->Withdraw(this, surrendered_quantity);
    Operation* operation = new Operation("WITHDRAW", name(), pool, {{pool->pool_token(), surrendered_quantity}}, output_quantities);
    ledger_.push_back(operation);
    return output_quantities;
}

std::vector<Operation*> Account::GetLedger(){
    return ledger_;
}