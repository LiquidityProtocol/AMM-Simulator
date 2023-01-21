#include "CommunityActor.hpp"
#include <cassert>

CommunityActor::CommunityActor(int MarketCount) : Account("CommunityActor" + std::to_string(MarketCount)) {}

template<typename T> T CommunityActor::wallet() const {
    throw std::invalid_argument("cannot get config of community");
}
template<typename T> T CommunityActor::total_value() const {
    throw std::invalid_argument("cannot get config of community");
}
template<typename T> T CommunityActor::ledger() const {
    throw std::invalid_argument("cannot get config of community");
}
template<typename T> T CommunityActor::GetQuantity() const {
    throw std::invalid_argument("cannot get config of community");
}

void CommunityActor::refill(Token *token, double amount = 1e9) {
    wallet_[token] = amount;
}
void CommunityActor::Provide(PoolInterface *pool, double nPoolTokens) {
    std::unordered_map<Token *, double> quantities;

    for (auto [token, quantity] : pool->quantities()) {
        refill(token);
        quantities[token] = quantity / pool->total_pool_token_quantity() * nPoolTokens;
    }
    pool->Provide(this, quantities);
}
void CommunityActor::Withdraw(PoolInterface *pool, double nPoolTokens) {
    pool->Withdraw(this, nPoolTokens);
}
