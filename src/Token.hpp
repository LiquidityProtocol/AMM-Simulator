#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>
#include <unordered_map>

class Token {
private:
	Token(const std::string &name) : name_(name) {}
	double usd_price;
	static std::unordered_map<std::string, Token *> existing_tokens_;
	std::string name_;
public:
	// disallow copying
	Token & operator=(const Token &) = delete;
	Token(const Token &) = delete;
	void setPrice(double price){
		usd_price = price;
	}
	double getPrice(){
		return usd_price;
	}
	static Token * GetToken(const std::string &name, double price = 0) {
		if (!existing_tokens_.count(name)) {
			existing_tokens_[name] = new Token(name);
			existing_tokens_[name]->setPrice(price);
		}
		return existing_tokens_[name];
	}

	std::string name() const {
		return name_;
	}
};

std::unordered_map<std::string, Token *> Token::existing_tokens_ = std::unordered_map<std::string, Token *>();

#endif