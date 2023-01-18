#ifndef STRAT_HASH_AI
#define STRAT_HASH_AI

#include "../Infrastructure/Signals.hpp"
#include "../../Utilities/Utilities.hpp"
#include "../../Protocols/Protocols.hpp"

namespace HashAI {
    TradeRoute *findArbs(std::unordered_set<PoolInterface *> pools);
    void loadPools() {
    }
};

#endif
