#include <unordered_map>
#include <unordered_set>

#include <stdexcept>
#include <math.h>

#include "Protocol.hpp"
#include "message.hpp"
#include "../Token.hpp"

using namespace std;

#define TEST_Protocol   1

int main()  {
    #if TEST_Protocol == 1
    Protocol<double> *P = Protocol<double>::GetProtocol("UniSwapV2");

    unordered_map<Token*, double> quantity;
    Token* pToken1 = Token::GetToken("ETH");
    Token* pToken2 = Token::GetToken("DAI");

    quantity[pToken1] = 10;
    quantity[pToken2] = 1000;
    
    alert(P -> computeSpotExchangeRate(quantity, pToken1, pToken2) == 0.01,
        "Exchange Rate Wrong",
        "Exchange Rate Correct");
    
    alert(abs(P -> computeDivergenceLoss(quantity, 1) + 0.05719) < 0.001,
        "Calculate the Divergence Loss Correct",
        "Calculate the Divergence Loss Wrong");
    #endif
}