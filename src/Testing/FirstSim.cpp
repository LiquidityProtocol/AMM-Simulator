#include <cmath>
#include <random>
#include <vector>
#include <iostream>
using namespace std;
#include <C:\Users\slshu\OneDrive\Documents\Ecole Polytechnique\Year 2\Intro to C++\Project\src\Utilities\Utilities.hpp>
#include <C:\Users\slshu\OneDrive\Documents\Ecole Polytechnique\Year 2\Intro to C++\Project\src\Protocols\UniSwapV2Pool.hpp>

enum Players {
    Trader = 0,
    Liquidity_Provider = 1,
    Arbritageur = 2
};

/*/double action_type(double market_price_ratio, double pool_price_ratio) { 
    double l2t = 0.05;
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0.0,1.0);

    double sample = distribution(generator);

    double arb_inc = abs(1 - market_price_ratio/pool_price_ratio)

    double arb_prob = 50 * arb_inc

    if (sample < l2t){
        return Liquidity_Provider;
    }
    else if (sample < l2t + arb_prob){
        return Arbritageur;
    }
    else {
        return Trader;
    }
    ;
}/*/

void print(std::vector<double> const &input)
{
    for (int i = 0; i < input.size(); i++) {
        std::cout << input.at(i) << ' ';
    }
}

void Simulation(){
    Token *token1 = Token::GetToken("token1");
    Token *token2 = Token::GetToken("token2");

    UniswapV2Pool pool({{token1, 100}, {token2, 200}});

    Account *account = Account::GetAccount("LP");
    account->Deposit(token1, 100);
    account->Deposit(token2, 100);

    Account *trader = Account::GetAccount("Trader");
    trader->Deposit(token1, 1000);
    trader->Deposit(token2, 1000);

    Account *arb = Account::GetAccount("Arbritageur");
    arb->Deposit(token1, 100);
    arb->Deposit(token2, 100);

    std::vector<double> slippages = {0};
    std::vector<double> spot_exchange_rates = {0.5};
    std::vector<double> trader_balances_1 = {1000};
    std::vector<double> trader_balances_2 = {1000};
    std::vector<double> pool_quantity_1 = {10};
    std::vector<double> pool_quantity_2 = {20};


    for (int i = 0; i < 5; i++){
        
        double swap_quantity = pool.SimulateSwap(token1, token2, 1);
        double slip = pool.ComputeSlippage(token1, token2, 1);
        slippages.push_back(slip);
        
        pool.ExecuteSwap(trader, token1, token2, 1, swap_quantity);
        
        double exchange_rate = pool.ComputeSpotExchangeRate(token1, token2);
        spot_exchange_rates.push_back(exchange_rate);

        double quantity_1 = pool.GetQuantity(token1);
        double quantity_2 = pool.GetQuantity(token2);
        pool_quantity_1.push_back(quantity_1);
        pool_quantity_2.push_back(quantity_2);

        double trader_1 = trader->GetQuantity(token1);
        double trader_2 = trader->GetQuantity(token2);
        trader_balances_1.push_back(trader_1);
        trader_balances_2.push_back(trader_2);
        
    }
    print(slippages);
    print(spot_exchange_rates);
    print(trader_balances_1);
    print(trader_balances_2);
    print(pool_quantity_1);
    print(pool_quantity_2);
}

int main() {
    Simulation();
}