#ifndef STRAT_RSI
#define STRAT_RSI

#include "../Infrastructure/Market.hpp"
#include "../Infrastructure/Events.hpp"
#include <vector>
#include <unordered_map>

namespace RSI {
    typedef std::unordered_map<Token *, std::unordered_map<Token *, double> > SpotPriceMat;
    
    double calculateChange(std::vector<Operation *> bars, Token *a, Token *b) {
        double change = bars[0]->GetSpotPrice(a, b) - bars[1]->GetSpotPrice(a, b);
        return change;
    }

    double calculateGain(std::vector<Operation *> bars, Token *a, Token *b) {
        double gain = 0;
        for (int i = 1; i < bars.size(); i++) {
            double change = calculateChange(bars, a, b);
            if (change > 0) {
                gain += change;
            }
        }
        return gain;
    }

    double calculateLoss(std::vector<Operation *> bars, Token *a, Token *b) {
        double loss = 0;
        for (int i = 1; i < bars.size(); i++) {
            double change = calculateChange(bars, a, b);
            if (change < 0) {
                loss += -change;
            }
        }
        return loss;
    }

    double calculateRSI(std::vector<Operation *> bars, Token *a, Token *b) {
        double gain = calculateGain(bars, a, b);
        double loss = calculateLoss(bars, a, b);
        double avg_gain = gain / bars.size();
        double avg_loss = loss / bars.size();
        double relative_strength = avg_gain / avg_loss;
        double RSI = 100 - (100 / (1 + relative_strength));
        return RSI;
    }

    void calculateSignal(std::vector<Signal> &signal, Market *market) {
        for (PoolInterface *pool : market->GetMarketPools()) {
            std::vector<Operation *> bars = pool->GetLatestOps(14);

            if (bars.empty())
                continue;

            for (Token *a : pool->tokens())
            for (Token *b : pool->tokens()) {
                double RSI = calculateRSI(bars, a, b);
                if (RSI > 70) {
                    signal.push_back(Signal(pool, a, b));
                }
            }
        }
    }
}

#endif