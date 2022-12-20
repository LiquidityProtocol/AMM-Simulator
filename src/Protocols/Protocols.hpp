#ifndef PROTOCOLS_HPP
#define PROTOCOLS_HPP

#include "UniswapV2Pool.hpp"
#include "UniswapV3Pool.hpp"
#include "BalancerPool.hpp"
#include "CurvePool.hpp"
#include "ConstantSum.hpp"

enum Protocol {
    UNISWAPV2 = 0,
    UNISWAPV3 = 1,
    BALANCER = 2,
    CURVE = 3,
    CONSTANTSUM = 4
};
Protocol getPoolType(PoolInterface *pool);

#endif