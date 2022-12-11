#include "Utilities.hpp"

TokensContainer::TokensContainer(const std::unordered_set<Token *> &tokens) {
    tokens_ = std::vector<Token *>(tokens.begin(), tokens.end());
    sort(tokens_.begin(), tokens_.end(), [](Token *a, Token *b) { return a->name() < b->name(); });
}

std::vector<Token *> TokensContainer::tokens() const {
    return tokens_;
}

bool TokensContainer::operator==(const TokensContainer &other) const {
    return tokens() == other.tokens();
}