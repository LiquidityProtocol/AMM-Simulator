#ifndef POOL_INTERFACE_HPP
#define POOL_INTERFACE_HPP

#include <unordered_map>
#include <unordered_set>
#include <string>
#include <stdexcept>
#include <algorithm>
#include "Token.hpp"
#include "Account.hpp"

class PoolInterface {
public:
    PoolInterface(std::unordered_map<Token *, double> quantities, double pool_fee = 0) : quantities_(quantities) {
        if (quantities.size() < 2) {
            throw std::invalid_argument("not enough tokens");
        }
        if (pool_fee < 0 || pool_fee > 1) {
            throw std::invalid_argument("invalid pool fee");
        } else {
            pool_fee_ = pool_fee;
        }
        pool_token_ = Token::GetToken("PoolToken" + std::to_string(reinterpret_cast<uint64_t>(this)));
        quantities_[pool_token_] = 1;
    }

    bool InPool(Token *token) const {
        return quantities_.count(token);
    }

    double GetQuantity(Token *token) const {
        if (!InPool(token)) {
            throw std::invalid_argument("invalid token");
        }
        return quantities_.find(token)->second;
    }

    std::unordered_set<Token *> tokens() const {
        std::unordered_set<Token *> tokens;
        tokens.reserve(quantities_.size());
        for (auto [token, quantity] : quantities_) {
            if (token != pool_token_) {
                tokens.emplace(token);
            }
        }
        return tokens;
    }

    double SimulateSwap(Token *input_token, Token *output_token, double input_quantity) const {
        if (!InPool(input_token) || !InPool(output_token)) {
            throw std::invalid_argument("invalid token");
        } else if (input_quantity <= 0) {
            throw std::invalid_argument("invalid quantity");
        } else {
            return ComputeSwappedQuantity(input_token, output_token, input_quantity);
        }
    }

    double Swap(Account *trader, Token *input_token, Token *output_token, double input_quantity) {
        if (!CheckWallet(trader, {{input_token, input_quantity}})) {
            throw std::invalid_argument("not enough quantities in wallet");
        }
        double output_quantity = SimulateSwap(input_token, output_token, input_quantity);
        ExecuteSwap(trader, input_token, output_token, input_quantity, output_quantity);
        return output_quantity;
    }

    double SimulateProvision(std::unordered_map<Token *, double> input_quantities) const {
        if (!ValidProvision(input_quantities)) {
            throw std::invalid_argument("invalid provision");
        }
        Token* reference_token = *tokens().begin();
        double generated_pool_token_quantity = input_quantities[pool_token_] / (GetQuantity(reference_token) / input_quantities[reference_token]);
        return generated_pool_token_quantity;
    }

    double Provide(Account *provider, std::unordered_map<Token *, double> input_quantities) {
        if (!CheckWallet(provider, input_quantities)) {
            throw std::invalid_argument("not enough quantities in wallet");
        }
        double generated_pool_token_quantity = SimulateProvision(input_quantities);
        ExecuteProvision(provider, input_quantities, generated_pool_token_quantity);
        return generated_pool_token_quantity;
    }

    std::unordered_map<Token *, double> SimulateWithdrawal(double surrendered_pool_token_quantity) const {
        if (surrendered_pool_token_quantity > GetQuantity(pool_token_)) {
            throw std::invalid_argument("too many pool tokens");
        } else if (surrendered_pool_token_quantity <= 0) {
            throw std::invalid_argument("invalid quantity");
        }
        std::unordered_map<Token *, double> output_quantities;
        double ratio = surrendered_pool_token_quantity / GetQuantity(pool_token_);
        for (auto token : tokens()) {
            output_quantities[token] = GetQuantity(token) * ratio;
        }
        return output_quantities;
    }

    std::unordered_map<Token *, double> Withdraw(Account *provider, double surrendered_pool_token_quantity) {
        if (!CheckWallet(provider, {{pool_token_, surrendered_pool_token_quantity}})) {
            throw std::invalid_argument("not enough quantities in wallet");
        }
        std::unordered_map<Token *, double> output_quantities = SimulateWithdrawal(surrendered_pool_token_quantity);
        ExecuteWithdrawal(provider, surrendered_pool_token_quantity, output_quantities);
        return output_quantities;
    }
protected:
    virtual double ComputeSwappedQuantity(Token *input_token, Token *output_token, double input_quantity) const = 0;
private:
    std::unordered_map<Token *, double> quantities_;
    double pool_fee_;
    Token *pool_token_;

    bool CheckWallet(Account *account, const std::unordered_map<Token *, double> &quantities) const {
        for (auto [token, quantity] : quantities) {
            if (account->GetQuantity(token) < quantity) {
                return false;
            }
        }
        return true;
    }

    void ExecuteSwap(Account *trader, Token *input_token, Token *output_token, double input_quantity, double output_quantity) {
        quantities_[input_token] += input_quantity;
        trader->Deposit(input_token, -input_quantity);
        quantities_[output_token] -= output_quantity;
        trader->Deposit(output_token, output_quantity);
    }

    bool ValidProvision(std::unordered_map<Token *, double> quantities) const {
        double reference_ratio = -1;
        for (auto token : tokens()) {
            if (quantities[token] <= 0) {
                return false;
            }
            if (reference_ratio == -1) {
                reference_ratio = GetQuantity(token) / quantities[token];
            } else {
                if (GetQuantity(token) / quantities[token] != reference_ratio) {
                    return false;
                }
            }
        }
        return true;
    }

    void ExecuteProvision(Account *provider, std::unordered_map<Token *, double> input_quantities, double generated_pool_token_quantity) {
        for (auto [token, quantity] : input_quantities) {
            quantities_[token] += quantity;
            provider->Deposit(token, -quantity);
        }
        quantities_[pool_token_] += generated_pool_token_quantity;
        provider->Deposit(pool_token_, generated_pool_token_quantity);
    }

    void ExecuteWithdrawal(Account *provider, double surrendered_pool_token_quantity, std::unordered_map<Token *, double> output_quantities) {
        for (auto [token, quantity] : output_quantities) {
            quantities_[token] -= quantity;
            provider->Deposit(token, quantity);
        }
        quantities_[pool_token_] -= surrendered_pool_token_quantity;
        provider->Deposit(pool_token_, -surrendered_pool_token_quantity);
    }
};

#endif