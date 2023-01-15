#ifndef STRAT_MOVING_AVERAGE
#define STRAT_MOVING_AVERAGE

#include "../Infrastructure/Market.hpp"
#include "../Infrastructure/Events.hpp"

typedef std::unordered_map<Token *, std::unordered_map<Token *, double> > SpotPriceMat;

SpotPriceMat calculateSMA(std::vector<Operation *> bars) {  // simple moving average
    SpotPriceMat temp;
    PoolInterface *pool = nullptr;

    for (Operation *ops : bars) {
        if (pool == nullptr) {
            pool = ops->pool();
        }
        assert(pool == ops->pool());

        for (Token *a : pool->tokens())
        for (Token *b : pool->tokens())
            temp[a][b] += ops->GetSpotPrice(a, b);
    }
    if (pool == nullptr) {
        throw std::invalid_argument("Empty List of Operations");
    } else {
        for (Token *a : pool->tokens())
        for (Token *b : pool->tokens())
            temp[a][b] /= bars.size();
    }
    return temp;
}
SpotPriceMat calculateEMA(std::vector<Operation *> bars) {  // exponential moving average
    SpotPriceMat temp;
    PoolInterface *pool = nullptr;

    double smoothing_parameter = 0.4; //decay factor of terms in Moving Average
    double weight_factor = smoothing_parameter;

    for (Operation *ops : bars) {
        if (pool == nullptr) {
            pool = ops->pool();
        }
        assert(pool == ops->pool());

        for (Token *a : pool->tokens())
        for (Token *b : pool->tokens()) {
            temp[a][b] += ops->GetSpotPrice(a, b) * weight_factor;
            weight_factor *= (1 - smoothing_parameter);
        }
    }
    if (pool == nullptr) {
        throw std::invalid_argument("Empty List of Operations");
    }

    return temp;
}

std::vector<Event> calculateSignal(Market *market, bool EMA) {
    std::vector<Event> signal;

    for (PoolInterface *pool : market->GetMarketPools()) {
        std::vector<Operation *> bars_06 = pool->GetLatestOps(6);
        std::vector<Operation *> bars_11 = pool->GetLatestOps(11);

        if (bars_11.empty())
            continue;

        SpotPriceMat MA_06 = EMA ? calculateEMA(bars_06) : calculateSMA(bars_06);
        SpotPriceMat MA_11 = EMA ? calculateEMA(bars_11) : calculateSMA(bars_11);

        double mark_up = 0.05;

        for (Token *a : pool->tokens())
        for (Token *b : pool->tokens())
            if (MA_06[b][a] > (1 - mark_up) * MA_11[b][a]) {
                signal.push_back(Event(pool, b, a));
            }
    }
    return signal;
}

#endif
