#ifndef CONSTANTSUM_HPP
#define CONSTANTSUM_HPP

#include <stdexcept>
#include "../Utilities/Utilities.hpp"

class ConstantSum : public PoolInterface {
    /*Implementation of modified constant sum protocol:
    Description of Protocol: px+y=k; p is price when pool is initialised, x and y tokens respectively
    */
public:
    using PoolInterface::PoolInterface;
private:
    double GetT1inT2Price(Token *token1, Token *token2 ) const {
        return (quantities_.find(token2)->second)/(quantities_.find(token1)->second);
    }

    double ExecuteSwap(Token *input_token, Token *output_token, double input_quantity) {

        double output_quantity = GetT1inT2Price(input_token, output_token)*input_quantity;
        if (quantities_[output_token] < output_quantity) {
            throw std::invalid_argument("Too few tokens in pool for swap");
        }
        quantities_[input_token] += input_quantity;
        quantities_[output_token] -= output_quantity;
        return output_quantity;
    }
};

#endif // CONSTANTSUM_HPP
