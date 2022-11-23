#ifndef BALANCER_POOL_HPP
#define BALANCER_POOL_HPP

#include <unordered_map>
#include <stdexcept>
#include <cmath>
#include "PoolInterface.hpp"

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

    double ExecuteSwap(Token *input_token, Token *output_token, double input_quantity) {
        double output_quantity = quantities_[output_token] - quantities_[output_token] * std::pow(quantities_[input_token] / (quantities_[input_token] + (1 - pool_fee_) * input_quantity), weights_[input_token] / weights_[output_token]);
        quantities_[input_token] += input_quantity;
        quantities_[output_token] -= output_quantity;
        return output_quantity;
    }
};

#endif