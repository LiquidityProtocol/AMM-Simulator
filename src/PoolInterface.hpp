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
    double Slippage(Token *input_token, Token *output_token, double input_quantity) {
        if (!InPool(input_token) || !InPool(output_token)) {
            throw std::invalid_argument("invalid token");
        } else if (input_quantity <= 0) {
            throw std::invalid_argument("invalid quantity");
        } else {
            return ComputeSlippage(input_token, output_token, input_quantity);
        }
    }
    double DivergenceLoss(double p, Token *token = nullptr) {
        if (!InPool(token)) {
            throw std::invalid_argument("invalid token");
        } else if (p <= -1) {
            throw std::invalid_argument("invalid change rate");
        } else
            return ComputeDivergenceLoss(p, token);
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

    virtual double ExecuteSwap(Token *input_token, Token *output_token, double input_quantity) = 0;
    virtual double ComputeSwapQuantity(Token *input_token, Token *output_token, double input_quantity) = 0;
    virtual double ComputeDivergenceLoss(double p, Token *token) = 0;
    virtual double ComputeSlippage(Token *input_token, Token *output_token, double input_quantity) = 0;
};

#endif