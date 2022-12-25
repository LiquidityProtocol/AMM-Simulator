#include <cassert>
#include "../Playground.hpp"

int main() {
    Playground playground;

    Token *token1 = playground.GetToken("token1", 10).first;
    Token *token2 = playground.GetToken("token2", 20).first;

    Account *alice = playground.GetAccount("Alice").first;
    alice->Deposit(token1, 100);
    alice->Deposit(token2, 100);

    assert(!playground.Existing(PROTOCOL::UNISWAP_V2, {token1, token2}));

    playground.ExecuteInitialProvision(alice, PROTOCOL::UNISWAP_V2, {{token1, 20}, {token2, 40}}, 0.01);

    assert(abs(playground.SimulateSwap(playground.GetPool(PROTOCOL::UNISWAP_V2, {token1, token2}), token1, token2, 10) - 13.2441) < 1e-4);

    std::cout << "Success!\n";
    
    return 0;
}
