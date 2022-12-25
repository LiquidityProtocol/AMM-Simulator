#include <cassert>
#include "../Playground.hpp"

int main() {
    Playground playground;

    Token *token1 = playground.GetToken("token1", 10).first;
    Token *token2 = playground.GetToken("token2", 20).first;
    Token *token3 = playground.GetToken("token3", 30).first;

    Account *alice = playground.GetAccount("Alice").first;
    alice->Deposit(token1, 100);
    alice->Deposit(token2, 100);

    playground.ExecuteInitialProvision(alice, PROTOCOL::UNISWAP_V2, {{token1, 20}, {token2, 40}}, 0.01);
    PoolInterface *pool = playground.GetPool(PROTOCOL::UNISWAP_V2, {token1, token2});

    assert(pool->InPool(token1));
    assert(!pool->InPool(token3));

    assert(pool->GetQuantity(token1) == 20);
    assert(pool->GetQuantity(token3) == 0);

    assert(pool->pool_fee() == 0.01);

    assert(pool->total_pool_token_quantity() == 1);

    assert(pool->tokens() == std::unordered_set<Token *>({token1, token2}));

    std::cout << "Success!\n";

    return 0;
}
