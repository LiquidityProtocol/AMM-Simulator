#ifndef PLAYGROUND_HPP
#define PLAYGROUND_HPP

#include "Utilities/Utilities.hpp"
#include "Protocols/Protocols.hpp"

class Playground {
public:
    std::pair<Token *, bool> GetToken(const std::string &name, double real_value = 0);
    std::unordered_set<Token *> existing_tokens() const;

    std::pair<Account *, bool> GetAccount(const std::string &name);
    std::unordered_set<Account *> existing_accounts() const;

    std::unordered_set<PoolInterface *> existing_pools() const;

    bool Existing(PROTOCOL protocol, const std::unordered_set<Token *> &tokens) const;
    PoolInterface * GetPool(PROTOCOL protocol, const std::unordered_set<Token *> &tokens) const;

    std::unordered_set<PoolInterface *> GetPools(PROTOCOL protocol, Token *input_token, Token *output_token) const;
    double SimulateSwap(PoolInterface *pool, Token *input_token, Token *output_token, double input_quantity) const;
    double ExecuteSwap(Account *trader, PoolInterface *pool, Token *input_token, Token *output_token, double input_quantity) const;

    double SimulateProvision(PROTOCOL protocol, const std::unordered_map<Token *, double> &provided_quantities) const;
    double ExecuteProvision(Account *provider, PROTOCOL protocol, const std::unordered_map<Token *, double> &provided_quantities) const;
    double ExecuteInitialProvision(Account *provider, PROTOCOL protocol, const std::unordered_map<Token *, double> &provided_quantities, double pool_fee);
    double ExecuteInitialProvision(Account *provider, PROTOCOL protocol, const std::unordered_map<Token *, double> &provided_quantities, double pool_fee, double slippage_controller);
    double ExecuteInitialProvision(Account *provider, PROTOCOL protocol, const std::unordered_map<Token *, double> &provided_quantities, double pool_fee, const std::unordered_map<Token *, double> &weights);

    std::unordered_map<Token *, double> SimulateWithdrawal(Token *token, double surrendered_quantity) const;
    std::unordered_map<Token *, double> ExecuteWithdrawal(Account *provider, Token *token, double surrendered_quantity);

    void Simulate(PROTOCOL protocol, PoolInterface *pool, double market_price);
    void ProvisionSimulation(PoolInterface *pool, Token *firstToken, Token *secondToken);
    void TradeSimulation(PoolInterface *pool, Token *firstToken, Token *secondToken);
    void ArbSimulation(PoolInterface *pool, Token *firstToken, Token *secondToken);

    double LastActionsAverage(std::string action);
    double provision_type();

    void SupplyPool(double provision_value,Token *firstToken, Token *secondToken, PoolInterface *pool, Account *provider );

    double ArbAmount(PoolInterface *pool, Token *firstToken, Token *secondToken);

private:
    std::unordered_map<std::string, Token *> existing_tokens_;
    std::unordered_map<std::string, Account *> existing_accounts_;
    std::unordered_map<PROTOCOL, std::unordered_map<TokensContainer, PoolInterface *>> existing_pools_;
    std::vector<std::pair<std::string, double>>  state_evolution;
    double market_price;

};

#endif // PLAYGROUND_HPP
