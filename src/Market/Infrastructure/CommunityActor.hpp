#ifndef CommunityActor_hpp
#define CommunityActor_hpp

#include "../../Utilities/Utilities.hpp"

// I dont override function of Account because no specific account can act as a Community Actor

class CommunityActor : public Account {
public:
    friend class Market;
    friend class SignalsHandler;
    
    template<typename T> T wallet() const;
    template<typename T> T total_value() const;
    template<typename T> T ledger() const;
    template<typename T> T GetQuantity() const;
private:
    CommunityActor(int MarketCount);

    void refill(Token *token, double amount);
    void Trade(PoolInterface *pool, Token *input_token, Token *output_token, double input_quantity);
    void Provide(PoolInterface *pool, double nPoolTokens);
    void Withdraw(PoolInterface *pool, double nPoolTokens);
};

#endif
