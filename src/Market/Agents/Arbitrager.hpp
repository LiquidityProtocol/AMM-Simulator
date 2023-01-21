#ifndef ARBITRAGER_HPP
#define ARBITRAGER_HPP

#include "../Infrastructure/SignalsHandler.hpp"

enum STRATEGY {
    NAIVE_GREEDY,
    SIMPLE_MOVING_AVERAGE,
    EXP_MOVING_AVERAGE,
    LINEAR_REGRESSION,
    MEAN_REVERSION
};

namespace std {
    template <>
    struct hash<STRATEGY> {
        size_t operator()(const STRATEGY &k) const {
            return static_cast<std::size_t>(k);
        }
    };
}

static const std::unordered_map<STRATEGY, QString> STRATEGY_NAME({
    {STRATEGY::SIMPLE_MOVING_AVERAGE, "MOVING_AVERAGE"},
    {STRATEGY::EXP_MOVING_AVERAGE, "EXP_MOVING_AVERAGE"},
    {STRATEGY::LINEAR_REGRESSION, "LINEAR_REGRESSION"},
//    {STRATEGY::MEAN_REVERSION, "MEAN_REVERSION"},
    {STRATEGY::NAIVE_GREEDY, "NAIVE_GREEDY"},
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
