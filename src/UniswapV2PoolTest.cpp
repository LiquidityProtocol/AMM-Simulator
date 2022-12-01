#include <cassert>
#include "Token.hpp"
#include "UniswapV2Pool.hpp"

int main() {
    Token *token1 = Token::GetToken("token1");
    Token *token2 = Token::GetToken("token2");

    UniswapV2Pool pool({{token1, 20}, {token2, 40}}, 0.01);

    assert(std::abs(pool.Swap(token1, token2, 10) - 13.24) < 1e-2);
    assert(std::abs(pool.GetQuantity(token2) - 26.756) < 1e-3);
    assert(pool.GetQuantity(token1) == 30);


    return 0;
}