#include <cassert>
#include "../Playground.hpp"

int main() {
    Playground playground;

    Token *token1 = playground.GetToken("token1", 10).first;
    Token *token2 = playground.GetToken("token2", 20).first;

    Account *alice = playground.GetAccount("Alice").first;
    alice->Deposit(token1, 100);
    alice->Deposit(token2, 100);

    assert(alice->name() == "Alice");

    assert(alice->GetQuantity(token1) == 100 && alice->GetQuantity(token2) == 100);

    std::cout << "Success!\n";

    return 0;
}
