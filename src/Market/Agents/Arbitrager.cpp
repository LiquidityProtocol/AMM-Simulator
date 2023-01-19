#include "Arbitrager.hpp"

#include "../Strategy/Strat_MovingAverage.hpp"
#include "../Strategy/Strat_LinearRegression.hpp"
#include "../Strategy/Strat_Greedy.hpp"

#include "../../Protocols/Protocols.hpp"

#include <cassert>

Arbitrager::Arbitrager(const std::string &name, double budget) : Account(name, budget) {}

void Arbitrager::sendStrategicSignal(PoolInterface *pool) {
    std::vector<Signal> TradeSignals;

    if (strat == STRATEGY::SIMPLE_MOVING_AVERAGE) {
        MovingAverage::calculateSignal(TradeSignals, pool, false);
    } else if (strat == STRATEGY::EXP_MOVING_AVERAGE) {
        MovingAverage::calculateSignal(TradeSignals, pool, true);
    } else if (strat == STRATEGY::LINEAR_REGRESSION) {
        LinearRegression::calculateSignal(TradeSignals, pool);
    } else if (strat == STRATEGY::HASH_AI) {
    } else {
        assert(strat == STRATEGY::NAIVE_GREEDY);
        assert(GetPoolType(pool) == PROTOCOL::UNISWAP_V2);

        Greedy::calculateSignal(TradeSignals, pool);
    }

    for (Signal s : TradeSignals) {
        Token *input = s.input_token();
        Token *output = s.output_token();
        PoolInterface *pool = s.pool();

        double volume = total_value() * 0.2;
        double quantity = volume / input->real_value();

        while (GetQuantity(input) < quantity * 1.8) {
            try {
                buy(input, quantity * 2 - GetQuantity(input));
            } catch (std::invalid_argument &e) {
                for (auto [token, quantity] : wallet()) {
                    if (token == input) continue;
                    if (token -> pool()) continue;

                    sell(token, quantity * 0.4);
                }
                quantity *= 0.95;
            }
        }
        handler->requestSignal(this, Signal(pool, input, output, quantity));
    }
}

void Arbitrager::setStrategy(STRATEGY strat) {
    this->strat = strat;
}

void Arbitrager::setHandler(SignalsHandler *handler) {
    this->handler = handler;
}

void Arbitrager::endEpoch() {
    StratHistory.push_back(strat);
    ValueHistory.push_back(total_value());
}
