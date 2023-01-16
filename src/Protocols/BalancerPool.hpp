#ifndef BALANCER_POOL_HPP
#define BALANCER_POOL_HPP

#include <cmath>
#include "../Utilities/Utilities.hpp"

class BalancerPool : public PoolInterface {
public:
    friend class Playground;
    friend class Market;

private:
    std::unordered_map<Token *, double> weights_;

    BalancerPool(
        std::unordered_set<Token *> tokens,
        double pool_fee,
        std::unordered_map<Token *, double> weights
    ) : PoolInterface(tokens, pool_fee) {
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
    BalancerPool(
        std::unordered_map<Token *, double> quantities,
        double pool_fee,
        std::unordered_map<Token *, double> weights
    ) : PoolInterface(quantities, pool_fee) {
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

    double GetWeight(Token *token) const {
        if (!weights_.count(token)) {
            throw std::invalid_argument("invalid token");
        }
        return weights_.find(token)->second;
    }

    double ComputeInvariant(const std::unordered_map<Token *, double> &quantities) const {
        double ans = 1;
        for (auto [token, quantity] : quantities) {
            ans *= std::pow(quantity, GetWeight(token));
        }
        return ans;
    }

    double ComputeSpotExchangeRate(Token *input_token, Token *output_token) const {
        return (GetQuantity(input_token) * GetWeight(input_token)) / (GetQuantity(output_token) * GetWeight(output_token));
    }

    double ComputeSwappedQuantity(Token *input_token, Token *output_token, double input_quantity) const {
        double r1 = GetQuantity(input_token);
        double r2 = GetQuantity(output_token);

        double w1 = GetWeight(input_token);
        double w2 = GetWeight(output_token);

        return r2 - r2 * std::pow(r1 / (r1 + input_quantity), w1 / w2);
    }
    double ComputeInputRequirement(Token *input_token, Token *output_token, double output_quantity) const {
        double r1 = GetQuantity(input_token);
        double r2 = GetQuantity(output_token);

        double w1 = GetWeight(input_token);
        double w2 = GetWeight(output_token);

        return r1/ std::pow( (r2 - output_quantity) / r2, w2 / w1) - r1;
    }
};


#endif // BALANCER_POOL_HPP

