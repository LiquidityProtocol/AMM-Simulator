#ifndef POOL_INTERFACE_HPP
#define POOL_INTERFACE_HPP

#include <unordered_map>
#include <unordered_set>
#include <stdexcept>
#include "Token.hpp"

class PoolInterface {
public:
    PoolInterface(std::unordered_map<Token *, double> quantities, double pool_fee = 0) : quantities_(quantities) {
        if (pool_fee < 0 || pool_fee > 1) {
            throw std::invalid_argument("invalid pool fee");
        } else {
            pool_fee_ = pool_fee;
        }
    }

    double Swap(Token *input_token, Token *output_token, double input_quantity) {
        if (!InPool(input_token) || !InPool(output_token)) {
            throw std::invalid_argument("invalid token");
        } else if (input_quantity <= 0) {
            throw std::invalid_argument("invalid quantity");
        } else {
            return ExecuteSwap(input_token, output_token, input_quantity);
        }
    }

    double GetSlippage(Token *input_token, Token *output_token, double input_quantity) {
        if (!InPool(input_token) || !InPool(output_token)) {
            throw std::invalid_argument("invalid token");
        } else if (input_quantity <= 0) {
            throw std::invalid_argument("invalid quantity");
        } else {
            return ComputeSlippage(input_token, output_token, input_quantity);
        }
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
            tokens.emplace(token);
        }
        return tokens;
    }
protected:
    std::unordered_map<Token *, double> quantities_;
    double pool_fee_;

    double ExecuteSwap(Token *input_token, Token *output_token, double input_quantity)  {
        double fees = input_quantity * pool_fee_;
        double output_quantity = ComputeSwappedQuantity(input_token, output_token, input_quantity - fees);

        quantities_[input_token] += input_quantity;
        quantities_[output_token] -= output_quantity;

        return output_quantity;
    }

    virtual double ComputeInvariant() = 0;
    virtual double ComputeSwappedQuantity(Token *input_token, Token *output_token, double input_quantity) = 0;
    virtual double ComputeSpotExchangeRate(Token *input_token, Token *output_token) {
        auto df = [&](Token *token) {
            const double eps = 1e-6;
            quantities_[token] -= eps;      double val1 = ComputeInvariant();
            quantities_[token] += eps*2;    double val2 = ComputeInvariant();
            quantities_[token] -= eps;

            return  (val2 - val1) / (2*eps);
        };
        return  df(input_token) / df(output_token);
    }
    virtual double ComputeSlippage(Token *input_token, Token *output_token, double input_quantity)  {
        double output_quantity = ComputeSwappedQuantity(input_token, output_token, input_quantity);
        double exchange_rate = ComputeSpotExchangeRate(input_token, output_token);

        return  input_quantity / output_quantity / exchange_rate - 1;
    }
};

#endif