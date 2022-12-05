#ifndef ARBITRAGER_HPP
#define ARBITRAGER_HPP

#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <stdexcept>
#include <cmath>
#include "PoolInterface.hpp"
#include "Token.hpp"
#include "Account.hpp"

class Arbitrager : public Account {

public:
    using Account::Account;

    void ExecuteArbitrage(PoolInterface *pool, Token *input_token, Token *output_token, double input_quantity) {
        if (Account::GetQuantity(input_token) < input_quantity)
        {
            throw std::invalid_argument("Not enough input token to execute arbitrage.");
        }


        Account::Trade(pool, input_token, output_token, input_quantity);
        

    }

    void find_cycles(std::vector<PoolInterface *> pools, Token *token, std::unordered_set<Token *> visited, std::vector<std::unordered_set<Token *>> &cycles) {
        // Does not work completely yet
        // find cycles from token to token
        // store each cycle as a set of tokens in a vector
        if (visited.count(token)) {
            cycles.push_back(visited);
        }

        else {
            visited.emplace(token);
            for (auto pool : pools) {
                if (pool->InPool(token)) {
                    for (auto other_token : pool->tokens()) {
                        if (other_token != token) {
                            find_cycles(pools, other_token, visited, cycles);
                        }
                    }
                }
            }
        }
    }



    double Arbitrage_one_pool(PoolInterface *pool) {
        double gain = 0;
        std::unordered_map<Token *, double> wallet = GetWallet();
        std::unordered_set<Token *> tokens_in_wallet; // Get all types of currency in my wallet
        tokens_in_wallet.reserve(wallet.size());
        for(auto iterator_wallet : wallet) {
            tokens_in_wallet.insert(iterator_wallet.first);
        }
        for ( auto iterator_tokens_wallet = tokens_in_wallet.begin(); iterator_tokens_wallet != tokens_in_wallet.end(); ++iterator_tokens_wallet ) {
        //For each of the currencies I test whether it is better to exchange it
            for (int k=0; k<wallet.size(); k++) {
                if (wallet[*iterator_tokens_wallet] >= 1) {
                    if ( (*pool).InPool(*iterator_tokens_wallet) ) {
                        std::unordered_set<Token *> tokens_in_pool = (*pool).tokens();
                        for (auto iterator_tokens_pool=tokens_in_pool.begin(); iterator_tokens_pool != tokens_in_pool.end(); ++iterator_tokens_pool) {
                            double outputquantity = (*pool).SimSwap(*iterator_tokens_wallet, *iterator_tokens_pool, 1);
                            if ( outputquantity*((*(*iterator_tokens_pool)).real_value()) - (*(*iterator_tokens_wallet)).real_value() > gain) {
                                //Save this operation if it is better than the previous ones
                                //My gain is what I get - what I put (1 input token)
                                gain = outputquantity*((*(*iterator_tokens_pool)).real_value()) - (*(*iterator_tokens_wallet)).real_value();
                                Token output_token = *iterator_tokens_pool;
                                Token input_token = *iterator_tokens_wallet;
                            }
                        }
                    }
                }
            }
        }
        if (gain > 0) {
            Trade(*pool, *input_token, *output_token, 1); //If the best operation has strictly positive gain we do it
        }
        return gain;
   } 
    /*
   void Arbitrage_all_pools() {
        double profit = 0;
        Need a list with all pools to call Arbitrage_one_pool(*pool) for all pools to get which one is best.
   }
   */


};

//Optimal amount function which does not work yet
double optimalAmount(PoolInterface *pools, Token *input_token, double previous_traded_amount, double gas_fees)
{
    //A->B->C->A
    //If we want delta_b which is from B to C, we need to use the token quantities of the pool A, B !!
    
    //iterate over all pools and append the token quantities to a vector
    std::vector<PoolInterface *> pool_vector;
    for (auto pool = pools.begin(); pool != pools.end(); ++pool) {
        std::unordered_set<Token *> tokens = pool.tokens();
        std::vector<Token *> token_vector;
        for (auto token = tokens.begin(); token != tokens.end(); ++token) {
            token_vector.push_back(pool.GetQuantity(token));
        }
        pool_vector.push_back(token_vector);
    }

    //iterate over all pools and calculate the optimal amount of tokens to trade
    double optimal_amount;
    std::vector<Token *> quantities[(pool_vector.size() + 2)*2];
    Token *temp_token = input_token;
    quantities.push_back(pool_vector[0].GetQuantity(temp_token));
    for (auto pool : pool_vector) {
        for (auto token : pool) {
            if (token != input_token) {
             
            
                if (token == temp_token)
                {
                    quantities.insert(quantities.begin(), pool.GetQuantity(token));
                }
                quantities.push_back(pool.GetQuantity(token));
                temp_token = token;
        }
     }
    }

    double E0 = quantities[0]*quantities[2]/(quantities[2]+quantities[1]*gas_fees);
    double E1 = gas_fees* quantities[1] * quantities[3] / (quantities[2] + quantities[1] * gas_fees);

    optimal_amount = (sqrt(E0*E1*gas_fees) - E0)/gas_fees;
    return optimal_amount;
}

#endif