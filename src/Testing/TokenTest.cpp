#include <cassert>
#include "../Playground.hpp"

int main () {
    Playground playground;

    Token *token1 = playground.GetToken("token1").first;
    Token *token2 = playground.GetToken("token2").first;
    Token *another_token1 = playground.GetToken("token1").first;

    assert(token1 != token2);
    assert(token1 == another_token1);
    assert(token1->name() == "token1");

    std::cout << "Success!\n";

    return 0;
}
