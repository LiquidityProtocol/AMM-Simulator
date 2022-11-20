#include <string>

class Token {
public:
	Token(std::string name) : name(name) {}

	std::string get_name() const {
		return name;
	}

	bool operator==(const Token &other) const {
		return name == other.name;
	}

	bool operator!=(const Token &other) const {
		return !(*this == other);
	}
private:
	std::string name;
};

namespace std {
	template<>
	struct hash<Token> {
		size_t operator()(const Token &token) const {
			return hash<string>()(token.get_name());
		}
	};
}