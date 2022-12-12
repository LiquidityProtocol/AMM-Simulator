#ifndef CURVE_POOL_HPP
#define CURVE_POOL_HPP

#include <cmath>
#include "../Utilities/Utilities.hpp"

class Curve : public PoolInterface {
public:
    Curve(std::unordered_map<Token *, double> quantities,
                  double pool_fee, 
                  double leverage=0) : PoolInterface(quantities, pool_fee) {
    
    if(leverage<0){
            throw std::invalid_argument("leverage can go from zero to infinity only");
    }
    else{
        leverage_ = leverage;
    }
}

private:
    
    double leverage_;

    double SumInvariant(std::unordered_map<Token *, double> quantities){
        double sum = 0;
        double product = 1;
        int n = quantities.size();
        for (auto [token, quantity] : quantities) {
            sum += quantity;
            product *= quantity;
        }
        if (leverage_ < 1e-10){
            return std::pow(product, 1/n) * n;
        } 
        if (leverage_ == 1){
            return std::pow(product * sum, 1 / (n + 1)) * std::pow(n, n/(n+1));
        }

        if (n == 2){
            return;

        }
        // raise Exception("cannot handle unequal asset pool with n>2")

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