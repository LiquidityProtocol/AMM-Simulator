#include <cassert>
#include "../Playground.hpp"

int main() {
    Playground playground;

    Token *token1 = playground.GetToken("token1", 10).first;
    Token *token2 = playground.GetToken("token2", 20).first;

    Account *alice = playground.GetAccount("Alice").first;
    alice->Deposit(token1, 100);
    alice->Deposit(token2, 100);

    playground.ExecuteInitialProvision(alice, PROTOCOL::UNISWAP_V2, {{token1, 20}, {token2, 40}}, 0.01);
    PoolInterface *pool = playground.GetPool(PROTOCOL::UNISWAP_V2, {token1, token2});

    Operation *op = alice->ledger().back();

    assert(op->operation_type() == "PROVIDE");
    assert(op->account_name() == alice->name());
    assert(op->input().size() == 2);
    assert(op->input()[token1] == 20);
    assert(op->input()[token2] == 40);
    assert(op->output().size() == 1);
    assert(op->output()[pool->pool_token()] == 1);

    std::cout << *op;

    std::cout << "Success!\n";

    return 0;
}
