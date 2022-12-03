#include "Token.hpp"

Token * Token::GetToken(const std::string &name) {
    if (!existing_tokens_.count(name)) {
        existing_tokens_[name] = new Token(name);
    }
    return existing_tokens_[name];
}
std::string Token::name() const {
    return name_;
}

double Token::real_value() const    {
    return real_value_;
}
void Token::set_real_value(double real_value)   {
    real_value_ = real_value;
}
std::unordered_map<std::string, Token *> Token::existing_tokens_ = std::unordered_map<std::string, Token *>();