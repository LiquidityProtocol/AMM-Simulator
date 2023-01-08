#include "../Simulation/Simulation.hpp"
#include <iostream>

int main() {
    Token *token1 = Token::GetToken("abc");
    Token *token2 = Token::GetToken("def");

    token1->set_real_value(100);
    token2->set_real_value(200);

    UniswapV2Pool pool({{token1, 100}, {token2, 100}});

    Simulation Sim1(&pool, 50, 100);

    for (int _ = 0 ; _ < 10 ; ++_)
        Sim1.runEpoch();

    ActionHistory h = Sim1.getHistory();

    for (size_t i = 0 ; i < h.size() ; ++i) {
        ActionInfo a = h[i];

        std::cerr << "Epoch " << i << ":\n";
        std::cerr << "> Slippage: " << a.getSlippage() << "\n";
        std::cerr << "> Pool Share Value: " << a.getPoolShareValue() << "\n";
        std::cerr << "> Spot Price : " << a.getSpotPrice(token1, token2) << "\n";
    }
}