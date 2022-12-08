#ifndef CONSTANT_SUM_HPP
#define CONSTANT_SUM_HPP

#include <stdexcept>
#include "PoolInterface.hpp"

class ConstantSum : public PoolInterface {
public:
    using PoolInterface::PoolInterface;
private:
    double ExecuteSwap(Token *input_token, Token *output_token, double input_quantity) {
        if (input_quantity > quantities_[output_token]) {
            throw std::invalid_argument("provided too many " + input_token->name() + "s");
        }
        double output_quantity = input_quantity;
        quantities_[input_token] += input_quantity;
        quantities_[output_token] -= output_quantity;
        return output_quantity;
    }

    double SimulateSwap(Token *input_token, Token *output_token, double input_quantity) {
        if (input_quantity > quantities_[output_token]) {
            throw std::invalid_argument("provided too many " + input_token->name() + "s");
        }
        return input_quantity;
    }
};

#endif // CONSTANT_SUM_HPP