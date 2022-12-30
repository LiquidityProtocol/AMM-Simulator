#include <iostream>
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

    // Test the GetSlope function
    std::cout << "Slope of TOKEN1: " << pool.GetSlope(&token1) << std::endl;
    std::cout << "Slope of TOKEN2: " << pool.GetSlope(&token2) << std::endl;
    std::cout << "Slope of TOKEN3: " << pool.GetSlope(&token3) << std::endl;

    // Test the ComputeInvariant function
    std::cout << "Invariant: " << pool.ComputeInvariant(quantities) << std::endl;

    // Test the ComputeSpotExchangeRate function
    std::cout << "Exchange rate TOKEN1 -> TOKEN2: " << pool.ComputeSpotExchangeRate(&token1, &token2) << std::endl;
    std::cout << "Exchange rate TOKEN2 -> TOKEN3: " << pool.ComputeSpotExchangeRate(&token2, &token3) << std::endl;

    // Test the ComputeSwappedQuantity function
    std::cout << "Quantity of TOKEN2 for 10 TOKEN1: " << pool.ComputeSwappedQuantity(&token1, &token2, 10) << std::endl;
    std::cout << "Quantity of TOKEN3 for 20 TOKEN2: " << pool.ComputeSwappedQuantity(&token2, &token3, 20) << std::endl;

    // Test the ComputeSlippage function
    std::cout << "Slippage for 10 TOKEN1 -> TOKEN2: " << pool.ComputeSlippage(&token1, &token2, 10) << std::endl;
    std::cout << "Slippage for 20 TOKEN2 -> TOKEN3: " << pool.ComputeSlippage(&token2, &token3, 20) << std::endl;

    return 0;
}
