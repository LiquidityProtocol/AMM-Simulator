#include "StrategyHeader.hpp"
#include "Strat_HashAI.hpp"
#include "Strat_LinearRegression.hpp"
#include "Strat_MovingAverage.hpp"

#include <cassert>

void Arbitrager::sell(Token *token, double quantity) {
    if (GetQuantity(token) < quantity) {
        throw std::invalid_argument("Not enough token to sell");
    } else {
        Deposit(token, -quantity);
    }
}

void Arbitrager::buy(Token *token, double quantity) {
    if (total_value() < token->real_value() * quantity) {
        throw std::invalid_argument("Not enough cash to buy token");
    } else {
        Deposit(token, quantity);
    }
}

double Arbitrager::ExecuteSignal(Signal *s, double input_quantity) {
    Token *input_token = s->input_token();
    Token *output_token = s->output_token();

    if (GetQuantity(input_token) < input_quantity) {
        buy(input_token, input_quantity - GetQuantity(input_token));
    }

    return Trade(s->pool(), input_token, output_token, input_quantity);
}
double Arbitrager::ExecuteTradeRoute(TradeRoute *route, double input_quantity) {
    for (Signal *node = route->head() ; node ; node = node->next())
        input_quantity = ExecuteSignal(node, input_quantity);

    return input_quantity;
}

void Arbitrager::ApplyStrategy(STRATEGY strat, Market *market) {
    std::vector<Signal> vec;

    if (strat == STRATEGY::SIMPLE_MOVING_AVERAGE) {
        MovingAverage::calculateSignal(vec, market, false);
    } else if (strat == STRATEGY::EXP_MOVING_AVERAGE) {
        MovingAverage::calculateSignal(vec, market, true);
    } else if (strat == STRATEGY::LINEAR_REGRESSION) {
        LinearRegression::calculateSignal(vec, market);
    } else if (strat == STRATEGY::HASH_AI) {
    } else {
        assert(strat == STRATEGY::NAIVE_GREEDY);


    }
}
