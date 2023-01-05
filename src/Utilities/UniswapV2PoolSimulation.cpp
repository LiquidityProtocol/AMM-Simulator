#include <cmath>
#include <random>
#include <vector>
#include <iostream>
using namespace std;
#include "Utilities.hpp"
#include "../Protocols/UniswapV2Pool.hpp"
#include "../Utilities/UniswapV2PoolSimulation.hpp"
#include "../Utilities/Utilities.hpp"


enum Players {
    Trader = 0,
    Liquidity_Provider = 1,
    Arbitrageur = 2
};

void print(std::vector<double> const &input)
{   std::cout << "Hello!!!" << std::endl;
    for (unsigned char i = 0; i < input.size(); i++) { std::cout << input.at(i) << ' ';   }   }

// Documenting the edge cases of Uniswap V2 Pool

// Swaps of size 1 - Range 100

void UniswapV2PoolTest1(){
    Token *token1 = Token::GetToken("token1");
    Token *token2 = Token::GetToken("token2");

    UniswapV2Pool pool({{token1, 100}, {token2, 200}});

    Account *account = Account::GetAccount("LP");
    account->Deposit(token1, 100);
    account->Deposit(token2, 100);

    Account *trader = Account::GetAccount("Trader");
    trader->Deposit(token1, 1000);
    trader->Deposit(token2, 1000);

    Account *arbitrageur = Account::GetAccount("Arbitrageur");
    arbitrageur->Deposit(token1, 100);
    arbitrageur->Deposit(token2, 100);

    std::vector<double> slippages = {0};
    std::vector<double> spot_exchange_rates = {0.5};
    std::vector<double> trader_balances_1 = {1000};
    std::vector<double> trader_balances_2 = {1000};
    std::vector<double> pool_quantity_1 = {10};
    std::vector<double> pool_quantity_2 = {20};


    for (int i = 0; i < 100; i++){

        double swap_quantity = pool.SimulateSwap(token1, token2, 1);

        double slip = pool.ComputeSlippage(token1, token2, 1);
        slippages.push_back(slip);

        pool.ExecuteSwap(trader, token1, token2, 1, swap_quantity);

        double exchange_rate = pool.ComputeSpotExchangeRate(token1, token2);

        spot_exchange_rates.push_back(exchange_rate);

        double quantity_1 = pool.GetQuantity(token1);
        pool_quantity_1.push_back(quantity_1);

        double quantity_2 = pool.GetQuantity(token2);
        pool_quantity_2.push_back(quantity_2);

        double trader_1 = trader->GetQuantity(token1);
        trader_balances_1.push_back(trader_1);

        double trader_2 = trader->GetQuantity(token2);
        trader_balances_2.push_back(trader_2);

    }
    print(slippages);
    print(spot_exchange_rates);
    print(trader_balances_1);
    print(trader_balances_2);
    print(pool_quantity_1);
    print(pool_quantity_2);

};


// Swaps that increase in proportion/size - Range 10 - steps 1

void UniswapV2PoolTest2(){
    Token *token1 = Token::GetToken("token1");
    Token *token2 = Token::GetToken("token2");

    UniswapV2Pool pool({{token1, 100}, {token2, 200}});

    Account *account = Account::GetAccount("LP");
    account->Deposit(token1, 100);
    account->Deposit(token2, 100);

    Account *trader = Account::GetAccount("Trader");
    trader->Deposit(token1, 1000);
    trader->Deposit(token2, 1000);

    Account *arbitrageur = Account::GetAccount("Arbitrageur");
    arbitrageur->Deposit(token1, 100);
    arbitrageur->Deposit(token2, 100);

    std::vector<double> slippages = {0};
    std::vector<double> spot_exchange_rates = {0.5};
    std::vector<double> trader_balances_1 = {1000};
    std::vector<double> trader_balances_2 = {1000};
    std::vector<double> pool_quantity_1 = {10};
    std::vector<double> pool_quantity_2 = {20};


    for (int i = 0; i < 10; i++){

        double swap_quantity = pool.SimulateSwap(token1, token2, i);

        double slip = pool.ComputeSlippage(token1, token2, i);
        slippages.push_back(slip);

        pool.ExecuteSwap(trader, token1, token2, 1, swap_quantity);

        double exchange_rate = pool.ComputeSpotExchangeRate(token1, token2);

        spot_exchange_rates.push_back(exchange_rate);

        double quantity_1 = pool.GetQuantity(token1);
        pool_quantity_1.push_back(quantity_1);

        double quantity_2 = pool.GetQuantity(token2);
        pool_quantity_2.push_back(quantity_2);

        double trader_1 = trader->GetQuantity(token1);
        trader_balances_1.push_back(trader_1);

        double trader_2 = trader->GetQuantity(token2);
        trader_balances_2.push_back(trader_2);

    }
    print(slippages);
    print(spot_exchange_rates);
    print(trader_balances_1);
    print(trader_balances_2);
    print(pool_quantity_1);
    print(pool_quantity_2);

};

// Swaps with (very) unbalanced initial endowment - Steps 1 - Range 100

void UniswapV2PoolTest3(){
    Token *token1 = Token::GetToken("token1");
    Token *token2 = Token::GetToken("token2");

    UniswapV2Pool pool({{token1, 500}, {token2, 50}});

    Account *account = Account::GetAccount("LP");
    account->Deposit(token1, 100);
    account->Deposit(token2, 100);

    Account *trader = Account::GetAccount("Trader");
    trader->Deposit(token1, 1000);
    trader->Deposit(token2, 1000);

    Account *arbitrageur = Account::GetAccount("Arbitrageur");
    arbitrageur->Deposit(token1, 100);
    arbitrageur->Deposit(token2, 100);

    std::vector<double> slippages = {0};
    std::vector<double> spot_exchange_rates = {0.5};
    std::vector<double> trader_balances_1 = {1000};
    std::vector<double> trader_balances_2 = {1000};
    std::vector<double> pool_quantity_1 = {10};
    std::vector<double> pool_quantity_2 = {20};


    for (int i = 0; i < 100; i++){

        double swap_quantity = pool.SimulateSwap(token1, token2, 1);

        double slip = pool.ComputeSlippage(token1, token2, 1);
        slippages.push_back(slip);

        pool.ExecuteSwap(trader, token1, token2, 1, swap_quantity);

        double exchange_rate = pool.ComputeSpotExchangeRate(token1, token2);

        spot_exchange_rates.push_back(exchange_rate);

        double quantity_1 = pool.GetQuantity(token1);
        pool_quantity_1.push_back(quantity_1);

        double quantity_2 = pool.GetQuantity(token2);
        pool_quantity_2.push_back(quantity_2);

        double trader_1 = trader->GetQuantity(token1);
        trader_balances_1.push_back(trader_1);

        double trader_2 = trader->GetQuantity(token2);
        trader_balances_2.push_back(trader_2);

    }
    print(slippages);
    print(spot_exchange_rates);
    print(trader_balances_1);
    print(trader_balances_2);
    print(pool_quantity_1);
    print(pool_quantity_2);

};
