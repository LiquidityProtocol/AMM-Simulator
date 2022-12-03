#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP

#include <unordered_map>
#include <stdexcept>
#include "Token.hpp"

class Account {
public:
    Account & operator=(const Account &) = delete;
	Account(const Account &) = delete;

    static Account * GetAccount(const std::string &name);

    std::string name() const;
    double total_value() const;

    double GetQuantity(Token *token) const;
    double GetValue(Token *token) const;

    void Deposit(Token *token, double quantity);

    // double Trade(PoolInterface *pool, Token *input_token, Token *output_token, double input_quantity) {
    //     return pool->Swap(this, input_token, output_token, input_quantity);
    // }

    // double Provide(PoolInterface *pool, std::unordered_map<Token *, double> provided_quantities) {
    //     return pool->Provide(this, provided_quantities);
    // }

    // std::unordered_map<Token *, double> Withdraw(PoolInterface *pool, double surrendered_quantity) {
    //     return pool->Withdraw(this, surrendered_quantity);
    // }
private:
    Account(const std::string &name) : name_(name), total_value_(0), wallet_() {}

    static std::unordered_map<std::string, Account *> existing_accounts_;
    std::string name_;
    double total_value_;
    std::unordered_map<Token *, double> wallet_;
};
#endif