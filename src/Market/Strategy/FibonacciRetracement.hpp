#ifndef STRAT_FIBONACCI_RETRACEMENT
#define STRAT_FIBONACCI_RETRACEMENT

#include "../Infrastructure/Signals.hpp"

// This code is for a trading strategy based on Fibonacci retracements. 
// A Fibonacci retracement is a technical analysis tool that uses horizontal
// lines to indicate areas where a financial instrument may experience support 
// or resistance. The strategy is to generate a trading signal when the price
// of an asset reaches a certain retracement level. 


namespace FibonacciRetracement {
// Define a struct to hold the start and end points of a price move
struct PriceMove {
double start;
double end;
};

// Function to calculate the Fibonacci retracement levels
std::unordered_map<double, double> calculateRetracementLevels(PriceMove move) {
    std::unordered_map<double, double> levels;
    // Fibonacci levels we want to calculate
    double retracementLevels[] = {0.236, 0.382, 0.5, 0.618, 0.786};
    double range = move.end - move.start;
    // Calculate the price level for each retracement level
    for (double level : retracementLevels) {
        levels[level] = move.start + range * level;
    }
    return levels;
}

// Function to generate signals based on retracement levels
void calculateSignal(std::vector<Signal> &signals, PoolInterface *pool, PriceMove move) {
    // Get the latest prices for the given pool
    std::vector<Operation *> latestPrices = pool->GetLatestOps(1);
    if (latestPrices.empty())
        return;

    // Get the current price for each trading pair in the pool
    std::unordered_map<Token *, std::unordered_map<Token *, double> > currentPrices;
    for (Operation *op : latestPrices) {
        for (Token *base : pool->tokens()) {
            for (Token *quote : pool->tokens()) {
                if (base->name() != quote->name()) {
                    currentPrices[base][quote] = op->GetSpotPrice(base, quote);
                }
            }
        }
    }

    // Calculate the retracement levels
    std::unordered_map<double, double> retracementLevels = calculateRetracementLevels(move);

    // Check if current price has hit any of the retracement levels
    for (Token *base : pool->tokens()) {
        for (Token *quote : pool->tokens()) {
            if (base->name() != quote->name()) {
                double currentPrice = currentPrices[base][quote];
                for (auto level : retracementLevels) {
                    if (currentPrice >= level.second * 0.99 && currentPrice <= level.second * 1.01) {
                        signals.push_back(Signal(pool, base, quote, level.first));
                    }
                }
            }
        }
    }
}
}

#endif