#ifndef ARBITRAGER_HPP
#define ARBITRAGER_HPP

#include "../Infrastructure/SignalsHandler.hpp"

enum STRATEGY {
    NAIVE_GREEDY,
    HASH_AI,
    SIMPLE_MOVING_AVERAGE,
    EXP_MOVING_AVERAGE,
    LINEAR_REGRESSION,
    MEAN_REVERSION
};

static const std::unordered_map<STRATEGY, QString> STRATEGY_NAME({
    {STRATEGY::EXP_MOVING_AVERAGE, "EXP_MOVING_AVERAGE"},
    {STRATEGY::HASH_AI, "HASH_AI"},
    {STRATEGY::LINEAR_REGRESSION, "LINEAR_REGRESSION"},
    {STRATEGY::MEAN_REVERSION, "MEAN_REVERSION"},
    {STRATEGY::NAIVE_GREEDY, "NAIVE_GREEDY"},
    {STRATEGY::SIMPLE_MOVING_AVERAGE, "NAIVE_GREEDY"}
});

class Arbitrager : public Account {
public:
    Arbitrager(const std::string &name, double budget);

    void sendStrategicSignal(PoolInterface *pool);
    void setStrategy(STRATEGY strat);
    void setHandler(SignalsHandler *handler);

    void endEpoch();
private:
    STRATEGY strat = STRATEGY::NAIVE_GREEDY;

    std::vector<STRATEGY> StratHistory;
    std::vector<double> ValueHistory;

    SignalsHandler *handler;
};

Q_DECLARE_METATYPE(STRATEGY);

#endif
