#ifndef Market_hpp
#define Market_hpp

#include "CommunityActor.hpp"

class Market {
public:
    Market();
    ~Market();

    // the add functions is not used in market simulating process
    // instead is used to create Rug Pull Strategy of Arbitrager
    void addToken(const std::string &name, double price);
    void addToken(Token *token);
    void addPool(PoolInterface *pool);
    void addAccount(Account *account);

    virtual void runEpoch();

    std::unordered_set<Token *> GetMarketTokens() const;
    std::unordered_set<PoolInterface *> GetMarketPools() const;
    std::unordered_set<Account *> GetMarketAccounts() const;
    Token* getToken(std::string name);
private:
    static int MarketCount;
    int MarketIndex;
    int epoch;

    std::unordered_set<Token *> tokens_;
    std::unordered_set<PoolInterface *> pools_;
    std::unordered_set<Account *> accounts_;

    CommunityActor *A;
};

#endif
