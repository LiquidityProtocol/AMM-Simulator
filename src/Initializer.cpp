#include "Utilities.hpp"

std::unordered_map<std::string, Token *> Token::existing_tokens_ = std::unordered_map<std::string, Token *>();
std::unordered_map<std::string, Account *> Account::existing_accounts_ = std::unordered_map<std::string, Account *>();