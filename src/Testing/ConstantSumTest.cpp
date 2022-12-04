#include <cassert>
#include <stdexcept>
#include "../Protocols/ConstantSum.hpp"

int main() {
    Token *token1 = Token::GetToken("token1");
    Token *token2 = Token::GetToken("token2");

    ConstantSum pool({{token1, 50}, {token2, 50}},
                     {{token1, 10}, {token2, 10}}, 0);

    Account *combi = Account::GetAccount("Combi");

    combi -> Deposit(token1, 100);
    combi -> Deposit(token2, 100);

    assert(pool.Swap(combi, token1, token2, 20) == 20);
    assert(pool.GetQuantity(token1) == 70);
    assert(pool.GetQuantity(token2) == 30);

    assert(pool.Swap(combi, token1, token2, 20) == 20);
    assert(pool.GetQuantity(token1) == 90);
    assert(pool.GetQuantity(token2) == 10);

    try {
        pool.Swap(combi, token1, token2, 20);
        assert(false);
    } catch (std::invalid_argument &e) {
        assert(std::string(e.what()) == "Not enough liquidity");
    }

    return 0;
}
