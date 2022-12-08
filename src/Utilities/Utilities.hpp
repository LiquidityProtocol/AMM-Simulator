#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <unordered_map>
#include <unordered_set>
#include <string>
#include <stdexcept>
#include <algorithm>

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
	Token(const std::string &name) : name_(name), real_value_(0) {}

	static std::unordered_map<std::string, Token *> existing_tokens_;
	std::string name_;
	double real_value_;
};

class PoolInterface;

class Account {
public:
    Account & operator=(const Account &) = delete;
	Account(const Account &) = delete;

    static Account * GetAccount(const std::string &name);

    std::string name() const;

    double total_value() const;

    double GetQuantity(Token *token) const;

    double GetValue(Token *token) const;

    void Deposit(Token *token, double quantity);

    double Trade(PoolInterface *pool, Token *input_token, Token *output_token, double input_quantity);

    double Provide(PoolInterface *pool, std::unordered_map<Token *, double> provided_quantities);

    std::unordered_map<Token *, double> Withdraw(PoolInterface *pool, double surrendered_quantity);
private:
    Account(const std::string &name) : name_(name), total_value_(0), wallet_() {}

    static std::unordered_map<std::string, Account *> existing_accounts_;
    std::string name_;
    double total_value_;
    std::unordered_map<Token *, double> wallet_;
};

class PoolInterface {
public:
    PoolInterface(std::unordered_map<Token *, double> quantities, double pool_fee = 0);
    virtual ~PoolInterface();
    bool InPool(Token *token) const;
    double GetQuantity(Token *token) const;

    double pool_fee() const;

    Token * pool_token() const;
    double total_pool_token_quantity() const;

    std::unordered_set<Token *> tokens() const;

    double SimulateSwap(Token *input_token, Token *output_token, double input_quantity) const;
    double Swap(Account *trader, Token *input_token, Token *output_token, double input_quantity);

    double SimulateProvision(std::unordered_map<Token *, double> input_quantities) const;
    double Provide(Account *provider, std::unordered_map<Token *, double> input_quantities);

    std::unordered_map<Token *, double> SimulateWithdrawal(double surrendered_pool_token_quantity) const;
    std::unordered_map<Token *, double> Withdraw(Account *provider, double surrendered_pool_token_quantity);

    double GetSlippage(Token *input_token, Token *output_token, double input_quantity) const;

    virtual double ComputeSwappedQuantity(Token *input_token, Token *output_token, double input_quantity) const = 0;
    virtual double ComputeInvariant(const std::unordered_map<Token *, double> &quantities) const = 0;
    virtual double ComputeSpotExchangeRate(Token *input_token, Token *output_token) const;
    virtual double ComputeSlippage(Token *input_token, Token *output_token, double input_quantity) const;


    std::unordered_map<Token *, double> quantities_;
    double pool_fee_;
    Token *pool_token_;

    bool CheckWallet(Account *account, const std::unordered_map<Token *, double> &quantities) const;

    void ExecuteSwap(Account *trader, Token *input_token, Token *output_token, double input_quantity, double output_quantity);

    bool ValidProvision(std::unordered_map<Token *, double> quantities) const;

    void ExecuteProvision(Account *provider, std::unordered_map<Token *, double> input_quantities, double generated_pool_token_quantity);

    void ExecuteWithdrawal(Account *provider, double surrendered_pool_token_quantity, std::unordered_map<Token *, double> output_quantities);
};

#endif