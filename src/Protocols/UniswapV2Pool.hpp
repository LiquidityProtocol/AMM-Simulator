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
};

#endif