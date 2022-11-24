#include <cassert>
#include <stdexcept>
#include "ConstantSum.hpp"

int main() {
    Token *token1 = Token::GetToken("token1");
    Token *token2 = Token::GetToken("token2");

    ConstantSum pool({{token1, 10}, {token2, 20}});

    assert(pool.Swap(token1, token2, 10) == 10);
    assert(pool.GetQuantity(token1) == 20);
    assert(pool.GetQuantity(token2) == 10);

    assert(pool.Swap(token1, token2, 10) == 10);
    assert(pool.GetQuantity(token1) == 30);
    assert(pool.GetQuantity(token2) == 0);

    try {
        pool.Swap(token1, token2, 10);
        assert(false);
    } catch (std::invalid_argument &e) {
        assert(std::string(e.what()) == "provided too many token1s");
    }

    return 0;
}
