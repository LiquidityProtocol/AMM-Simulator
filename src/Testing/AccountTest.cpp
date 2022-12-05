#include <cassert>
#include "../Utilities/Utilities.hpp"
#include "../Protocols/UniswapV2Pool.hpp"
#include <vector>

int main() {
    Token *token1 = Token::GetToken("ABC");
    token1->set_real_value(1000);

    Token *token2 = Token::GetToken("DEF");
    token2->set_real_value(2300);

    Account *Alice = Account::GetAccount("Alice");
    Alice->Deposit(token1, 500);
    Alice->Deposit(token2, 1000);

    UniswapV2Pool pool({{token1, 1}, {token2, 2}});
    Alice->Provide(&pool, {{token1, 10}, {token2, 20}});
    Alice->Provide(&pool, {{token1, 50}, {token2, 100}});
    Alice->Trade(&pool, token2, token1, 20);
    Alice->Trade(&pool, token1, token2, 20);
    // Alice->Withdraw(&pool, 20);
    std::vector<Operation*> ledger = Alice->GetLedger();
    for (auto operation: ledger)
        std::cout << (*operation);

    assert(Alice->name() == "Alice");

    assert(abs(Alice->GetQuantity(token1) - 428.5915) < 1e-4);
    assert(abs(Alice->GetQuantity(token2) - 899.2219) < 1e-4);

    assert(Alice->GetValue(token1) == Alice->GetQuantity(token1) * token1->real_value());
    assert(Alice->GetValue(token2) == Alice->GetQuantity(token2) * token2->real_value());

    return 0;
}