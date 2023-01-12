#include "Utilities.hpp"
#include "../Protocols/UniswapV2Pool.hpp"
#include <iostream>
#include <cmath>
using namespace std;

// First I implement it for one pool using Gaussian Distribution
double Divergence_loss_sim_no_fee(double iteration_counter) {
    for (int i = 0; i < iteration_counter; i++) {
        Token *token1 = Token::GetToken("token1");
        Token *token2 = Token::GetToken("token2");
        UniswapV2Pool pool1({{token1, 1000}, {token2, 1000}});
        UniswapV2Pool pool2({{token1, 900}, {token2, 1111}});
        Account *LP = Account::GetAccount("LP");
        LP -> Deposit(token1, 20);
        LP -> Deposit(token2, 20);
        cout << "\n Token1 of LP before:" << LP -> GetQuantity(token1);
        cout << "\n Token2 of LP before:" << LP -> GetQuantity(token2);
        LP -> Provide(&pool1, {{token1, 20}, {token2, 20}});
        cout << "\n pool q token 1: " << pool1.GetQuantity(token1);
        cout << "\n pool q token 2: " << pool1.GetQuantity(token2);
        LP -> Withdraw(&pool2, LP -> GetQuantity(pool1.pool_token()));
        cout << "\n Token1 of LP after:" << LP -> GetQuantity(token1);
        cout << "\n Token2 of LP after:" << LP -> GetQuantity(token2);
    }
    return 0;


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