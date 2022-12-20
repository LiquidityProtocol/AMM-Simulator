#include <cassert>
#include "../Playground.hpp"

int main() {
    Playground playground;

    Token *token1 = playground.GetToken("token1", 10).first;
    Token *token2 = playground.GetToken("token2", 20).first;

    Account *alice = playground.GetAccount("Alice").first;
    alice->Deposit(token1, 1000);
    alice->Deposit(token2, 1000);

    playground.ExecuteInitialProvision(alice, PROTOCOL::CONSTANT_SUM, {{token1, 50}, {token2, 50}}, 0, {{token1, 10}, {token2, 10}});
    PoolInterface *pool = playground.GetPool(PROTOCOL::CONSTANT_SUM, {token1, token2});

    assert(playground.ExecuteSwap(alice, pool, token1, token2, 20) == 20);
    assert(pool->GetQuantity(token1) == 70);
    assert(pool->GetQuantity(token2) == 30);

    assert(playground.ExecuteSwap(alice, pool, token1, token2, 20) == 20);
    assert(pool->GetQuantity(token1) == 90);
    assert(pool->GetQuantity(token2) == 10);

    try {
        playground.ExecuteSwap(alice, pool, token1, token2, 20);
        assert(false);
    } catch (std::invalid_argument &e) {
        assert(std::string(e.what()) == "not enough liquidity");
    }

    std::cout << "Success!\n";

    return 0;
}
