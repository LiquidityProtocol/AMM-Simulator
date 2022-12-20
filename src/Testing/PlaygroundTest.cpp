#include <cassert>
#include "../Playground.hpp"

int main () {
    Playground playground;

    Token *token1 = playground.GetToken("token1", 10).first;
    Token *token2 = playground.GetToken("token2", 20).first;
    assert(playground.existing_tokens() == std::unordered_set<Token *>({token1, token2}));

    Account *alice = playground.GetAccount("Alice").first;
    alice->Deposit(token1, 100);
    alice->Deposit(token2, 100);

    playground.ExecuteInitialProvision(alice, PROTOCOL::UNISWAP_V2, {{token1, 20}, {token2, 40}}, 0.01);
    PoolInterface *pool = playground.GetPool(PROTOCOL::UNISWAP_V2, {token1, token2});
    assert(pool->total_pool_token_quantity() == 1);

    playground.ExecuteSwap(alice, pool, token1, token2, 10);
    assert(alice->GetQuantity(token1) == 70);
    assert(abs(alice->GetQuantity(token2) - 73.2441) < 1e-4);
    playground.ExecuteSwap(alice, pool, token1, token2, 10);
    assert(alice->GetQuantity(token1) == 60);
    assert(abs(alice->GetQuantity(token2) - 79.8828) < 1e-4);
    assert(pool->GetQuantity(token1) == 40);
    assert(abs(pool->GetQuantity(token2) - 20.117) < 1e-3);

    playground.ExecuteWithdrawal(alice, pool->pool_token(), alice->GetQuantity(pool->pool_token()));
    assert(alice->GetQuantity(token1) == 100);
    assert(abs(alice->GetQuantity(token2) - 100) < 1e-4);
    assert(!playground.Existing(PROTOCOL::UNISWAP_V2, {token1, token2}));

    for (auto op : alice->ledger()) {
        std::cout << *op;
    }
    for (auto data : alice->wallet()) {
        std::cout << data.first->name() << ": " << data.second << "\n";
    }

    std::cout << "Success!\n";

    return 0;
}
