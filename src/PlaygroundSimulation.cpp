#include "Playground.hpp"
#include <vector>
#include <iostream>
#include <utility>
#include <numeric>
#include <random>
#include <iostream>


enum Provision_Type {
    Withdraw = 0,
    Supply = 1
};

void Playground::Simulate(PROTOCOL protocol, PoolInterface *pool, double market_price){
    double liquidity_prob = 0.1;

    double random = (rand() % 10000);
    double sample = random/10000;

    std::string Name;
    auto it=existing_tokens_.begin();

    std::pair<std::string, Token *> firstToken = *it;
    it++;
    std::pair<std::string, Token *> secondToken = *it;

    double pool_price = pool->ComputeSpotExchangeRate(firstToken.second, secondToken.second);
    double arb_const = 1.8;
    double arb_prob = std::abs(1 - market_price/pool_price) * arb_const;

    if (sample < liquidity_prob){
            ProvisionSimulation(pool, firstToken.second, secondToken.second);
        }
        else if (sample < liquidity_prob + arb_prob){
            return ArbSimulation(pool, firstToken.second, secondToken.second);
        }
        else {
            return TradeSimulation(pool, firstToken.second, secondToken.second);
        }
        ;
    }


double Playground::LastActionsAverage(std::string action){
     std::string targetString = action;
     std::vector<double> last10;

        for (auto iter = state_evolution.rbegin(); iter != state_evolution.rend(); ++iter) {
            if (iter->first == targetString) {
                last10.push_back(iter->second);
                if (last10.size() == 10) {
                    break;
                }
            }
        }

        double average = std::accumulate(last10.begin(), last10.end(), 0.0) / last10.size();

        return average;
    }



double Playground::provision_type(){
    /* This function just tells us whether we should provide or withdraw
     *
     * @return: Provision Type
     */

    double random = rand()%10000;
    double sample = random/10000;

    if (sample < 0.5){
        return 1;
    }
    else {
        return 0;
    }
}

void Playground::SupplyPool(double token_1_provision_value,Token *firstToken, Token *secondToken, PoolInterface *pool, Account *provider){
    double market_token1 = pool->GetQuantity(firstToken);
    double market_token2 = pool->GetQuantity(secondToken);

    double market_ratio = market_token2/market_token1;

    double token_2_provision_value = market_ratio * token_1_provision_value;

    pool->Provide(provider, {{firstToken, token_1_provision_value}, {secondToken, token_2_provision_value}});

}


void Playground::ProvisionSimulation(PoolInterface *pool, Token *firstToken, Token *secondToken){

    auto it = existing_accounts_.find("Provider");
    it -> first;
    Account *account = it->second;

    double provider_token1 = account->GetQuantity(firstToken);
    double provider_pooltoken = account->GetQuantity(pool->pool_token());


    double black_swan = 0.005;
    double random = (rand() % 10000);
    double sample = random/10000;

    double type_provision = provision_type();
    double token_val;
    std::string ActionName;

    if (type_provision == Supply){
        token_val = provider_token1;
        ActionName = "Liquidity Supply";

    }
    else if (type_provision == Withdraw){
        token_val = provider_pooltoken;
        ActionName = "Liquidity Withdrawal";
    }

    double liquidity_mean;
    double liquidity_std;

    if(sample < black_swan){
        liquidity_mean = token_val/2;
        liquidity_std = token_val/5;
    }

    else{
       liquidity_mean = LastActionsAverage(ActionName);
       liquidity_std = liquidity_mean/2.5;
    }

    std::mt19937 generator(std::random_device{}());

        // Define the distribution
        double mean = liquidity_mean;
        double stddev = liquidity_std;
        std::normal_distribution<double> distribution(mean, stddev);

        // Generate a random number
        double liquidity_val = distribution(generator);


     if(type_provision == Supply){
         SupplyPool(liquidity_val, firstToken, secondToken, pool, account);
         state_evolution.push_back(std::make_pair("Liquidity Supply", liquidity_val));
     }
     else if (type_provision == Withdraw){
         std::unordered_map<Token *, double> tokens = pool->SimulateWithdrawal(liquidity_val);
         pool->ExecuteWithdrawal(account, liquidity_val, tokens);
         state_evolution.push_back(std::make_pair("Liquidity Withdrawal", liquidity_val));
     }

}

void Playground::TradeSimulation(PoolInterface *pool, Token *firstToken, Token *secondToken){
    auto it = existing_accounts_.find("Trader");
    it -> first;
    Account *account = it->second;

    double trader_token1 = account->GetQuantity(firstToken);
    double trader_token2 = account->GetQuantity(secondToken);

    double black_swan = 0.005;
    double random = (rand() % 10000);
    double sample = random/10000;

    double trade_mean;
    double trade_std;

    if(sample < black_swan){
        trade_mean = 0;
        trade_std = (trader_token1)/4;
    }
    else{
        trade_mean = LastActionsAverage("Trade");
        trade_std = LastActionsAverage("Trade")/5;
    }

    std::mt19937 generator(std::random_device{}());

        // Define the distribution
        double mean = trade_mean;
        double stddev = trade_std;
        std::normal_distribution<double> distribution(mean, stddev);

        // Generate a random number
        double trade_val = distribution(generator);

    if (trade_val>=0){
        double token2_quantity = pool->SimulateSwap(firstToken, secondToken, trade_val);
        pool->ExecuteSwap(account, firstToken, secondToken, trade_val, token2_quantity);

    }
    else{
        double token2_quantity = pool->ComputeInputRequirement(secondToken, firstToken, std::abs(trade_val));
        pool->ExecuteSwap(account, secondToken, firstToken, token2_quantity, std::abs(trade_val));
    }

    state_evolution.push_back(std::make_pair("Trade", trade_val));
}


double Playground::ArbAmount(PoolInterface *pool, Token *firstToken, Token *secondToken){
    double market_tok_1 = pool->GetQuantity(firstToken);
    double market_tok_2 = pool->GetQuantity(secondToken);

    double constant = market_tok_1 * market_tok_2;
    double new_quantity_1 = sqrt(constant * market_price);


    return market_tok_1 - new_quantity_1;
}

void Playground::ArbSimulation(PoolInterface *pool, Token *firstToken, Token *secondToken){
    auto it = existing_accounts_.find("Arb");
    it -> first;
    Account *account = it->second;

    double change_token1 = ArbAmount(pool, firstToken, secondToken);

                if (change_token1 < 0){
                    double output = pool->ComputeSwappedQuantity(firstToken, secondToken, std::abs(change_token1));
                    pool->ExecuteSwap(account, firstToken, secondToken, std::abs(change_token1), output);
                }
                else if (change_token1 > 0){
                    double input = pool->ComputeInputRequirement(secondToken, firstToken, change_token1);
                    pool->ExecuteSwap(account, secondToken, firstToken, input, change_token1);


}


}
