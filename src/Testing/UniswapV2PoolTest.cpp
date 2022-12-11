#include <cassert>
#include "../Protocols/UniswapV2Pool.hpp"

int main() {
    Token *token1 = Token::GetToken("token1", 10).first;
    Token *token2 = Token::GetToken("token2", 20).first;

    Account *alice = Account::GetAccount("Alice").first;
    alice->Deposit(token1, 100);
    alice->Deposit(token2, 100);

    try {
        UniswapV2Pool::GetPool(token1, token2);
        assert(false);
    } catch (std::invalid_argument &e) {
        assert(std::string(e.what()) == "there is no existing pool with corresponding tokens");
    }

    alice->Provide(token1, token2, 20, 40, 0.01);

    alice->Trade(token1, token2, 10);
    assert(alice->GetQuantity(token1) == 70);
    assert(abs(alice->GetQuantity(token2) - 73.2441) < 1e-4);

    alice->Trade(token1, token2, 10);
    assert(alice->GetQuantity(token1) == 60);
    assert(abs(alice->GetQuantity(token2) - 79.8828) < 1e-4);

    UniswapV2Pool *pool = UniswapV2Pool::GetPool(token1, token2);
    assert(pool->GetQuantity(token1) == 40);
    assert(abs(pool->GetQuantity(token2) - 20.117) < 1e-3);

    alice->Withdraw(pool->pool_token(), alice->GetQuantity(pool->pool_token()));
    assert(alice->GetQuantity(token1) == 100);
    assert(abs(alice->GetQuantity(token2) - 100) < 1e-4);
    try {
        UniswapV2Pool::GetPool(token1, token2);
        assert(false);
    } catch (std::invalid_argument &e) {
        assert(std::string(e.what()) == "there is no existing pool with corresponding tokens");
    }
    
    return 0;
}
