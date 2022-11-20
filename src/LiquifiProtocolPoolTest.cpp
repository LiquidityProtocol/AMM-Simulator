#include <vector>
#include <stdexcept>
#include <string.h>
#include "LiquifiProtocolPool.hpp"

int main() {
    Token token1("Token_1"), token2("Token_2"), token3("Token_3");
    LiquifiProtocolPool pool({{token1, 10}, {token2, 20}}, 0);

    try {
        pool.standard_immediate_swap({token3, 0});
        assert(false);
    } catch (std::invalid_argument &e) {
        assert(strcmp(e.what(), "invalid token"));
    }

    try {
        pool.standard_immediate_swap({token1, 0});
        assert(false);
    } catch (std::invalid_argument &e) {
        assert(strcmp(e.what(), "invalid quantity"));
    }

    auto output = pool.standard_immediate_swap({token1, 10});
    assert(output.get_token() == token2);
    assert(output.get_quantity() == 10);

    return 0;
}