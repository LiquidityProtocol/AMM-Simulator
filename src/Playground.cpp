#include "Playground.hpp"

std::pair<Token *, bool> Playground::GetToken(const std::string &name, double real_value) {
    if (existing_tokens_.count(name)) {
        return {existing_tokens_[name], false};
    } else {
        return {existing_tokens_[name] = new Token(name, real_value), true};
    }
}

std::unordered_set<Token *> Playground::existing_tokens() const {
    std::unordered_set<Token *> tokens; tokens.reserve(existing_tokens_.size());
    for (const auto &[name, token] : existing_tokens_) {
        tokens.emplace(token);
    }
    return tokens;
}

std::pair<Account *, bool> Playground::GetAccount(const std::string &name) {
    if (existing_accounts_.count(name)) {
        return {existing_accounts_[name], false};
    } else {
        return {existing_accounts_[name] = new Account(name), true};
    }
}

std::unordered_set<Account *> Playground::existing_accounts() const {
    std::unordered_set<Account *> accounts; accounts.reserve(existing_accounts_.size());
    for (const auto &[name, account] : existing_accounts_) {
        accounts.emplace(account);
    }
    return accounts;
}

std::unordered_set<PoolInterface *> Playground::existing_pools() const {
    std::unordered_set<PoolInterface *> pools;
    for (const auto &[protocol, tokens_container_to_pool] : existing_pools_) {
        for (const auto &[tokens_container, pool] : tokens_container_to_pool) {
            pools.emplace(pool);
        }
    }
    return pools;
}

bool Playground::Existing(PROTOCOL protocol, const std::unordered_set<Token *> &tokens) const {
    return existing_pools_.count(protocol) && existing_pools_.find(protocol)->second.count(TokensContainer(tokens));
}

PoolInterface * Playground::GetPool(PROTOCOL protocol, const std::unordered_set<Token *> &tokens) const {
    if (!Existing(protocol, tokens)) {
        throw std::invalid_argument("this pool does not exist");
    }
    return existing_pools_.find(protocol)->second.find(TokensContainer(tokens))->second;
}

std::unordered_set<PoolInterface *> Playground::GetPools(PROTOCOL protocol, Token *input_token, Token *output_token) const {
    std::unordered_set<PoolInterface *> pools;
    for (const auto &[tokens_container, pool] : existing_pools_.find(protocol)->second) {
        if (pool->InPool(input_token) && pool->InPool(output_token)) {
            pools.emplace(pool);
        }
    }
    return pools;
}

double Playground::SimulateSwap(PoolInterface *pool, Token *input_token, Token *output_token, double input_quantity) const {
    return pool->SimulateSwap(input_token, output_token, input_quantity);
}

double Playground::ExecuteSwap(Account *trader, PoolInterface *pool, Token *input_token, Token *output_token, double input_quantity) const {
    return trader->Trade(pool, input_token, output_token, input_quantity);
}

double Playground::SimulateProvision(PROTOCOL protocol, const std::unordered_map<Token *, double> &provided_quantities) const {
    std::unordered_set<Token *> tokens; tokens.reserve(provided_quantities.size());
    for (const auto &[token, quantity] : provided_quantities) {
        tokens.emplace(token);
    }
    if (!Existing(protocol, tokens)) {
        return PoolInterface::INITIAL_POOL_TOKEN_SUPPLY;
    }
    return GetPool(protocol, tokens)->SimulateProvision(provided_quantities);
}

double Playground::ExecuteProvision(Account *provider, PROTOCOL protocol, const std::unordered_map<Token *, double> &provided_quantities) const {
    std::unordered_set<Token *> tokens; tokens.reserve(provided_quantities.size());
    for (const auto &[token, quantity] : provided_quantities) {
        tokens.emplace(token);
    }
    if (!Existing(protocol, tokens)) {
        throw std::invalid_argument("this pool does not exist");
    }
    return provider->Provide(GetPool(protocol, tokens), provided_quantities);
}

double Playground::ExecuteInitialProvision(Account *provider, PROTOCOL protocol, const std::unordered_map<Token *, double> &provided_quantities, double pool_fee) {
    std::unordered_set<Token *> tokens; tokens.reserve(provided_quantities.size());
    for (const auto &[token, quantity] : provided_quantities) {
        tokens.emplace(token);
    }
    if (!Existing(protocol, tokens)) {
        if (protocol == PROTOCOL::UNISWAP_V2) {
            existing_pools_[protocol][TokensContainer(tokens)] = new UniswapV2Pool(tokens, pool_fee);
        }
    }
    return ExecuteProvision(provider, protocol, provided_quantities);
}

double Playground::ExecuteInitialProvision(Account *provider, PROTOCOL protocol, const std::unordered_map<Token *, double> &provided_quantities, double pool_fee, double slippage_controller) {
    std::unordered_set<Token *> tokens; tokens.reserve(provided_quantities.size());
    for (const auto &[token, quantity] : provided_quantities) {
        tokens.emplace(token);
    }
    if (!Existing(protocol, tokens)) {
        if (protocol == PROTOCOL::UNISWAP_V3) {
            existing_pools_[protocol][TokensContainer(tokens)] = new UniswapV3Pool(tokens, pool_fee, slippage_controller);
        }
    }
    return ExecuteProvision(provider, protocol, provided_quantities);
}

double Playground::ExecuteInitialProvision(Account *provider, PROTOCOL protocol, const std::unordered_map<Token *, double> &provided_quantities, double pool_fee, const std::unordered_map<Token *, double> &weights) {
    std::unordered_set<Token *> tokens; tokens.reserve(provided_quantities.size());
    for (const auto &[token, quantity] : provided_quantities) {
        tokens.emplace(token);
    }
    if (!Existing(protocol, tokens)) {
        if (protocol == PROTOCOL::CONSTANT_SUM) {
            existing_pools_[protocol][TokensContainer(tokens)] = new ConstantSum(tokens, pool_fee, weights);
        } else if (protocol == PROTOCOL::BALANCER) {
            existing_pools_[protocol][TokensContainer(tokens)] = new BalancerPool(tokens, pool_fee, weights);
        }
    }
    return ExecuteProvision(provider, protocol, provided_quantities);
}

std::unordered_map<Token *, double> Playground::SimulateWithdrawal(Token *token, double surrendered_quantity) const {
    if (!token->pool()) {
        throw std::invalid_argument("this is not a pool token");
    }
    return token->pool()->SimulateWithdrawal(surrendered_quantity);
}

std::unordered_map<Token *, double> Playground::ExecuteWithdrawal(Account *provider, Token *token, double surrendered_quantity) {
    if (!token->pool()) {
        throw std::invalid_argument("this is not a pool token");
    }
    std::unordered_map<Token *, double> output_quantities = provider->Withdraw(token->pool(), surrendered_quantity);
    if (!token->pool()->total_pool_token_quantity()) {
        PROTOCOL protocol;
        if (typeid(token->pool()) == typeid(UniswapV2Pool)) {
            protocol = PROTOCOL::UNISWAP_V2;
        } else if (typeid(token->pool()) == typeid(UniswapV3Pool)) {
            protocol = PROTOCOL::UNISWAP_V3;
        } else if (typeid(token->pool()) == typeid(ConstantSum)) {
            protocol = PROTOCOL::CONSTANT_SUM;
        } else if (typeid(token->pool()) == typeid(BalancerPool)) {
            protocol = PROTOCOL::BALANCER;
        }
        existing_pools_[protocol].erase(token->pool()->tokens_container_);
    }
    return output_quantities;
}
