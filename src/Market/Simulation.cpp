#include "Simulation.hpp"
#include <QThread>

Simulation::Simulation() {
    market_ = new Market();
    handler = new SignalsHandler();
    arb_ = new Arbitrager("Poor Combi", 10000);
    LP_ = new Provider("Rich Combi", 100000);

    arb_->setHandler(handler);
    market_->setHandler(handler);
}

std::unordered_set<PoolInterface *> Simulation::GetPools() const {
    return market_->GetMarketPools();
}
std::unordered_set<Token *> Simulation::GetTokens() const {
    return market_->GetMarketTokens();
}

Market *Simulation::GetMarket() const {
    return market_;
}

Arbitrager *Simulation::GetArb() const {
    return arb_;
}
Provider *Simulation::GetLP() const {
    return LP_;
}

void Simulation::runEpoch() {
    for (auto pool : GetPools()) {
        arb_->sendStrategicSignal(pool);
        LP_->StrategicProvide(pool);
    }
    market_->runEpoch();
    handler->respondSignals();

    for (auto pool : GetPools())
        pool->endEpoch();

    arb_->endEpoch();
    LP_->endEpoch();
}
