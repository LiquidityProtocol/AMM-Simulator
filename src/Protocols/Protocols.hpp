#ifndef PROTOCOLS_HPP
#define PROTOCOLS_HPP

#include "UniswapV2Pool.hpp"
#include "UniswapV3Pool.hpp"
#include "BalancerPool.hpp"
#include "CurvePool.hpp"
#include "ConstantSum.hpp"

enum PROTOCOL {
    UNISWAP_V2 = 0,
    UNISWAP_V3 = 1,
    BALANCER = 2,
    CURVE = 3,
    CONSTANT_SUM = 4
};
PROTOCOL getPoolType(PoolInterface *pool);

#endif
