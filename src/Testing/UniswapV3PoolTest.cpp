#include <cassert>
#include "../Protocols/UniswapV3Pool.hpp"

int main() {
    Token *token1 = Token::GetToken("token1");
    Token *token2 = Token::GetToken("token2");

    UniswapV3Pool pool({{token1, 20}, {token2, 40}}, 0.01);

    Account *account = Account::GetAccount("Alice");
    account->Deposit(token1, 1000);
    account->Deposit(token2, 10000);

    assert(account->Trade(&pool, token1, token2, 30) == 20);
    assert(pool.GetQuantity(token1) == 50);
    assert(pool.GetQuantity(token2) == 90);

    assert(account->Trade(&pool, token1, token2, 20) == 20);
    assert(pool.GetQuantity(token1) == 90);
    assert(pool.GetQuantity(token2) == 10);

    try {
        account->Trade(&pool, token1, token2, 20);
        assert(false);
    } catch (std::invalid_argument &e) {
        assert(std::string(e.what()) == "not enough liquidity");
    }

    return 0;
}