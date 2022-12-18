#ifndef CURVE_POOL_HPP
#define CURVE_POOL_HPP

#include <cmath>
#include "../Utilities/Utilities.hpp"

class Curve : public PoolInterface {
public:
    Curve(std::unordered_map<Token *, double> quantities,
                  double pool_fee, 
                  double leverage = 0) : PoolInterface(quantities, pool_fee) {
    
        if(leverage<0) {
            throw std::invalid_argument("leverage can go from zero to infinity only");
        } else {
            leverage_ = leverage;
        }
    }
private:
    double leverage_;

    double ComputeInvariant(const std::unordered_map<Token *, double> &quantities) const {
        double sum = 0;
        double product = 1;
        int n = quantities.size();
        for (auto [token, quantity] : quantities) {
            sum += quantity;
            product *= quantity;
        }
        if (leverage_ < 1e-6) {
            return std::pow(product, 1 / n) * n;
        } else if (leverage_ > 1e10)    {
            return sum;
        } else if (abs(leverage_ == 1) < 1e-10) {
            return std::pow(product * sum * std::pow(n, n), 1 / (n + 1));
        }
        throw std::invalid_argument("unable to compute invariant");
    }
    double ComputeSpotExchangeRate(Token *input_token, Token *output_token) const {
        return ;
    }

    double ComputeSwappedQuantity(Token *input_token, Token *output_token, double input_quantity) const {
        return ;
    }

    double ComputeSlippage(Token *input_token, Token *output_token, double input_quantity) const {
        return ;
    }
};

#endif