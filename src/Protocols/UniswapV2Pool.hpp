#ifndef UNISWAP_V2_POOL_HPP
#define UNISWAP_V2_POOL_HPP

#include "../Utilities/Utilities.hpp"

class UniswapV2Pool : public PoolInterface {
public:
    static std::vector<UniswapV2Pool *> existing_pools();

    static UniswapV2Pool * GetPool(Token *token1, Token *token2);

    static bool Existing(Token *token1, Token *token2);

    static double SimulateSwap(Token *input_token, Token *output_token, double input_quantity);
    static Operation * Swap(Account *trader, Token *input_token, Token *output_token, double input_quantity);

    static double SimulateProvision(Token *token1, Token *token2, double quantity1, double quantity2);
    static Operation * Provide(Account *provider, Token *token1, Token *token2, double quantity1, double quantity2, double pool_fee = 0);

    static std::unordered_map<Token *, double> SimulateWithdrawal(Token *pool_token, double surrendered_pool_token_quantity);
    static Operation * Withdraw(Account *provider, Token *pool_token, double surrendered_pool_token_quantity);
private:
    static std::unordered_map<TokensContainer, UniswapV2Pool *> existing_pools_;
    static std::vector<UniswapV2Pool *> existing_pools_in_chronological_order_;

    using PoolInterface::PoolInterface;

    double ComputeInvariant(const std::unordered_map<Token *, double> &quantities) const;
    double ComputeSpotExchangeRate(Token *input_token, Token *output_token) const;
    double ComputeSwappedQuantity(Token *input_token, Token *output_token, double input_quantity) const;
    double ComputeSlippage(Token *input_token, Token *output_token, double input_quantity) const;
};

#endif //UNISWAP_V2_POOL_HPP
