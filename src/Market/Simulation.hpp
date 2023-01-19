#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "Infrastructure/Market.hpp"
#include "Infrastructure/SignalsHandler.hpp"

#include "Agents/Arbitrager.hpp"
#include "Agents/Provider.hpp"

//#include "Strategy/Strat_HashAI.hpp"
//#include "Strategy/Strat_MovingAverage.hpp"
//#include "Strategy/Strat_LinearRegression.hpp"

class Simulation {
public:
    Simulation();

    std::unordered_set<PoolInterface *> GetPools() const;
    std::unordered_set<Token *> GetTokens() const;

    Market *GetMarket() const;
    Account *GetArb() const;
    Account *GetLP() const;

    void runEpoch();
private:
    Market *market_;
    Arbitrager *arb_;
    Provider *LP_;

    SignalsHandler *handler;
};

#endif // SIMULATION_HPP
