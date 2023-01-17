#include "Market.hpp"
#include <random>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cassert>

std::default_random_engine generator;
std::normal_distribution<double> distribution(0.0, 1.0);

double RV(double m, double var) {
    return distribution(generator) * var + m;
}

int Market::MarketCount = 0;

Market::Market() {
    MarketIndex = ++MarketCount;
    epoch = 0;
    A = new CommunityActor(MarketIndex);
}
Market::~Market() {
    delete A;
    for (auto pool : pools_)    delete pool;
    for (auto token : tokens_)  delete token;
    
    pools_.clear();
    tokens_.clear();
}
void Market::loadInitialScenario(const std::unordered_map<std::string, double> &price_tags, PROTOCOL protocol) {
    // create some initial tokens of the market
    for (auto &[tokenName, price] : price_tags)
        addToken(tokenName, price);

    // create some initial accounts of the market
    Account *account1 = new Account("Alice");
    addAccount(account1);
    Account *account2 = new Account("Bob");
    addAccount(account2);

    for (auto token1 : tokens_)
    for (auto token2 : tokens_) {
        if (token1->name() != token2->name()) {
            std::unordered_map<Token *, double> quantities;

            if (RV(0, 1) < 0) { // the direction of unbalance is decided randomly
                quantities[token1] = 1e8 / token1->real_value();
                quantities[token2] = 9e7 / token2->real_value();
            } else {
                quantities[token1] = 9e7 / token1->real_value();
                quantities[token2] = 1e8 / token2->real_value(); // each token has equal volumeUSD inside the pool
            }
            PoolInterface *pool = nullptr;

            if (protocol == PROTOCOL::UNISWAP_V2) {
                pool = new UniswapV2Pool(quantities, 0.01);
            } else if (protocol == PROTOCOL::UNISWAP_V3) {
                pool = new UniswapV3Pool(quantities, 0.01, 10);
            } else {
                throw std::invalid_argument("currently not supporting this protocol");
            }

            addPool(pool);
            A->refill(pool->pool_token(), pool->GetQuantity(pool->pool_token()));
        } else {
            break; // market doesn't contain pools with duplicate pairs
        }
    }
    assert(pools_.size() == tokens_.size() * (tokens_.size() - 1) / 2 && "Combi");
}
void Market::loadInitialScenario(const std::unordered_set<PoolInterface *> pools) {
    for (auto pool : pools)
        addPool(pool);
}

void Market::addToken(const std::string &name, double price) {
    tokens_.emplace(new Token(name, price));
}
void Market::addToken(Token *token) {
    tokens_.emplace(token);
}
void Market::addAccount(Account *account) {
    accounts_.emplace(account);
}

bool Market::havePool(PoolInterface *pool) const {
    return pools_.count(pool);
}

bool Market::haveToken(Token *token) const {
    return tokens_.count(token);
}

void Market::addPool(PoolInterface *pool) {
    pools_.emplace(pool);
    for (auto token : pool->tokens())
        addToken(token);
}

Token* Market::getToken(std::string name) const {
    for (auto token: tokens_){
        if (token->name() == name){
            return token;
        }
    }
    throw std::invalid_argument("Token not exists");
}

void Market::runEpoch() {
    for (auto pool : GetMarketPools()) {
        Token *token1 = *(pool->tokens()).begin();
        Token *token2 = *(++(pool->tokens()).begin());

        double PoolRatio = pool->GetSpotPrice(token1, token2);
        double MarketRatio = token2->real_value() / token1->real_value();

        {   // LPs' Behavior:
            double LP_incentive = abs(log(PoolRatio) - log(MarketRatio));
            double LP_amount = RV(1, 1) - LP_incentive;

            // each pool token worth 1e8 USD so we use constant 0.01 so that the volume of one provision is approximately 1M USD

            if (LP_amount < 0) {
                A->Withdraw(pool, -0.01 * LP_amount);
            } else {
                A->Provide(pool, 0.01 * LP_amount);
            }
        }   // done LPs' behavior
        {   // Traders' behavior
            double volume1 = token1->real_value() * pool->GetQuantity(token1);
            double volume2 = token2->real_value() * pool->GetQuantity(token2);

            if (PoolRatio >= MarketRatio) {
                std::swap(token1, token2);
                std::swap(volume1, volume2);
            }
            // token1 is being over estimated
            assert(volume1 < volume2 + 1e-4);

            double volumeBalance = sqrt(volume1 * volume2);
            double optimalQuantity = (volumeBalance - volume1) / token1->real_value();

            try {
                A->Trade(pool, token1, token2, optimalQuantity * std::max(0.001, RV(1, 2)));
            } catch(...) {}
        }   // done Traders' behavior
    }
}

void Market::executeSignal(Account *sender, Signal *signal) {
    PoolInterface *pool = signal->pool();

    if (!havePool(pool)) {
        throw std::invalid_argument("Pool doesn't exist in this market");
    }

    Token *input_token = signal->input_token();
    Token *output_token = signal->output_token();
    double input_quantity = signal->quantity();

    sender->Trade(pool, input_token, output_token, input_quantity);
}

std::unordered_set<Token *> Market::GetMarketTokens() const {
    return tokens_;
}
std::unordered_set<PoolInterface *> Market::GetMarketPools() const {
    return pools_;
}
