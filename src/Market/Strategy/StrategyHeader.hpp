#ifndef STRATEGY_HEADER_HPP
#define STRATEGY_HEADER_HPP

#include "../Infrastructure/Events.hpp"
#include "../Infrastructure/Market.hpp"

enum STRATEGY {
    NAIVE_GREEDY,
    HASH_AI,
    SIMPLE_MOVING_AVERAGE,
    EXP_MOVING_AVERAGE,
    LINEAR_REGRESSION,
    MEAN_REVERSION
};

class Arbitrager : public Account {
public:
    void sell(Token *token, double quantity);
    void buy(Token *token, double quantity);

    double ExecuteSignal(Signal *s, double input_quantity);
    double ExecuteTradeRoute(TradeRoute *route, double input_quantity);

    void ApplyStrategy(STRATEGY strat, Market *market);
};

#endif
