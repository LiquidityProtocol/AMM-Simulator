#include <vector>
#include <stdexcept>
#include "PoolChunk.hpp"

class LiquifiProtocolPool {
public:
    LiquifiProtocolPool(std::vector<PoolChunk> pool_chunks, double pool_fee) : pool_chunks(pool_chunks), pool_fee(pool_fee) {}

    PoolChunk standard_immediate_swap(PoolChunk input) {
        if (input.get_token() != pool_chunks[0].get_token() && input.get_token() != pool_chunks[1].get_token()) {
            throw std::invalid_argument("invalid token");
        } else if (input.get_quantity() <= 0) {
            throw std::invalid_argument("invalid quantity");
        } else {
            return execute_standard_immediate_swap(input);
        }
    }
private:
    std::vector<PoolChunk> pool_chunks;
    double pool_fee;

    PoolChunk execute_standard_immediate_swap(PoolChunk input) {
        size_t input_index = input.get_token() == pool_chunks[0].get_token() ? 0 : 1;
        size_t output_index = input_index ^ 1;
        PoolChunk output(pool_chunks[output_index].get_token(), pool_chunks[output_index].get_quantity() - pool_chunks[input_index].get_quantity() * pool_chunks[output_index].get_quantity() / (pool_chunks[input_index].get_quantity() + (1 - pool_fee) * input.get_quantity()));
        pool_chunks[input_index].update_quantity(input.get_quantity());
        pool_chunks[output_index].update_quantity(-output.get_quantity());
        return output;
    }
};