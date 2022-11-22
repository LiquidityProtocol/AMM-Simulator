#include <stdexcept>
#include <string>
#include "LiquifiProtocolPool.hpp"

int main() {
    Token *token1 = new Token("Token_1"), *token2 = new Token("Token_2"), *token3 = new Token("Token_3");
    LiquifiProtocolPool pool(token1, token2, 10, 20, 0);

    try {
        pool.standard_immediate_swap({token3, 0});
        assert(false);
    } catch (std::invalid_argument &e) {
        assert(std::string(e.what()) == "invalid token");
    }

    try {
        pool.standard_immediate_swap({token1, 0});
        assert(false);
    } catch (std::invalid_argument &e) {
        assert(std::string(e.what()) == "invalid quantity");
    }

    auto output = pool.standard_immediate_swap({token1, 10});
    assert(output.get_token() == token2);
    assert(output.get_quantity() == 10);

    return 0;
}