#include <cassert>
#include <unordered_set>
#include "Token.hpp"
#include "ConstantSum.hpp"
#include "PoolInterface.hpp"

int main() {
    Token *token1 = Token::GetToken("token1");
    Token *token2 = Token::GetToken("token2");
    Token *token3 = Token::GetToken("token3");

    ConstantSum pool({{token1, 10}, {token2, 20}});

    assert(pool.InPool(token1));
    assert(!pool.InPool(token3));

    try {
        pool.GetQuantity(token3);
        assert(false);
    } catch (std::invalid_argument &e) {
        assert(std::string(e.what()) == "invalid token");
    }
    assert(pool.GetQuantity(token1) == 10);

    assert(pool.tokens() == std::unordered_set<Token *>({token1, token2}));

    assert(pool.Swap(token1, token2, 10) == 20);
    assert(pool.GetQuantity(token1) == 20);
    assert(pool.GetQuantity(token2) == 0);

    return 0;
}
