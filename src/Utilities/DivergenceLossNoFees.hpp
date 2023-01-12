#include "Utilities.hpp"
#include "../Protocols/UniswapV2Pool.hpp"
#include <iostream>
#include <cmath>
using namespace std;

vector<double> Divergence_loss_UNISWAP_visualisation() {

    int n = 7;
    vector<double> sample_trades{100, 500, 1000, 1500, 2000, 2500, 3000};
    vector<double> total_divergence_loss(7);

    for (int i = 0; i < n; ++i) {
        // Token initialization
        Token *token1 = Token::GetToken("token1");
        Token *token2 = Token::GetToken("token2");
        double token1_price = 100; // Initial price of token_1 in $
        double token2_price = 1; // Initial price of token_2 in $ - this price will stay constant - assume it is a stablecoin

        UniswapV2Pool pool1({{token1, 10}, {token2, 1000}}); // Pool initialization

        //LP Account setup
        Account *LP = Account::GetAccount("LP");
        double token1_init = 10; // amount of token_1 to be invested
        double token2_init = 1000; // amount of token_2 to be invested
        LP -> Deposit(token1, token1_init);
        LP -> Deposit(token2, token2_init);

        LP -> Provide(&pool1, {{token1, token1_init}, {token2, token2_init}}); // LP Providing liquidity

        // Trader account definition
        Account *trader = Account::GetAccount("Trader");
        trader -> Deposit(token1, 10000); // The number of deposited tokens is arbitrary here, just has to allow for a trade
        trader -> Deposit(token2, 10000);

        // Trade execution
        trader -> Trade(&pool1, token2, token1, sample_trades[i]); // Trade execution

        LP -> Withdraw(&pool1, LP -> GetQuantity(pool1.pool_token())); // LP Withdrawing all funds from the pool

        // Quantities withdrawn from the pool by the LP
        double token1_final = LP -> GetQuantity(token1); 
        double token2_final = LP -> GetQuantity(token2);

        double final_price_token1 = (token2_final / token1_final) * token2_price;   // Final price of token_1 

        // Nominal loss calculation
        double value_hold = final_price_token1 * token1_init + token2_price * token2_init; // Money if the LP just held his crypto
        double value_provide = final_price_token1 * token1_final + token2_price * token2_final; // LP Money after providing and withdrawing
        double nominal_loss = value_hold - value_provide; // Nominal  Loss experienced by the LP
        
        // Divergence loss calculation
        double price_ratio = final_price_token1 / token1_price;
        double divergence_loss = (2 * sqrt(price_ratio) / (1 + price_ratio)) - 1;

        total_divergence_loss[i] = divergence_loss;
    }
    return total_divergence_loss;
}



//The function calculates the divergence loss using the Kullback-Leibler divergence
double Divergence_loss_sim_KL(double iteration_counter) {
    double loss = 0;
    for (int i = 0; i < iteration_counter; i++) {
        Token *token1 = GetToken("token1");
        Token *token2 = GetToken("token2");
        UniswapV2Pool pool1({{token1, 1000}, {token2, 1000}});
        UniswapV2Pool pool2({{token1, 900}, {token2, 1111}});
        Account *LP = GetAccount("LP");
        LP -> Deposit(token1, 20);
        LP -> Deposit(token2, 20);
        LP -> Provide(&pool1, {{token1, 20}, {token2, 20}});
        double qty_pool_token = GetQuantity(LP, pool1.pool_token());
        LP -> Withdraw(&pool2, LP -> GetQuantity(pool1.pool_token()));
        double qty_token1 = GetQuantity(LP, token1);
        double qty_token2 = GetQuantity(LP, token2);
        double current_price = qty_token1 / qty_token2;
        double target_price = 900 / 1111;
        double p = current_price / (current_price + target_price);
        loss += p * log(p / target_price) + (1 - p) * log((1 - p) / (1 - target_price));
    }
    return loss;
}
//The function calculates the divergence loss using the Jensen-Shannon divergence
double Divergence_loss_sim_JS(double iteration_counter) {
    double loss = 0;
    for (int i = 0; i < iteration_counter; i++) {
        Token *token1 = GetToken("token1");
        Token *token2 = GetToken("token2");
        UniswapV2Pool pool1({{token1, 1000}, {token2, 1000}});
        UniswapV2Pool pool2({{token1, 900}, {token2, 1111}});
        Account *LP = GetAccount("LP");
        LP -> Deposit(token1, 20);
        LP -> Deposit(token2, 20);
        LP -> Provide(&pool1, {{token1, 20}, {token2, 20}});
        double qty_pool_token = GetQuantity(LP, pool1.pool_token());
        LP -> Withdraw(&pool2, LP -> GetQuantity(pool1.pool_token()));
        double qty_token1 = GetQuantity(LP, token1);
        double qty_token2 = GetQuantity(LP, token2);
        double current_price = qty_token1 / qty_token2;
        double target_price = 900 / 1111;
        double p = current_price / (current_price + target_price);
        double p_b = (p + target_price) / 2;
        loss += p * log(p / p_b) + (1 - p) * log((1 - p) / (1 - p_b));
    }
    return loss;
}


//this class calculates the divergence loss for a liquidity pool based on the current 
//value, reference value, threshold, and decay factor
class DivergenceLoss {
  public:
    DivergenceLoss(double threshold, double decay) : threshold_(threshold), decay_(decay) {}

    // Computes divergence loss given the current value and the reference value
    double operator()(double value, double reference) {
      double divergence = std::abs(value - reference);
      if (divergence > threshold_) {
        return decay_ * (divergence - threshold_);
      } else {
        return 0.0;
      }
    }

  private:
    double threshold_;
    double decay_;
};
