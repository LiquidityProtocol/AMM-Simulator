#ifndef UNISWAP_V2_POOL_HPP
#define UNISWAP_V2_POOL_HPP

#include "../Utilities/Utilities.hpp"

class UniswapV2Pool : public PoolInterface {
public:
    friend class Playground;
    friend class Market;

private:
    UniswapV2Pool(std::unordered_set<Token *> tokens, double pool_fee) : PoolInterface(tokens, pool_fee) {
        if (tokens.size() > 2) {
            throw std::invalid_argument("Uniswap V2 only supports for 2 tokens!");
        }
    }
    UniswapV2Pool(std::unordered_map<Token *, double> quantities, double pool_fee) : PoolInterface(quantities, pool_fee) {
        if (quantities.size() > 2) {
            throw std::invalid_argument("Uniswap V2 only supports for 2 tokens!");
        }
    }

    double ComputeInvariant(const std::unordered_map<Token *, double> &quantities) const {
        double ans = 1;
        for (auto [token, quantity] : quantities) {
            ans *= quantity;
        }
        return ans;
    }

    double ComputeSpotExchangeRate(Token *input_token, Token *output_token) const {
        return GetQuantity(input_token) / GetQuantity(output_token);
    }

    double ComputeSwappedQuantity(Token *input_token, Token *output_token, double input_quantity) const {
        return GetQuantity(output_token) - GetQuantity(input_token) * GetQuantity(output_token) / (GetQuantity(input_token) + input_quantity);
    }

    double ComputeSlippage(Token *input_token, Token *output_token, double input_quantity) const {
        return input_quantity / GetQuantity(input_token);
    }
};

#endif //UNISWAP_V2_POOL_HPP
