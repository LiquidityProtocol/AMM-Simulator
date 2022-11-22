#ifndef UNISWAP_V2_POOL_HPP
#define UNISWAP_V2_POOL_HPP

#include "PoolInterface.hpp"
#include "PoolChunk.hpp"

class UniswapV2Pool : public PoolInterface {
public:
    using PoolInterface::PoolInterface;
private:
    PoolChunk ExecuteSwap(const PoolChunk &input) {
        Token *input_token = input.token();
        Token *output_token = GetOtherToken(input_token);
        PoolChunk output(output_token, quantities_[output_token] - quantities_[input_token] * quantities_[output_token] / (quantities_[input_token] + (1 - pool_fee_) * input.quantity()));
        quantities_[input_token] += input.quantity();
        quantities_[output_token] -= output.quantity();
        return output;
    }
};

#endif