#include <cassert>
#include "../Playground.hpp"

int main () {
    Playground playground;

    Token *token1 = playground.GetToken("token1").first;
    Token *token2 = playground.GetToken("token2").first;
    assert(playground.existing_tokens() == std::unordered_set<Token *>({token1, token2}));

    return 0;
}