#ifndef UNISWAP_V3_POOL_HPP
#define UNISWAP_V3_POOL_HPP

#include <cmath>
#include "../Utilities/Utilities.hpp"

class UniswapV3Pool : public PoolInterface {
public:
    UniswapV3Pool(std::unordered_map<Token *, double> quantities,
                  double pool_fee, 
                  double slippage_controller) : PoolInterface(quantities, pool_fee) {
        if(slippage_controller<1){
            throw std::invalid_argument("invalid slippage controller");
        }
        else{
            slippage_controller_ = slippage_controller;
        }
    
        double r1 = quantities.begin() -> second;
        double r2 = (++quantities.begin()) -> second;

        double C1 = r1;
        double C2 = r2;
    }

private:
    double C1, C2;
    double slippage_controller_;

    double ComputeInvariant() const {
        return slippage_controller_ * C1 * C2 /((sqrt(slippage_controller_) - 1) * (sqrt(slippage_controller_) - 1));
    }
    double ComputeSpotExchangeRate(Token *input_token, Token *output_token) const {
        double r1 = GetQuantity(input_token);
        double r2 = GetQuantity(output_token);
        return (r1 + C1/(sqrt(slippage_controller_) - 1))/(r2 + C2/(sqrt(slippage_controller_) - 1));
    }
    double ComputeSwappedQuantity(Token *input_token, Token *output_token, double input_quantity) const {
        double r1 = GetQuantity(input_token);
        double r2 = GetQuantity(output_token);
        double r1_prime = (r1 + input_quantity);
        double B = (1-1/sqrt(slippage_controller_))*(1-1/sqrt(slippage_controller_));
        return  r2 - (C1*C2/(B*(r1_prime + C1/(sqrt(slippage_controller_)-1))) - C2/(sqrt(slippage_controller_)-1));
    }
};

#endif