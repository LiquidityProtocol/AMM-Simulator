#include "Protocols.hpp"

PROTOCOL GetPoolType(const PoolInterface *pool) {
    if (typeid(*pool) == typeid(UniswapV2Pool)) {
        return PROTOCOL::UNISWAP_V2;
    } else if (typeid(*pool) == typeid(UniswapV3Pool)) {
        return PROTOCOL::UNISWAP_V3;
    } else if (typeid(*pool) == typeid(BalancerPool)) {
        return PROTOCOL::BALANCER;
    } else if (typeid(*pool) == typeid(CurvePool)) {
        return PROTOCOL::CURVE;
    } else if (typeid(*pool) == typeid(ConstantSum)) {
        return PROTOCOL::CONSTANT_SUM;
    }
    throw std::invalid_argument("there is no pool type corresponding to this pool");
}
