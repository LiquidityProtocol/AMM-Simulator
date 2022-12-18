#include "Playground.hpp"

std::pair<Token *, bool> Playground::GetToken(const std::string &name, double real_value) {
    if (existing_tokens_.count(name)) {
        return {existing_tokens_[name], false};
    } else {
        return {existing_tokens_[name] = new Token(name, real_value), true};
    }
}

std::unordered_set<Token *> Playground::existing_tokens() const {
    std::unordered_set<Token *> tokens; tokens.reserve(existing_tokens_.size());
    for (const auto &[name, token] : existing_tokens_) {
        tokens.emplace(token);
    }
    return tokens;
}
