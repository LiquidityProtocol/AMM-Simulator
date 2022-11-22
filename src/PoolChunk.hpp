#ifndef POOL_CHUNK_HPP
#define POOL_CHUNK_HPP

#include "Token.hpp"

class PoolChunk {
public:
    PoolChunk(Token *token, double quantity) : token_(token), quantity_(quantity) {}

    Token * token() const {
        return token_;
    }

    double quantity() const {
        return quantity_;
    }

    void update_quantity(double change) {
        quantity_ += change;
    }
private:
    Token *token_;
    double quantity_;
};

#endif