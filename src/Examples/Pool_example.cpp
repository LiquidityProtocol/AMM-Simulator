#include <iostream>

#include <unordered_map>
#include <unordered_set>

#include "Pool_example.hpp"
#include "../Token.hpp"

using namespace std;

class ConstantProduct : public Pool<UniSwapV2_protocol> {
public:
    ConstantProduct(const unordered_map<Token *, double>& q) : Pool<UniSwapV2_protocol>(q)  {}
private:
    double ExecuteSwap(Token *input_token, Token *output_token, double input_quantity)  {
        UniSwapV2_protocol *F = UniSwapV2_protocol::getProtocol();
        F->setInvariant(quantities_[input_token] * quantities_[output_token]);

        double output_quantity = F->computeSwapQuantity(quantities_, input_token, output_token, input_quantity);

        quantities_[input_token] += input_quantity;
        quantities_[output_token] -= output_quantity;

        return output_quantity;
    }
};
int main()  {
    Token *token1 = Token::GetToken("token1");
    Token *token2 = Token::GetToken("token2");

    unordered_map<Token *, double> q;
    q[token1] = 10;
    q[token2] = 20;

    ConstantProduct pool(q);

    assert(pool.Swap(token1, token2, 10) == 10);
    assert(pool.GetQuantity(token1) == 20);
    assert(pool.GetQuantity(token2) == 10);

    return 0;
}