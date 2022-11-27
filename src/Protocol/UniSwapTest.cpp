#include <iostream>

#include <unordered_map>
#include <unordered_set>

#include "UniSwap.hpp"

using namespace std;

int main()  {
    UniSwapV3_protocol *testing_pool = UniSwapV3_protocol::getProtocol();
    UniSwapV3_protocol *another_pool = UniSwapV3_protocol::getProtocol();

    assert(testing_pool == another_pool);

    Token *token1 = Token::GetToken("DAI");
    Token *token2 = Token::GetToken("ETH");

    unordered_map<Token *, double> q;
    q[token1] = 10;
    q[token2] = 1000;

    cerr << "Combi\n";

    testing_pool -> setSlippageController(4);
    testing_pool -> setInvariant(make_pair(20, 600));

    cerr << testing_pool -> computeSwapQuantity(q,token1, token2, 1) << "\n";
}