#ifndef STRAT_BREAKOUT
#define STRAT_BREAKOUT

// Breakout strategy: It is a trend-following strategy that aims to enter
//  a market when the price breaks through a level of resistance or support.

#include "../Infrastructure/Signals.hpp"

namespace Breakout {
typedef std::unordered_map<Token *, std::unordered_map<Token *, double> > SpotPriceMat;

double calculateHigh(std::vector<Operation *> bars) {  // calculate highest price of the period
    double high = 0;
    for (Operation *ops : bars) {
        double spotPrice = ops->GetSpotPrice(ops->base(), ops->quote());
        high = std::max(high, spotPrice);
    }
    return high;
}

double calculateLow(std::vector<Operation *> bars) {  // calculate lowest price of the period
    double low = std::numeric_limits<double>::max();
    for (Operation *ops : bars) {
        double spotPrice = ops->GetSpotPrice(ops->base(), ops->quote());
        low = std::min(low, spotPrice);
    }
    return low;
}

void calculateSignal(std::vector<Signal> &signal, PoolInterface *pool) {
    std::vector<Operation *> bars_20 = pool->GetLatestOps(20);  // consider the last 20 bars

    if (bars_20.empty())
        return;

    double high_20 = calculateHigh(bars_20);
    double low_20 = calculateLow(bars_20);

    std::vector<Operation *> bars_04 = pool->GetLatestOps(4);  // consider the last 4 bars

    double high_04 = calculateHigh(bars_04);
    double low_04 = calculateLow(bars_04);

    double breakout_threshold = 0.02;  // 2% threshold for breakout

    for (Token *a : pool->tokens())
    for (Token *b : pool->tokens())
        if (b->name() != a->name() && (high_04 > (1 + breakout_threshold) * high_20 || low_04 < (1 - breakout_threshold) * low_20)) {
            signal.push_back(Signal(pool, b, a));
        }
}
}

#endif