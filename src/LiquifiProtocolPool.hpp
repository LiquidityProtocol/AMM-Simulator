#include <unordered_map>
#include <stdexcept>
#include <chrono>
#include "Token.hpp"
#include "PoolChunk.hpp"

class LiquifiProtocolPool {
public:
    LiquifiProtocolPool(Token *token1, Token *token2, double quantity1 = 0, double quantity2 = 0, double pool_fee = 0) : token1(token1), token2(token2), pool_fee(pool_fee) {
        token_to_quantity[token1] = quantity1;
        token_to_quantity[token2] = quantity2;
    }

    PoolChunk standard_immediate_swap(PoolChunk input) {
        if (input.get_token() != token1 && input.get_token() != token2) {
            throw std::invalid_argument("invalid token");
        } else if (input.get_quantity() <= 0) {
            throw std::invalid_argument("invalid quantity");
        } else {
            return execute_standard_immediate_swap(input);
        }
    }
private:
    Token *token1, *token2;
    std::unordered_map<Token *, double> token_to_quantity;
    double pool_fee;

    // class TimeLockedSwapOrder {
    // public:
    //     TimeLockedSwapOrder(PoolChunk input, std::chrono::seconds timeout, double stop_loss_price_limit) : input(input), timeout(timeout), initiation_time(std::chrono::system_clock::now()), expiration_time(initiation_time + timeout), stop_loss_price_limit(stop_loss_price_limit) {
            
    //     }
    // private:
    //     PoolChunk input;
    //     std::chrono::seconds timeout;
    //     std::chrono::time_point<std::chrono::system_clock> initiation_time, expiration_time;
    //     double stop_loss_price_limit;
    //     std::vector<PoolChunk> temporary_balance;
    // };

    PoolChunk execute_standard_immediate_swap(PoolChunk input) {
        Token *input_token = input.get_token();
        Token *output_token = get_other_token(input_token);
        PoolChunk output(output_token, token_to_quantity[output_token] - token_to_quantity[input_token] * token_to_quantity[output_token] / (token_to_quantity[input_token] + (1 - pool_fee) * input.get_quantity()));
        token_to_quantity[input_token] += input.get_quantity();
        token_to_quantity[output_token] -= output.get_quantity();
        return output;
    }

    Token * get_other_token(Token *token) const {
        return token == token1 ? token2 : token1;
    }
};