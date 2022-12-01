#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP

#include <unordered_map>
#include <stdexcept>
#include "PoolInterface.hpp"
#include "Token.hpp"

class Account {
public:
    Account & operator=(const Account &) = delete;
	Account(const Account &) = delete;

    static Account * GetAccount(const std::string &name) {
		if (!existing_accounts_.count(name)) {
			existing_accounts_[name] = new Account(name);
		}
		return existing_accounts_[name];
	}

    std::string name() const {
        return name_;
    }

    double total_value() const {
        return total_value_;
    }

    double GetQuantity(Token *token) const {
        return wallet_.count(token) ? wallet_.find(token)->second : 0;
    }

    double GetValue(Token *token) const {
        return GetQuantity(token) * token->real_value();
    }

    void Deposit(Token *token, double quantity) {
        wallet_[token] += quantity;
        total_value_ += quantity * token->real_value();
    }

    void Trade(PoolInterface *pool, Token *input_token, Token *output_token, double input_quantity) {
        if (input_quantity > GetQuantity(input_token)) {
            throw std::invalid_argument("not enough " + input_token->name() + "s");
        } else {
            double output_quantity = pool->Swap(input_token, output_token, input_quantity);
            Deposit(input_token, -input_quantity);
            Deposit(output_token, output_quantity);
            total_value_ -= input_quantity * input_token->real_value();
            total_value_ += output_quantity * output_token->real_value();
        }
    }

    std::unordered_map<Token *, double> GetWallet() {
        return wallet_;
    }

private:
    Account(const std::string &name) : name_(name), total_value_(0), wallet_() {}

    static std::unordered_map<std::string, Account *> existing_accounts_;
    std::string name_;
    double total_value_;
    std::unordered_map<Token *, double> wallet_;
};

std::unordered_map<std::string, Account *> Account::existing_accounts_ = std::unordered_map<std::string, Account *>();

#endif