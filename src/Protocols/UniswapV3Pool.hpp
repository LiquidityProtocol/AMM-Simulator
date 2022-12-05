#ifndef UNISWAPV3_POOL_HPP
#define UNISWAPV3_POOL_HPP

#include <unordered_map>
#include <stdexcept>
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


};

#endif