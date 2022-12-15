
#include <cassert>
#include "../Protocols/UniswapV2Pool.hpp"

using namespace std;
int main() {
    Token *token1 = Token::GetToken("token1");
    Token *token2 = Token::GetToken("token2");

    UniswapV2Pool pool({{token1, 20}, {token2, 40}}, 0.01);

    assert(std::abs(pool.SimulateSwap(token1, token2, 10) - 13.24) < 1e-2);
    
    return 0;  }





