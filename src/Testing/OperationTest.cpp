#include <cassert>
#include "../Protocols/UniswapV2Pool.hpp"

int main() {
    Token *token1 = Token::GetToken("token1");
    Token *token2 = Token::GetToken("token2");
    UniswapV2Pool pool({{token1, 10}, {token2, 20}});

    Operation op("PROVIDE", "Alice", &pool, {{token1, 10}}, {{token2, 20}});

    assert(op.operation_type() == "PROVIDE");
    assert(op.account_name() == "Alice");
    assert(op.input().size() == 1);
    assert(op.input()[token1] == 10);
    assert(op.output().size() == 1);
    assert(op.output()[token2] == 20);

    std::cout << op;

    return 0;
}