#ifndef UNISWAP_V2_POOL_HPP
#define UNISWAP_V2_POOL_HPP

#include "PoolInterface.hpp"

class UniswapV2Pool : public PoolInterface {
public:
    using PoolInterface::PoolInterface;
private:
    double ComputeInvariant()   {
        double ans = 1;
        for(auto [token, quantity] : quantities_)
            ans *= quantity;
        return  ans;
    }
    double ComputeSwappedQuantity(Token *input_token, Token *output_token, double input_quantity)   {
        return quantities_[output_token] - ComputeInvariant() / (quantities_[input_token] + input_quantity);
    }
    double ComputeSlippage(Token *input_token, Token *output_token, double input_quantity)  {
        return input_quantity / quantities_[input_token];
    }

};

#endif