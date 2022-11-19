#include <iostream>
#include <unordered_map>
#include <cassert>
#include "Token.hpp"

int main () {
    Token token1("Token_1"), token2("Token_2");
    
    assert(!(token1 == token2));
    std::unordered_map<Token, int> token_to_quantity;
    token_to_quantity[token1] = 1;
    token_to_quantity[token2] = 2;
    assert(token_to_quantity.size() == 2);
    assert(token_to_quantity[token1] == 1);
    assert(token_to_quantity[token2] == 2);

    return 0;
}