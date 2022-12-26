#include "../Protocols/Protocols.hpp"
#include "../Utilities/Utilities.hpp"
#include "../Playground.hpp"
#include <cassert>
#include <fstream>

int main() {
    Playground playground;

    Token *token1 = playground.GetToken("token1", 10).first;
    Token *token2 = playground.GetToken("token2", 20).first;

    Account *alice = playground.GetAccount("Alice").first;
    alice->Deposit(token1, 100000);
    alice->Deposit(token2, 100000);

    playground.ExecuteInitialProvision(alice, PROTOCOL::CURVE, {{token1, 1000}, {token2, 5000}}, 0, 2);
    PoolInterface *pool = playground.GetPool(PROTOCOL::CURVE, {token1, token2});

    std::ofstream fout;
    fout.open("data_points.csv");

    for (int _ = 0 ; _ < 4000 ; ++_) {
        playground.ExecuteSwap(alice, pool, token1, token2, 1);

        fout << pool->GetQuantity(token1) << ", ";
        fout << pool->GetQuantity(token2) << "\n";
    }
    fout.close();
}