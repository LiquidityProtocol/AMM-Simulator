#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <unordered_map>
#include <unordered_set>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <iostream>
#include <utility>

class PoolInterface;

class Token {
public:
	// disallow copying
	Token & operator=(const Token &) = delete;
	Token(const Token &) = delete;

    friend class Playground;

	std::string name() const;
	double real_value() const;
    PoolInterface * pool() const;

private:
	std::string name_;
	double real_value_;
    PoolInterface *pool_;
    
	Token(const std::string &name, double real_value);
    Token(PoolInterface *pool);
};

class Operation {
public:
    Operation(const std::string &operation_type,
              const std::string &account_name,
              PoolInterface *pool,
              std::unordered_map<Token *, double> input,
              std::unordered_map<Token *, double> output);

    std::string operation_type() const;
    std::string account_name() const;
    std::unordered_map<Token *, double> input() const;
    std::unordered_map<Token *, double> output() const;

    friend std::ostream & operator<<(std::ostream &os, const Operation &op);
private:
    std::string operation_type_;
    std::string account_name_;
    PoolInterface *pool_;
    std::unordered_map<Token *, double> input_;
    std::unordered_map<Token *, double> output_;
};

class Account {
public:
    Account & operator=(const Account &) = delete;
	Account(const Account &) = delete;

    static std::pair<Account *, bool> GetAccount(const std::string &name);

    std::string name() const;
    double total_value() const;
    std::unordered_map<Token *, double> wallet() const;
    std::vector<Operation *> ledger() const;

    double GetQuantity(Token *token) const;

    void Deposit(Token *token, double quantity);

    void Trade(Token *input_token, Token *output_token, double input_quantity);
    void Provide(Token *token1, Token *token2, double quantity1, double quantity2, double pool_fee);
    void Withdraw(Token *pool_token, double surrendered_pool_token_quantity);

    static std::vector<Account *> existing_accounts();
private:
    static std::unordered_map<std::string, Account *> existing_accounts_;
    static std::vector<Account *> existing_accounts_in_chronological_order;
    
    Account(const std::string &name);

    std::string name_;
    double total_value_;
    std::unordered_map<Token *, double> wallet_;
    std::vector<Operation *> ledger_;
};

class PoolInterface {
public:
    PoolInterface & operator=(const PoolInterface &) = delete;
	PoolInterface(const PoolInterface &) = delete;

    bool InPool(Token *token) const;
    double GetQuantity(Token *token) const;

    double pool_fee() const;

    Token * pool_token() const;
    double total_pool_token_quantity() const;

    std::unordered_set<Token *> tokens() const;

    double SpecificSimulateSwap(Token *input_token, Token *output_token, double input_quantity) const;
    Operation * SpecificSwap(Account *trader, Token *input_token, Token *output_token, double input_quantity);

    double SpecificSimulateProvision(std::unordered_map<Token *, double> input_quantities) const;
    Operation * SpecificProvide(Account *provider, std::unordered_map<Token *, double> input_quantities);

    std::unordered_map<Token *, double> SpecificSimulateWithdrawal(double surrendered_pool_token_quantity) const;
    Operation * SpecificWithdraw(Account *provider, double surrendered_pool_token_quantity);

    double GetSlippage(Token *input_token, Token *output_token, double input_quantity) const;

    std::vector<Operation *> ledger() const;
protected:
    static constexpr double FIRST_POOL_TOKEN_SUPPLY = 1;

    PoolInterface(std::unordered_set<Token *> tokens, double pool_fee);

    virtual double ComputeSwappedQuantity(Token *input_token, Token *output_token, double input_quantity) const = 0;
    virtual double ComputeInvariant(const std::unordered_map<Token *, double> &quantities) const = 0;
    virtual double ComputeSpotExchangeRate(Token *input_token, Token *output_token) const;
    virtual double ComputeSlippage(Token *input_token, Token *output_token, double input_quantity) const;
private:
    std::unordered_map<Token *, double> quantities_;
    double pool_fee_;
    Token *pool_token_;
    std::vector<Operation *> ledger_;

    bool CheckWallet(Account *account, const std::unordered_map<Token *, double> &quantities) const;

    void ExecuteSwap(Account *trader, Token *input_token, Token *output_token, double input_quantity, double output_quantity);

    bool ValidProvision(std::unordered_map<Token *, double> quantities) const;

    void ExecuteProvision(Account *provider, std::unordered_map<Token *, double> input_quantities, double generated_pool_token_quantity);

    void ExecuteWithdrawal(Account *provider, double surrendered_pool_token_quantity, std::unordered_map<Token *, double> output_quantities);
};

class TokensContainer {
public:
    TokensContainer(const std::unordered_set<Token *> &tokens);

    std::vector<Token *> tokens() const;

    bool operator==(const TokensContainer &other) const;
private:
    std::vector<Token *> tokens_;
};

namespace std {
    template<>
    struct hash<TokensContainer> {
        size_t operator()(const TokensContainer &a) const {
            string temp = "";
            for (auto token : a.tokens()) {
                temp += " " + token->name();
            }
            return hash<string>()(temp);
        }
    };
}

#endif // UTILITIES_HPP
