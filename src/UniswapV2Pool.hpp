#ifndef UNISWAP_V2_POOL_HPP
#define UNISWAP_V2_POOL_HPP

#include "PoolInterface.hpp"

class UniswapV2Pool : public PoolInterface {
public:
    using PoolInterface::PoolInterface;
private:
    double ExecuteSwap(Token *input_token, Token *output_token, double input_quantity) {
        double output_quantity = ComputeSwapQuantity(input_token, output_token, input_quantity);
        quantities_[input_token] += input_quantity;
        quantities_[output_token] -= output_quantity;
        return output_quantity;
    }
    double ComputeSwapQuantity(Token *input_token, Token *output_token, double input_quantity)  {
        return quantities_[output_token] - quantities_[input_token] * quantities_[output_token] / (quantities_[input_token] + (1 - pool_fee_) * input_quantity);
    }
    double ComputeSlippage(Token *input_token, Token *output_token, double input_quantity)  {
        return  input_quantity / quantities_[input_token] - 1;
    }
    double ComputeDivergenceLoss(double p, Token *token)    {
        return  sqrt(1 + p) / (1 + p/2) - 1;
    }
};

#endif