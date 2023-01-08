#include <cassert>
#include "Arbitrager.hpp"
#include "Token.hpp"
#include "UniswapV2Pool.hpp"

int main() {
    //write some tests
    Token *token1 = Token::GetToken("A");
    token1->set_real_value(1000);

    Token *token2 = Token::GetToken("B");
    token2->set_real_value(1000);

    Token *token3 = Token::GetToken("C");
    token3->set_real_value(1000);

    //initialise account instance
    Account *arb_account;
    arb_account = Account::GetAccount("Arb");

    //initialise Arbitrage instance
    Arbitrager *arb;

    //initialise vector of UniSwapV2Pools between every token pair
    std::vector<PoolInterface *> pools_inp;
    pools_inp.push_back(new UniswapV2Pool({{token1, 100}, {token2, 1000}}));
    pools_inp.push_back(new UniswapV2Pool({{token1, 100}, {token3, 100}}));
    pools_inp.push_back(new UniswapV2Pool({{token2, 100}, {token3, 100}}));

    //print pools vector details


    //set_pools in arbitrager class
    //arb->set_pools(pools);
    //find cycles in the graph of token pairs
    std::unordered_set<Token *> visited;
    std::vector<std::unordered_set<Token *>> cycles;
    arb->find_cycles(pools_inp, token1, visited, cycles);

    //print cycles
    for (auto cycle : cycles) {
        for (auto token : cycle) {
            std::cout << token->name() << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}

