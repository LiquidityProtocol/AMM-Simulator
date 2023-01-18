#include "Market.hpp"
#include <iostream>
#include <random>

//std::default_random_engine generator;
//std::normal_distribution<double> rnorm(0.0, 1.0);
//std::uniform_real_distribution<double> runi(0.0, 1.0);


double Market::ProfitLP(PoolInterface *pool) {
    // Provision data part

//    // Here we determine the provider account
//    auto it = existing_accounts_.find("Provider");
//    it -> first;
//    Account *LP = it -> second;

    // Without provision
    double hold_value = 0;
    double pool_share = 0;

    for (auto op : pool->ledger())
        if (op->operation_type() == "PROVIDE") {
            auto input = op->input();
            auto output = op->output();

            assert(output.size() == 1);
            pool_share += output.begin()->second;

            for (auto [token, quantity] : input)
                hold_value += quantity * token->real_value();
         }
    if (hold_value == 0)
        return 0;
    // With provision
    double value_provide = pool->pool_token_value() * pool_share;
    double nominal_profit = value_provide - hold_value;
    double relative_profit = nominal_profit / hold_value;
    std::cerr << relative_profit << std::endl;

    return relative_profit;
}

//    // Here we determine the initial amount of tokens provided
//    std::vector<double> token_amounts = Retrieve_provided(pool);
//    double token1_init_provided = token_amounts[0];
//    double token2_init_provided = token_amounts[1];


//    // Here gotta have the market ratio at provision double market_ratio_provision =
//    // double token2_init_provided = market_ratio_provision * token1_init_provided
//    // double token1_price = token2_price * (1 / market_ratio)

//    // Token 2 price is stable as we said
//    double token2_price = 1;
//    double token1_price = 100;

//    // Withdrawal data part
//    // Quantities withdrawn from the pool by the LP
//    // double token1_final = LP -> GetQuantity(token1);
//    // double token2_final = LP -> GetQuantity(token2);

//    double final_price_token1 = (token2_final / token1_final) * token2_price;   // Final price of token_1

//    // Nominal loss calculation
//    double value_hold = final_price_token1 * token1_init_provided + token2_price * token2_init_provided; // Money if the LP just held his crypto
//    double value_provide = final_price_token1 * token1_final + token2_price * token2_final; // LP Money after providing and withdrawing
//    double nominal_loss = value_hold - value_provide; // Nominal  Loss experienced by the LP

//    // Divergence loss calculation
//    double price_ratio = final_price_token1 / token1_price;
//    double divergence_loss = (2 * sqrt(price_ratio) / (1 + price_ratio)) - 1;

//    return divergence_loss;



    /*
    vector<double> sample_trades{100, 500, 1000, 1500, 2000, 2500, 3000};
    int n = sample_trades.size();
    vector<double> total_divergence_loss(n);

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
*/
