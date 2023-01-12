#include "Utilities.hpp"
#include "../Protocols/UniswapV2Pool.hpp"
#include <iostream>
#include <cmath>
using namespace std;

double Divergence_loss_sim_with_fee(double iteration_counter, double set_fee) {
    double loss = 0;
    for (int i = 0; i < iteration_counter; i++) {
        Token *token1 = Token::GetToken("token1");
        Token *token2 = Token::GetToken("token2");
        UniswapV2Pool pool1({{token1, 1000}, {token2, 1000}});
        UniswapV2Pool pool2({{token1, 900}, {token2, 1111}});
        Account *LP = Account::GetAccount("LP");
        LP -> Deposit(token1, 20);
        LP -> Deposit(token2, 20);
        LP -> Provide(&pool1, {{token1, 20}, {token2, 20}});
        double qty_pool_token = LP -> GetQuantity(pool1.pool_token());
        double fee = set_fee;
        LP -> Withdraw(&pool2, qty_pool_token * (1 - fee));
        double qty_token1 = LP -> GetQuantity(token1);
        double qty_token2 = LP -> GetQuantity(token2);
        double current_price = qty_token1 / qty_token2;
        double target_price = 900 / 1111;
        loss += std::abs(current_price - target_price);
    }
    return loss;
}