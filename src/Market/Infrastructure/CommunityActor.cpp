#include "CommunityActor.hpp"
#include "../../Playground.hpp"

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

void CommunityActor::refill(Token *token) {
    wallet_[token] = 1e9;
}
void CommunityActor::Trade(PoolInterface *pool, Token *input_token, Token *output_token, double input_quantity) {
    refill(input_token);
    refill(output_token);

    pool->Swap(this, input_token, output_token, input_quantity);
}
void CommunityActor::Provide(PoolInterface *pool, double nPoolTokens) {
    std::unordered_map<Token *, double> quantities;

    for (auto [token, quantity] : pool->quantities()) {
        refill(token);
        quantities[token] = quantity / pool->GetQuantity(pool->pool_token()) * nPoolTokens;
    }
    pool->Provide(this, quantities);
}
void CommunityActor::Withdraw(PoolInterface *pool, double nPoolTokens) {
    pool->Withdraw(this, nPoolTokens);
}

// int main() {
//     Playground playground;

//     Token *token1 = playground.GetToken("token1", 10).first;
//     Token *token2 = playground.GetToken("token2", 20).first;

//     CommunityActor combi(1);

//     combi.refill(token1);
//     combi.refill(token2);

//     playground.ExecuteInitialProvision(&combi, PROTOCOL::CONSTANT_SUM, {{token1, 50}, {token2, 50}}, 0, {{token1, 10}, {token2, 10}});
//     PoolInterface *pool = playground.GetPool(PROTOCOL::CONSTANT_SUM, {token1, token2});

//     std::cout << "Success!\n";

//     return 0;
// }