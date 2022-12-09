#include "Utilities.hpp"

Token * Token::GetToken(const std::string &name) {
    /*
        * Returns a pointer to the token with the given name.
        *
        * @param name: Name of the token.
        * 
        * @return: Pointer to the token.
    */
    if (!existing_tokens_.count(name)) {
        existing_tokens_[name] = new Token(name);
        existing_tokens_in_chronological_order.emplace_back(existing_tokens_[name]);
    }
    return existing_tokens_[name];
}

std::string Token::name() const {
    /*
        * Getter for the name.
        *
        * @param: None.
        * 
        * @return: Name.
    */
    return name_;
}

double Token::real_value() const {
    /*
        * Getter for the real value.
        *
        * @param: None.
        * 
        * @return: Real value.
    */
    return real_value_;
}

void Token::set_real_value(double real_value) {
    /*
        * Setter for the real value.
        *
        * @param real_value: Real value.
        * 
        * @return: None.
    */
    real_value_ = real_value;
}

std::vector<Token *> Token::existing_tokens() {
    return existing_tokens_in_chronological_order;
}
