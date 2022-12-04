#include <cassert>
#include "../Utilities/Utilities.hpp"

int main () {
    Token *token1_pointer = Token::GetToken("token1");
    Token *token2_pointer = Token::GetToken("token2");
    Token *another_token1_pointer = Token::GetToken("token1");

    assert(token1_pointer != token2_pointer);
    assert(token1_pointer == another_token1_pointer);
    assert(token1_pointer->name() == "token1");

    return 0;
}