#ifndef CONSTANT_SUM_HPP
#define CONSTANT_SUM_HPP

#include "../Utilities/Utilities.hpp"

class ConstantSum : public PoolInterface {
    /*Implementation of modified constant sum protocol:
    Description of Protocol: px+y=k; p is price when pool is initialised, x and y tokens respectively
    */
public:
    friend class Playground;
    friend class Market;

private:
    std::unordered_map<Token *, double> slopes_;

    ConstantSum(
        std::unordered_set<Token *> tokens,
        double pool_fee,
        std::unordered_map<Token *, double> slopes
    ) : PoolInterface(tokens, pool_fee) {
        double slope_sum = 0;
        for (auto [token, slope] : slopes) {
            if (slope <= 0)
                throw std::invalid_argument("invalid configuration of ConstantSum Protocol");
            slope_sum += slope;
        }
        for (auto [token, slope] : slopes) {
            slopes_[token] = slope / slope_sum;
        }
    }
    ConstantSum(std::unordered_map<Token *, double> quantities,
                double pool_fee,
                std::unordered_map<Token *, double> slopes
    ) : PoolInterface(quantities, pool_fee) {
        double slope_sum = 0;
        for (auto [token, slope] : slopes) {
            if (slope <= 0)
                throw std::invalid_argument("invalid configuration of ConstantSum Protocol");
            slope_sum += slope;
        }
        for (auto [token, slope] : slopes) {
            slopes_[token] = slope / slope_sum;
        }
    }
    
    double GetSlope(Token *token) const {
        if (!slopes_.count(token)) {
            throw std::invalid_argument("invalid token");
        }
        return slopes_.find(token)->second;
    }

    double ComputeInvariant(const std::unordered_map<Token *, double> &quantities) const {
        double ans = 0;
        for (auto [token, quantity] : quantities) {
            ans += quantity * GetSlope(token);
        }
        return ans;
    }

    double ComputeSpotExchangeRate(Token *input_token, Token *output_token) const {
        return GetSlope(output_token) / GetSlope(input_token);
    }

    double ComputeSwappedQuantity(Token *input_token, Token *output_token, double input_quantity) const {
        return input_quantity / ComputeSpotExchangeRate(input_token, output_token);
    }

    double ComputeSlippage(Token *input_token, Token *output_token, double input_quantity) const {
        return 0;
    }
};

#endif // CONSTANT_SUM_HPP