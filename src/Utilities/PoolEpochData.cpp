#include "Utilities.hpp"

PoolEpochData::PoolEpochData(PoolInterface *pool) : pool_(pool) {}

double PoolEpochData::GetOpenPrice(Token *a, Token *b) const {
    if (!pool_->InPool(a) || !pool_->InPool(b))
        throw std::invalid_argument("Pool doesn't support this pair");

    return (open.find(a)->second).find(b)->second;
}
double PoolEpochData::GetHighPrice(Token *a, Token *b) const {
    if (!pool_->InPool(a) || !pool_->InPool(b))
        throw std::invalid_argument("Pool doesn't support this pair");

    return (high.find(a)->second).find(b)->second;
}
double PoolEpochData::GetLowPrice(Token *a, Token *b) const {
    if (!pool_->InPool(a) || !pool_->InPool(b))
        throw std::invalid_argument("Pool doesn't support this pair");

    return (low.find(a)->second).find(b)->second;
}
double PoolEpochData::GetClosePrice(Token *a, Token *b) const {
    if (!pool_->InPool(a) || !pool_->InPool(b))
        throw std::invalid_argument("Pool doesn't support this pair");

    return (close.find(a)->second).find(b)->second;
}

double PoolEpochData::GetMarketPrice(Token *a) const {
    return (market_price.find(a)->second);
}
double PoolEpochData::GetSpotPrice(Token *a, Token *b) const {
    return GetClosePrice(a, b);
}
double PoolEpochData::GetQuanitty(Token *a) const {
    return quantities.find(a)->second;
}
double PoolEpochData::GetVolume(Token *a) const {
    return GetMarketPrice(a) * GetQuanitty(a);
}

PoolInterface *PoolEpochData::pool() const {
    return pool_;
}

int PoolEpochData::epochIndex() const {
    return nEpoch;
}

