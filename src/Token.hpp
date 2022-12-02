#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>
#include <unordered_map>

class Token {
public:
	// disallow copying
	Token & operator=(const Token &) = delete;
	Token(const Token &) = delete;

	static Token * GetToken(const std::string &name) {
		if (!existing_tokens_.count(name)) {
			existing_tokens_[name] = new Token(name);
		}
		return existing_tokens_[name];
	}

	std::string name() const {
		return name_;
	}

	double real_value() const {
		return real_value_;
	}

	void set_real_value(double real_value) {
		real_value_ = real_value;
	}
private:
	Token(const std::string &name) : name_(name), real_value_(0) {}

	static std::unordered_map<std::string, Token *> existing_tokens_;
	std::string name_;
	double real_value_;
};

std::unordered_map<std::string, Token *> Token::existing_tokens_ = std::unordered_map<std::string, Token *>();

#endif