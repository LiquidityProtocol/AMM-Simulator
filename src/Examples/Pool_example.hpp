#ifndef POOL_HPP
#define POOL_HPP

#include <unordered_map>
#include <unordered_set>

#include "../Protocol/includeMe.hpp"
#include "../Token.hpp"

using namespace std;

template<typename protocolType>
class Pool  {
protected:
    std::unordered_map<Token *, double> quantities_;
    double pool_fee_;

    virtual double ExecuteSwap(Token *input_token, Token *output_token, double input_quantity) = 0;
public:
    Pool<protocolType>(const std::unordered_map<Token *, double> &quantities, double pool_fee = 0) : quantities_(quantities) {
        if (pool_fee < 0 || pool_fee > 1) {
            throw std::invalid_argument("invalid pool fee");
        } else {
            pool_fee_ = pool_fee;
        }
    }
    double Swap(Token *input_token, Token *output_token, double input_quantity) {
        if (!InPool(input_token) || !InPool(output_token)) {
            throw std::invalid_argument("invalid token");
        } else if (input_quantity <= 0) {
            throw std::invalid_argument("invalid quantity");
        } else {
            return ExecuteSwap(input_token, output_token, input_quantity);
        }
    }

    bool InPool(Token *token) const {
        return quantities_.count(token);
    }

    double GetQuantity(Token *token) const {
        if (!InPool(token)) {
            throw std::invalid_argument("invalid token");
        }
        return quantities_.find(token)->second;
    }

    std::unordered_set<Token *> tokens() const {
        std::unordered_set<Token *> tokens;
        tokens.reserve(quantities_.size());
        for (auto [token, quantity] : quantities_) {
            tokens.emplace(token);
        }
        return tokens;
    }
};
#endif