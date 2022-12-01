#include <cassert>
#include "Account.hpp"
#include "Token.hpp"
#include "UniswapV2Pool.hpp"

int main() {
    Token *token1 = Token::GetToken("ABC");
    token1->set_real_value(1000);

    Token *token2 = Token::GetToken("DEF");
    token2->set_real_value(2300);

    Account *account = Account::GetAccount("Alice");
    account->Deposit(token1, 50);
    account->Deposit(token2, 100);

    assert(account->name() == "Alice");
    assert(account->GetQuantity(token1) == 50 && account->GetQuantity(token2) == 100);
    assert(account->GetValue(token1) == 50000 && account->GetValue(token2) == 230000);
    assert(account->total_value() == 280000);

    return 0;
}