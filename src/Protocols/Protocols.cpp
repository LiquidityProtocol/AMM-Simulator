#include "Protocols.hpp"

using namespace std;

Protocol getPoolType(PoolInterface *pool) {
    if (dynamic_cast<UniswapV2Pool*>(pool)) {
        return UNISWAPV2;
    } else if (dynamic_cast<UniswapV3Pool*>(pool)) {
        return UNISWAPV3;
    } else if (dynamic_cast<BalancerPool*>(pool)) {
        return BALANCER;
    } else if (dynamic_cast<CurvePool*>(pool)) {
        return CURVE;
    } else {
        return CONSTANTSUM;
    }
}