#ifndef PROTOCOLS_HPP
#define PROTOCOLS_HPP

#include "UniswapV2Pool.hpp"
#include "UniswapV3Pool.hpp"
#include "BalancerPool.hpp"
#include "CurvePool.hpp"
#include "ConstantSum.hpp"

enum PROTOCOL {
    UNISWAP_V2,
    UNISWAP_V3,
    CONSTANT_SUM,
    BALANCER,
    CURVE,
};
PROTOCOL getPoolType(PoolInterface *pool);

#endif