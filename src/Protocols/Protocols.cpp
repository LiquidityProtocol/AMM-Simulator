#include "Protocols.hpp"

PROTOCOL GetPoolType(PoolInterface *pool) {
    if (dynamic_cast<UniswapV2Pool *>(pool)) {
        return PROTOCOL::UNISWAP_V2;
    } else if (dynamic_cast<UniswapV3Pool *>(pool)) {
        return PROTOCOL::UNISWAP_V3;
    } else if (dynamic_cast<BalancerPool *>(pool)) {
        return PROTOCOL::BALANCER;
    } else if (dynamic_cast<CurvePool *>(pool)) {
        return PROTOCOL::CURVE;
    } else if (dynamic_cast<ConstantSum *>(pool)) {
        return PROTOCOL::CONSTANT_SUM;
    }
    throw std::invalid_argument("there is no pool type corresponding to this pool");
}
