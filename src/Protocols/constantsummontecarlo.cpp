#include <iostream>
#include <random>
#include <unordered_map>

#include "ConstantSum.hpp"

// Define a simple Token class for testing
class Token {
public:
    Token(std::string symbol) : symbol_(symbol) {}

    std::string GetSymbol() const { return symbol_; }

private:
    std::string symbol_;
};

int main() {
    // Create some tokens
    Token token1("TOKEN1");
    Token token2("TOKEN2");
    Token token3("TOKEN3");

    // Initialize the quantities of the tokens in the pool
    std::unordered_map<Token*, double> quantities = {
        {&token1, 10},
        {&token2, 20},
        {&token3, 30}
    };

    // Initialize the slopes of the tokens in the pool
    std::unordered_map<Token*, double> slopes = {
        {&token1, 1},
        {&token2, 2},
        {&token3, 3}
    };

    // Create a ConstantSum object with a pool fee of 0.1
    ConstantSum pool(quantities, slopes, 0.1);

    // Set up a random number generator
    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<double> dist(0, 1);

    // Run the Monte Carlo simulation for 1000 iterations
    for (int i = 0; i < 1000; i++) {
        // Generate a random number between 0 and 1
        double r = dist(rng);

        if (r < 0.3) {
            // 30% chance of adding a random quantity of TOKEN1 to the pool
            quantities[&token1] += dist(rng) * 100;
        } else if (r < 0.6) {
            // 30% chance of removing a random quantity of TOKEN2 from the pool
            quantities[&token2] -= dist(rng) * 100;
        } else {
            // 40% chance of adding a random quantity of TOKEN3 to the pool
            quantities[&token3] += dist(rng) * 100;
        }

        // Recompute the invariant for the updated quantities
        double invariant = pool.ComputeInvariant(quantities);

        // Print the updated invariant
        std::cout << "Iteration " << i << ": Invariant = " << invariant << std::endl;
    }

    return 0;
}
