#include "Utilities.hpp"

std::pair<Token *, bool> Token::GetToken(const std::string &name, double real_value) {
    if (existing_tokens_.count(name)) {
        return {existing_tokens_[name], false};
    } else {
        existing_tokens_in_chronological_order.emplace_back(new Token(name, real_value));
        return {existing_tokens_[name] = existing_tokens_in_chronological_order.back(), true};
    }
}

Token * Token::GetPoolToken(PoolInterface *pool) {
    std::string name = "PoolToken" + std::to_string(reinterpret_cast<uint64_t>(pool));
    return new Token(name, 0, pool);
}

std::vector<Token *> Token::existing_tokens() {
    return existing_tokens_in_chronological_order;
}

std::string Token::name() const {
    return name_;
}

double Token::real_value() const {
    return real_value_;
}

PoolInterface * Token::pool() const {
    return pool_;
}

Token::Token(const std::string &name, double real_value, PoolInterface *pool)
    : name_(name)
    , real_value_(real_value)
    , pool_(pool) {}
