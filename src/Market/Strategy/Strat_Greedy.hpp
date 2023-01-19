#ifndef STRAT_GREEDY_HPP
#define STRAT_GREEDY_HPP

#include "../Infrastructure/Signals.hpp"
#include <cmath>

namespace Greedy {
    void calculateSignal(std::vector<Signal> &signal, PoolInterface *pool) {
        Token *token1 = *(pool->tokens()).begin();
        Token *token2 = *(++(pool->tokens()).begin());

        double PoolRatio = pool->GetSpotPrice(token1, token2);
        double MarketRatio = token2->real_value() / token1->real_value();

        double volume1 = token1->real_value() * pool->GetQuantity(token1);
        double volume2 = token2->real_value() * pool->GetQuantity(token2);

        if (PoolRatio >= MarketRatio) {
            std::swap(token1, token2);
            std::swap(volume1, volume2);
        }
        // token1 is being over estimated
        assert(volume1 < volume2 + 1e-4);

        signal.push_back(Signal(pool, token1, token2));
    }
};

#endif // STRAT_GREEDY_HPP
