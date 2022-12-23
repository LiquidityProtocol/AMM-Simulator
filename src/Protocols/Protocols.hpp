#ifndef PROTOCOLS_HPP
#define PROTOCOLS_HPP

#include "UniswapV2Pool.hpp"
#include "UniswapV3Pool.hpp"
#include "ConstantSum.hpp"
#include "BalancerPool.hpp"
#include <QVariant>

enum PROTOCOL {
    UNISWAP_V2,
    UNISWAP_V3,
    CONSTANT_SUM,
    BALANCER
};

Q_DECLARE_METATYPE(PROTOCOL);
#endif
