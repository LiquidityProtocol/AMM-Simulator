#include <cassert>
#include <unordered_set>
#include <stdexcept>
#include "Token.hpp"
#include "UniswapV2Pool.hpp"

int main() {
    Token *token1 = Token::GetToken("token1");
    Token *token2 = Token::GetToken("token2");
    Token *token3 = Token::GetToken("token3");

    UniswapV2Pool pool({{token1, 10}, {token2, 20}});

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

    return 0;
}