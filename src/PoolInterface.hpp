#ifndef POOL_INTERFACE_HPP
#define POOL_INTERFACE_HPP

#include <unordered_map>
#include <stdexcept>
#include "Token.hpp"
#include "PoolChunk.hpp"

class PoolInterface {
public:
    PoolInterface(Token *token1, Token *token2, double quantity1, double quantity2, double pool_fee = 0) : token1_(token1), token2_(token2) {
        quantities_ = {{token1, quantity1}, {token2, quantity2}};
        if (pool_fee < 0 || pool_fee > 1) {
            throw std::invalid_argument("invalid pool fee");
        } else {
            pool_fee_ = pool_fee;
        }
    }

    PoolChunk Swap(const PoolChunk &input) {
        if (!InPool(input.token())) {
            throw std::invalid_argument("invalid token");
        } else if (input.quantity() <= 0) {
            throw std::invalid_argument("invalid quantity");
        } else {
            return ExecuteSwap(input);
        }
    }

    bool InPool(Token *token) const {
        return token == token1_ || token == token2_;
    }

    Token * GetOtherToken(Token *token) const {
        if (!InPool(token)) {
            throw std::invalid_argument("invalid token");
        }
        return token == token1_ ? token2_ : token1_;
    }

    double GetQuantity(Token *token) const {
        if (!InPool(token)) {
            throw std::invalid_argument("invalid token");
        }
        return quantities_.find(token)->second;
    }
protected:
    Token *token1_, *token2_;
    std::unordered_map<Token *, double> quantities_;
    double pool_fee_;

    virtual PoolChunk ExecuteSwap(const PoolChunk &input) = 0;
};

#endif