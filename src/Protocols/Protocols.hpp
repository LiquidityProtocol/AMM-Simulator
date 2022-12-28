#ifndef PROTOCOLS_HPP
#define PROTOCOLS_HPP

#include "UniswapV2Pool.hpp"
#include "UniswapV3Pool.hpp"
#include "ConstantSum.hpp"
#include "BalancerPool.hpp"
#include "CurvePool.hpp"

enum PROTOCOL {
    UNISWAP_V2,
    UNISWAP_V3,
    CONSTANT_SUM,
    BALANCER,
    CURVE
};

PROTOCOL GetPoolType(PoolInterface *pool);

#endif // PROTOCOLS_HPP
