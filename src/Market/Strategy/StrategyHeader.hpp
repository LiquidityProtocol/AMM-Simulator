#ifndef STRATEGY_HEADER_HPP
#define STRATEGY_HEADER_HPP

#include "../Infrastructure/Events.hpp"

enum STRATEGY {
    HASH_AI,
    SIMPLE_MOVING_AVERAGE,
    EXP_MOVING_AVERAGE,
    LINEAR_REGRESSION
};

class Arbitrager : public Account {
public:
    void sell(Token *token, double quantity);
    void buy(Token *token, double quantity);

    double ExecuteSignal(Event *event, double input_quantity);
    double ExecuteTradeRoute(TradeRoute *rout, double input_quantity);

    void ApplyStrategy(STRATEGY strat);
};

#endif
