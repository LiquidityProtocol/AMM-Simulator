#include "../Utilities/Utilities.hpp"
#include "../Protocols/UniswapV2Pool.hpp"
#include <iostream>

int main(){
  Token * token1 = Token::GetToken("token1");
  Token * token2 = Token::GetToken("token2");
  UniswapV2Pool pool({{token1, 10}, {token2, 20}});
  Operation op("PROVIDE", "combi", &pool, {{token1, 10}}, {{token2, 20}});
  op.Print();
  return 0;
}