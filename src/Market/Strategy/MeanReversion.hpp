#ifndef STRAT_MEAN_REVERSION
#define STRAT_MEAN_REVERSION

#include "../Infrastructure/Market.hpp"
#include "../Infrastructure/Events.hpp"

namespace MeanReversion {
    typedef std::unordered_map<Token *, std::unordered_map<Token *, double> > SpotPriceMat;

    double calculateMean(std::vector<Operation *> bars) {
        double mean = 0;
        PoolInterface *pool = nullptr;

        for (Operation *ops : bars) {
            if (pool == nullptr) {
                pool = ops->pool();
            }
            assert(pool == ops->pool());

            for (Token *a : pool->tokens())
            for (Token *b : pool->tokens())
                mean += ops->GetSpotPrice(a, b);
        }
        if (pool == nullptr) {
            throw std::invalid_argument("Empty List of Operations");
        } else {
            mean /= bars.size() * pool->tokens().size() * pool->tokens().size();
        }
        return mean;
    }

    void calculateSignal(std::vector<Signal> &signal, Market *market) {
        for (PoolInterface *pool : market->GetMarketPools()) {
            std::vector<Operation *> bars_20 = pool->GetLatestOps(20);

            if (bars_20.empty())
                continue;

            double mean = calculateMean(bars_20);

            double deviation_limit = 0.05;

            for (Token *a : pool->tokens())
            for (Token *b : pool->tokens())
                if (b->name() != a->name() && abs(mean - pool->GetSpotPrice(a, b)) > deviation_limit * mean) {
                    signal.push_back(Signal(pool, b, a));
                }
        }
    }
}

#endif



