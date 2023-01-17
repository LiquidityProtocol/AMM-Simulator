#ifndef ARBITRAGER_HPP
#define ARBITRAGER_HPP

#include "../Infrastructure/Events.hpp"

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

    void ApplyStrategy(STRATEGY strat, PoolInterface *pool);
};

#endif