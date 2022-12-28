#include "Protocols.hpp"

using namespace std;

PROTOCOL getPoolType(PoolInterface *pool) {
    if (dynamic_cast<UniswapV2Pool*>(pool)) {
        return UNISWAP_V2;
    } else if (dynamic_cast<UniswapV3Pool*>(pool)) {
        return UNISWAP_V3;
    } else if (dynamic_cast<BalancerPool*>(pool)) {
        return BALANCER;
    } else if (dynamic_cast<CurvePool*>(pool)) {
        return CURVE;
    } else {
        return CONSTANT_SUM;
    }
}