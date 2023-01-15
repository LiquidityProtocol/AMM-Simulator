#ifndef UNISWAP_V3_POOL_HPP
#define UNISWAP_V3_POOL_HPP

#include <cmath>
#include "../Utilities/Utilities.hpp"

class UniswapV3Pool : public PoolInterface {
public:
    friend class Playground;
    friend class Market;

private:
    std::unordered_map<Token *, double> weights_;
    double slippage_controller_;
    
    UniswapV3Pool(
        std::unordered_set<Token *> tokens,
        double pool_fee, 
        double slippage_controller
    ) : PoolInterface(tokens, pool_fee) {
        if (slippage_controller <= 1) {
            throw std::invalid_argument("invalid slippage controller");
        } else {
            slippage_controller_ = slippage_controller;
        }
    }
    UniswapV3Pool(
        std::unordered_map<Token *, double> quantities,
        double pool_fee, 
        double slippage_controller
    ) : PoolInterface(quantities, pool_fee) {
        if (slippage_controller <= 1) {
            throw std::invalid_argument("invalid slippage controller");
        } else {
            slippage_controller_ = slippage_controller;
        }
        weights_ = quantities;
    }

    double GetWeight(Token *token) const {
        return GetQuantity(pool_token()) / INITIAL_POOL_TOKEN_SUPPLY * weights_.find(token)->second;
    }

    double ComputeInvariant(const std::unordered_map<Token *, double> &quantities) const {
        double ans = 1;

        for (auto [token, weight] : weights_) {
            auto it = quantities.find(token);
            if (it != quantities.end()) {
                ans *= (it->second + weight / (sqrt(slippage_controller_) - 1));
            } else {
                throw std::invalid_argument("invalid input quantities");
            }
        }

        return ans;
    }

    double ComputeSpotExchangeRate(Token *input_token, Token *output_token) const {
        double r1 = GetQuantity(input_token), C1 = GetWeight(input_token);
        double r2 = GetQuantity(output_token), C2 = GetWeight(output_token);

        return (r1 + C1 / (sqrt(slippage_controller_) - 1)) / (r2 + C2 / (sqrt(slippage_controller_) - 1));
    }

    double ComputeSwappedQuantity(Token *input_token, Token *output_token, double input_quantity) const {
        double r1 = GetQuantity(input_token), C1 = GetWeight(input_token);
        double r2 = GetQuantity(output_token), C2 = GetWeight(output_token);

        double B = sqrt(slippage_controller_) - 1;

        double r1_prime = (r1 + input_quantity);
        double r2_prime = ComputeInvariant(quantities()) / (r1_prime + C1 / B) - C2 / B;

        return r2 - r2_prime;
    }

    double ComputeSlippage(Token *input_token, Token *output_token, double input_quantity) const {
        double r1 = GetQuantity(input_token);
        double C1 = GetWeight(input_token);

        return input_quantity / (r1 + C1 / (sqrt(slippage_controller_) - 1));
    }
};

#endif // UNISWAP_V3_POOL_HPP
