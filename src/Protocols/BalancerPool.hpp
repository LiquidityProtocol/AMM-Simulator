#ifndef BALANCER_POOL_HPP
#define BALANCER_POOL_HPP

#include <unordered_map>
#include <stdexcept>
#include <cmath>
#include "PoolInterface.hpp"
#include "Token.hpp"

class BalancerPool : public PoolInterface {
public:
    BalancerPool(std::unordered_map<Token *, double> quantities, std::unordered_map<Token *, double> weights, double pool_fee = 0) : PoolInterface(quantities, pool_fee) {
        double weights_sum = 0;
        for (auto [token, weight] : weights) {
            if (weight <= 0) {
                throw std::invalid_argument("invalid weights");
            }
            weights_sum += weight;
        }
        if (weights_sum != 1) {
            throw std::invalid_argument("invalid weights");
        } else {
            weights_ = weights;
        }
    }
private:
    std::unordered_map<Token *, double> weights_;

    double GetWeight(Token *token) const {
        if (!weights_.count(token)) {
            throw std::invalid_argument("invalid token");
        }
        return weights_.find(token)->second;
    }

    double ComputeSwappedQuantity(Token *input_token, Token *output_token, double input_quantity) const {
        return GetQuantity(output_token) - GetQuantity(output_token) * std::pow(GetQuantity(input_token) / (GetQuantity(input_token) + (1 - pool_fee()) * input_quantity), GetWeight(input_token) / GetWeight(output_token));
    }
};

#endif