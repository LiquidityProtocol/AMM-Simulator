#ifndef PROTOCOLS_HPP
#define PROTOCOLS_HPP

#include "UniswapV2Pool.hpp"
#include "UniswapV3Pool.hpp"
#include "ConstantSum.hpp"
#include "BalancerPool.hpp"
#include "CurvePool.hpp"
#include <QVariant>

enum PROTOCOL {
    UNISWAP_V2,
    UNISWAP_V3,
    CONSTANT_SUM,
    BALANCER,
    CURVE
};

static const std::unordered_map<PROTOCOL, std::string> PROTOCOL_NAME({
        {PROTOCOL::UNISWAP_V2, "UNISWAP V2"},
        {PROTOCOL::UNISWAP_V3, "UNISWAP V3"},
        {PROTOCOL::CONSTANT_SUM, "CONSTANT SUM"},
        {PROTOCOL::BALANCER, "BALANCER"},
        {PROTOCOL::CURVE, "CURVE"}
});

PROTOCOL GetPoolType(PoolInterface *pool);

Q_DECLARE_METATYPE(PROTOCOL);

#endif // PROTOCOLS_HPP
