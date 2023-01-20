#include "Utilities.hpp"

std::string Token::name() const {
    return pool_ ? "Pool Token - " + pool_->name() : name_;
}

double Token::real_value() const {
    return pool_ ? pool_->GetPoolValue() / pool_->total_pool_token_quantity() : real_value_;
}

PoolInterface * Token::pool() const {
    return pool_;
}

Token::Token(const std::string &name, double real_value)
    : name_(name)
    , real_value_(real_value)
    , pool_(nullptr) {}

Token::Token(PoolInterface *pool)
    : name_("PoolToken" + std::to_string(reinterpret_cast<uint64_t>(pool)))
    , real_value_(0)
    , pool_(pool) {}
