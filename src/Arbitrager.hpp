#ifndef ARBITRAGER_HPP
#define ARBITRAGER_HPP

#include <unordered_map>
#include <stdexcept>
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

    /// @brief Execute arbitrage on a pool with a given input token and output token.
    /// NOT WORKING, IT IS JUST A SKETCH TO SEE THE GENERAL IDEA
    /*def findArb(PoolInterface *pool, Token *input_token, tokToken *output_tokenenOut, maxHops, currentPairs, path, bestTrades, count=5):
    for i in range(len(pairs)):
        newPath = path.copy()
        pair = pairs[i]
        if not pair['token0']['address'] == tokenIn['address'] and not pair['token1']['address'] == tokenIn['address']:
            continue
        if pair['reserve0']/pow(10, pair['token0']['decimal']) < 1 or pair['reserve1']/pow(10, pair['token1']['decimal']) < 1:
            continue
        if tokenIn['address'] == pair['token0']['address']:
            tempOut = pair['token1']
        else:
            tempOut = pair['token0']
        newPath.append(tempOut)
        if tempOut['address'] == tokenOut['address'] and len(path) > 2:
            Ea, Eb = getEaEb(tokenOut, currentPairs + [pair])
            newTrade = { 'route': currentPairs + [pair], 'path': newPath, 'Ea': Ea, 'Eb': Eb }
            if Ea and Eb and Ea < Eb:
                newTrade['optimalAmount'] = getOptimalAmount(Ea, Eb)
                if newTrade['optimalAmount'] > 0:
                    newTrade['outputAmount'] = getAmountOut(newTrade['optimalAmount'], Ea, Eb)
                    newTrade['profit'] = newTrade['outputAmount']-newTrade['optimalAmount']
                    newTrade['p'] = int(newTrade['profit'])/pow(10, tokenOut['decimal'])
                else:
                    continue
                bestTrades = sortTrades(bestTrades, newTrade)
                bestTrades.reverse()
                bestTrades = bestTrades[:count]
        elif maxHops > 1 and len(pairs) > 1:
            pairsExcludingThisPair = pairs[:i] + pairs[i+1:]
            bestTrades = findArb(pairsExcludingThisPair, tempOut, tokenOut, maxHops-1, currentPairs + [pair], newPath, bestTrades, count)
    return bestTrades */

   void Arbitrage(PoolInterface *pool) {
        std::unordered_map<Token *, double> wallet = GetWallet();
        std::vector<Token *> tokens_in_wallet;
        tokens_in_wallet.reserve(wallet.size());
        for(auto kv : wallet) {
            tokens_in_wallet.push_back(kv.first);
        }
        for (int i=0; i<wallet.size(); i++) {
            for (int k=0; k<wallet.size(); k++) {
               /*Trade(PoolInterface *pool, Token *input_token, Token *output_token, double input_quantity)*/
                if (wallet[tokens_in_wallet[k]] >= 1) {
                    if ( (*pool).InPool(*tokens_in_wallet[k]) == true ) {
                        std::unordered_set<Token *> tokens_in_pool = (*pool).tokens();
                        for (int i=0; i<tokens_in_pool.size(); i++) {
                            double outputquantity = (*pool).SimSwap(*tokens_in_wallet[k], *tokens_in_pool[i], 1);
                            while (outputquantity*((*tokens_in_pool[i]).real_value()) + (wallet[tokens_in_wallet[k]]-1)*((*tokens_in_wallet[k]).real_value()) > wallet[tokens_in_wallet[k]]*((*tokens_in_wallet[k]).real_value())) {
                                Trade(*pool, *tokens_in_wallet[k], *tokens_in_pool[i], 1);
                            }
                        } 
                    }
                }
            }     
        }
   }

};



#endif