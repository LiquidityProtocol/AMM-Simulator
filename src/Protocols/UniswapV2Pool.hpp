#ifndef UNISWAP_V2_POOL_HPP
#define UNISWAP_V2_POOL_HPP

#include "../Utilities/Utilities.hpp"

class UniswapV2Pool : public PoolInterface {
public:
    using PoolInterface::PoolInterface;
private:
    double ComputeSwappedQuantity(Token *input_token, Token *output_token, double input_quantity) const {
        return GetQuantity(output_token) - GetQuantity(input_token) * GetQuantity(output_token) / (GetQuantity(input_token) + (1 - pool_fee()) * input_quantity);
    }

    double ComputeInvariant() const {
        double ans = 1;
        for(auto token : tokens())
            ans *= GetQuantity(token);
        return ans;
    }

    double ComputeSlippage(Token *input_token, Token *output_token, double input_quantity) const {
        return input_quantity / GetQuantity(input_token);
    }
};

#endif