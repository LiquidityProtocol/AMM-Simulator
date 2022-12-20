#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "../Protocols/Protocols.hpp"
#include "../Utilities/Utilities.hpp"

#include <cmath>
#include <random>
#include <vector>

enum Action {
    PROVIDE = 0,
    TRADE = 1
};
// the LP doesn't have incentive to WITHDRAW at the middle of the simulation bc:
// - if he is having profit, he would withdraw all the share and the simulation is done
// - otherwise, the withdraw amount woule become permanent loss and is not profitable

class ActionInfo {
public:
    ActionInfo(Action type, PoolInterface *pool, double x);
    ~ActionInfo() = default;

    Action getType() const;
    double getSlippage() const;
    double cntPoolToken() const;

    double getPoolShareValue() const;
    double getSpotPrice(Token *a, Token *b) const;
private:
    Action type_;
    // action config
    double receivedPoolTokens_;
    double slippage_;

    // pool config
    double poolShareValue_;
    std::unordered_map<Token *, std::unordered_map<Token *, double>> spotPriceMat; // pool config
};
class ActionHistory {
public:
    void addEvent(ActionInfo event);
    size_t size();

    ActionInfo operator[](int i) const;
private:
    std::vector<ActionInfo> history_;
};

class Simulation {
public:
    Simulation(PoolInterface *pool, int nArbs, int nEpochs);
    ~Simulation() = default;

    void runEpoch();
    void Provide(double expectedPoolTokenQuantity);

    ActionHistory getHistory();
private:
    bool converged_ = false;
    int nEpochs_;
    int nArbs_;
    int epoch;
    PoolInterface *pool_;
    Protocol poolType_;

    Account *simulationTrader;
    Account *simulationProvider;

    ActionHistory history_;

    static std::default_random_engine generator;
    static std::normal_distribution<double> distribution;

    double calcOptimalAmount(Token *input_token, Token *output_token);
};
#endif