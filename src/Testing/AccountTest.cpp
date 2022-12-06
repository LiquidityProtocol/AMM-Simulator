#include <cassert>
#include "../Protocols/UniswapV2Pool.hpp"

int main() {
    Token *token1 = Token::GetToken("ABC");
    token1->set_real_value(1000);

    Token *token2 = Token::GetToken("DEF");
    token2->set_real_value(2300);

    Account *alice = Account::GetAccount("Alice");
    alice->Deposit(token1, 500);
    alice->Deposit(token2, 1000);

    UniswapV2Pool pool({{token1, 1}, {token2, 2}});
    alice->Provide(&pool, {{token1, 10}, {token2, 20}});
    alice->Provide(&pool, {{token1, 50}, {token2, 100}});
    alice->Trade(&pool, token2, token1, 20);
    alice->Trade(&pool, token1, token2, 20);

    for (auto operation : alice->ledger()) {
        std::cout << (*operation);
    }

    assert(alice->name() == "Alice");

    assert(abs(alice->GetQuantity(token1) - 428.5915) < 1e-4);
    assert(abs(alice->GetQuantity(token2) - 899.2219) < 1e-4);

    assert(alice->GetValue(token1) == alice->GetQuantity(token1) * token1->real_value());
    assert(alice->GetValue(token2) == alice->GetQuantity(token2) * token2->real_value());

    return 0;
}