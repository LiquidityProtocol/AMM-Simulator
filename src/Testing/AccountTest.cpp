#include <cassert>
#include "../Utilities/Utilities.hpp"
#include "../Protocols/UniswapV2Pool.hpp"
#include <vector>

int main() {
    Token *token1 = Token::GetToken("ABC");
    token1->set_real_value(1000);

    Token *token2 = Token::GetToken("DEF");
    token2->set_real_value(2300);

    Account *account = Account::GetAccount("Alice");
    account->Deposit(token1, 500);
    account->Deposit(token2, 1000);

    UniswapV2Pool pool({{token1, 1}, {token2, 2}});
    account->Provide(&pool, {{token1, 10}, {token2, 20}});
    account->Provide(&pool, {{token1, 50}, {token2, 100}});
    account->Trade(&pool, token2, token1, 20);
    account->Trade(&pool, token1, token2, 20);
    account->Withdraw(&pool, 20);
    std::vector<Operation*> ledger = account->GetLedger();
    for (auto operation: ledger){
        operation->Print();
    }

    assert(account->name() == "Alice");
    assert(account->GetQuantity(token1) == 50 && account->GetQuantity(token2) == 100);
    assert(account->GetValue(token1) == 50000 && account->GetValue(token2) == 230000);
    assert(account->total_value() == 280000);

    return 0;
}