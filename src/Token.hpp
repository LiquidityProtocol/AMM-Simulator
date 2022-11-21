#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>
#include <unordered_map>

class Token {
private:
	Token(const std::string &name) : name_(name) {}

	static std::unordered_map<std::string, Token *> existing_tokens_;
	std::string name_;
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
};

std::unordered_map<std::string, Token *> Token::existing_tokens_ = std::unordered_map<std::string, Token *>();

#endif