#ifndef PLAYGROUND_HPP
#define PLAYGROUND_HPP

#include "Utilities/Utilities.hpp"

class Playground {
public:
    std::pair<Token *, bool> GetToken(const std::string &name, double real_value = 0);
    std::unordered_set<Token *> existing_tokens() const;

private:
    std::unordered_map<std::string, Token *> existing_tokens_;
};

#endif // PLAYGROUND_HPP
