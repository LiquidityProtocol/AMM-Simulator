#ifndef FIRSTSIMULATION_H
#define FIRSTSIMULATION_H
#include <unordered_map>
#include <vector>
#include "Utilities.hpp"


//#include <src/Utilities/FirstSimulation.cpp>


double action_type(double market_price_ratio, double pool_price_ratio);
Token* trade_sim_tokenchoice(Token* tok1, Token* tok2 );
double trade_sim_tradeval(double market_token, double trader_token);
double arb_simulation(double market_exchange_rate, double quantity1, double quantity2);
double provision_type();
std::unordered_map<Token *, double> liquidity(double market_token1, double market_token2, double lp_token1, double lp_token2, Token *token1, Token *token2);
double random_withdrawal (double pool_tokens);

void print(std::vector<double> const &input);

void SimulationOne();

void SimulationTwo();


#endif // FIRSTSIMULATION_H
