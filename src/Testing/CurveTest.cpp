#include "../Protocols/CurvePool.hpp"
#include "../Protocols/UniswapV2Pool.hpp"
#include <cassert>
#include <fstream>

int main() {
    Token *token1 = Token::GetToken("abc");
    Token *token2 = Token::GetToken("def");

    CurvePool pool({{token1, 1000}, {token2, 5000}}, 0, 2);

    Account *alice = Account::GetAccount("Alice");
    alice->Deposit(token1, 100000);
    alice->Deposit(token2, 100000);

    std::ofstream fout;
    fout.open("data_points.csv");

    for (int _ = 0 ; _ < 4500 ; ++_) {
        alice->Trade(&pool, token1, token2, 1);

        fout << pool.GetQuantity(token1) << ", ";
        fout << pool.GetQuantity(token2) << "\n";
    }
    fout.close();
}