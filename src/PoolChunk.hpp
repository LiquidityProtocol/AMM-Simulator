#include "Token.hpp"

class PoolChunk {
public:
    PoolChunk(Token *token, double quantity) : token(token), quantity(quantity) {}

    Token * get_token() const {
        return token;
    }

    double get_quantity() const {
        return quantity;
    }

    void update_quantity(double change) {
        quantity += change;
    }
private:
    Token *token;
    double quantity;
};