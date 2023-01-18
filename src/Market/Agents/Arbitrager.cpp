#include "Arbitrager.hpp"
#include "../Strategy/Strat_HashAI.hpp"
#include "../Strategy/Strat_MovingAverage.hpp"
#include "../Strategy/Strat_LinearRegression.hpp"

#include "../../Protocols/Protocols.hpp"

#include <cassert>

Arbitrager::Arbitrager(const std::string name, double budget) : Account(name) {
    budget_ = budget;
}

void Arbitrager::sell(Token *token, double quantity) {
    if (GetQuantity(token) < quantity) {
        throw std::invalid_argument("Not enough token to sell");
    } else {
        Deposit(token, -quantity);
        budget_ += quantity * token->real_value();
    }
}

void Arbitrager::buy(Token *token, double quantity) {
    if (budget() < token->real_value() * quantity) {
        throw std::invalid_argument("Not enough cash to buy token");
    } else {
        Deposit(token, quantity);
        budget_ -= quantity * token->real_value();
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

void Arbitrager::ApplyStrategy(STRATEGY strat, PoolInterface *pool) {
    std::vector<Signal> vec;

    if (strat == STRATEGY::SIMPLE_MOVING_AVERAGE) {
        MovingAverage::calculateSignal(vec, pool, false);
    } else if (strat == STRATEGY::EXP_MOVING_AVERAGE) {
        MovingAverage::calculateSignal(vec, pool, true);
    } else if (strat == STRATEGY::LINEAR_REGRESSION) {
        LinearRegression::calculateSignal(vec, pool);
    } else if (strat == STRATEGY::HASH_AI) {
    } else {
        assert(strat == STRATEGY::NAIVE_GREEDY);
        assert(GetPoolType(pool) == PROTOCOL::UNISWAP_V2);


    }
}

double Arbitrager::budget() const {
    return budget_;
}

double Arbitrager::value() const {
    return total_value_ + budget_;
}
