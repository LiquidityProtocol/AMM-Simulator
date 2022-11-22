#include <cassert>
#include "Token.hpp"
#include "UniswapV2Pool.hpp"
#include "PoolInterface.hpp"

int main() {
    Token *token1 = Token::GetToken("token1");
    Token *token2 = Token::GetToken("token2");
    Token *token3 = Token::GetToken("token3");

    UniswapV2Pool pool(token1, token2, 10, 20);

    assert(pool.InPool(token1));
    assert(!pool.InPool(token3));

    try {
        pool.GetOtherToken(token3);
        assert(false);
    } catch (std::invalid_argument &e) {
        assert(std::string(e.what()) == "invalid token");
    }
    assert(pool.GetOtherToken(token1) == token2);

    try {
        pool.GetQuantity(token3);
        assert(false);
    } catch (std::invalid_argument &e) {
        assert(std::string(e.what()) == "invalid token");
    }
    assert(pool.GetQuantity(token1) == 10);

    auto output = pool.Swap({token1, 10});
    assert(output.token() == token2);
    assert(output.quantity() == 10);
    assert(pool.GetQuantity(token1) == 20);
    assert(pool.GetQuantity(token2) == 10);

    return 0;
}