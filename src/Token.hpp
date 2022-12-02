#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>
#include <unordered_map>

class Token {
public:
	// disallow copying
	Token & operator=(const Token &) = delete;
	Token(const Token &) = delete;

	static Token * GetToken(const std::string &name);

	std::string name() const;

	double real_value() const;
	void set_real_value(double real_value);
private:
	Token(const std::string &name);

	static std::unordered_map<std::string, Token *> existing_tokens_;
	std::string name_;
	double real_value_;
};

#endif