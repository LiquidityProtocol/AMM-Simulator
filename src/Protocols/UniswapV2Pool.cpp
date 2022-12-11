#include "UniswapV2Pool.hpp"

UniswapV2Pool * UniswapV2Pool::GetPool(Token *token1, Token *token2) {
    TokensContainer tokens_container({token1, token2});
    if (existing_pools_.count(tokens_container)) {
        return existing_pools_[tokens_container];
    } else {
        throw std::invalid_argument("there is no existing pool with corresponding tokens");
    }
}

bool UniswapV2Pool::Existing(Token *token1, Token *token2) {
    return existing_pools_.count(TokensContainer({token1, token2}));
}

double UniswapV2Pool::SimulateSwap(Token *input_token, Token *output_token, double input_quantity) {
    if (Existing(input_token, output_token)) {
        UniswapV2Pool *pool = existing_pools_[TokensContainer({input_token, output_token})];
        return pool->SpecificSimulateSwap(input_token, output_token, input_quantity);
    } else {
        throw std::invalid_argument("there is no existing pool with corresponding tokens");
    }
}

Operation * UniswapV2Pool::Swap(Account *trader, Token *input_token, Token *output_token, double input_quantity) {
    if (Existing(input_token, output_token)) {
        UniswapV2Pool *pool = existing_pools_[TokensContainer({input_token, output_token})];
        return pool->SpecificSwap(trader, input_token, output_token, input_quantity);
    } else {
        throw std::invalid_argument("there is no existing pool with corresponding tokens");
    }
}

double UniswapV2Pool::SimulateProvision(Token *token1, Token *token2, double quantity1, double quantity2) {
    if (Existing(token1, token2)) {
        UniswapV2Pool *pool = existing_pools_[TokensContainer({token1, token2})];
        return pool->SpecificSimulateProvision({{token1, quantity1}, {token2, quantity2}});
    } else {
        return FIRST_POOL_TOKEN_SUPPLY;
    }
}

Operation * UniswapV2Pool::Provide(Account *provider, Token *token1, Token *token2, double quantity1, double quantity2, double pool_fee) {
    UniswapV2Pool *pool = nullptr;
    if (Existing(token1, token2)) {
        pool = existing_pools_[TokensContainer({token1, token2})];
    } else {
        pool = existing_pools_[TokensContainer({token1, token2})] = new UniswapV2Pool({token1, token2}, pool_fee);
    }
    return pool->SpecificProvide(provider, {{token1, quantity1}, {token2, quantity2}});
}

std::unordered_map<Token *, double> UniswapV2Pool::SimulateWithdrawal(Token *pool_token, double surrendered_pool_token_quantity) {
    if (pool_token->pool()) {
        return pool_token->pool()->SpecificSimulateWithdrawal(surrendered_pool_token_quantity);
    } else {
        throw std::invalid_argument("invalid pool token");
    }
}

Operation * UniswapV2Pool::Withdraw(Account *provider, Token *pool_token, double surrendered_pool_token_quantity) {
    if (pool_token->pool()) {
        PoolInterface *pool = pool_token->pool();
        Operation *operation = pool->SpecificWithdraw(provider, surrendered_pool_token_quantity);
        if (!pool->GetQuantity(pool_token)) {
            existing_pools_.erase(TokensContainer(pool->tokens()));
        }
        return operation;
    } else {
        throw std::invalid_argument("invalid pool token");
    }
}

double UniswapV2Pool::ComputeInvariant(const std::unordered_map<Token *, double> &quantities) const {
    double ans = 1;
    for (auto [token, quantity] : quantities) {
        ans *= quantity;
    }
    return ans;
}

double UniswapV2Pool::ComputeSpotExchangeRate(Token *input_token, Token *output_token) const {
    return GetQuantity(input_token) / GetQuantity(output_token);
}

double UniswapV2Pool::ComputeSwappedQuantity(Token *input_token, Token *output_token, double input_quantity) const {
    return GetQuantity(output_token) - GetQuantity(input_token) * GetQuantity(output_token) / (GetQuantity(input_token) + input_quantity);
}

double UniswapV2Pool::ComputeSlippage(Token *input_token, Token *output_token, double input_quantity) const {
    return input_quantity / GetQuantity(input_token);
}
