#include <cassert>
#include "../Playground.hpp"

int main () {
    Playground playground;

    Token *token1 = playground.GetToken("token1", 10).first;
    Token *token2 = playground.GetToken("token2", 20).first;
    assert(playground.existing_tokens() == std::unordered_set<Token *>({token1, token2}));

    Account *acc1 = playground.GetAccount("acc1").first;
    acc1->Deposit(token1, 1000);
    acc1->Deposit(token2, 2000);
    playground.ExecuteInitialProvision(acc1, PROTOCOL::UNISWAP_V2, {{token1, 10}, {token2, 20}}, 0);
    PoolInterface *pool = playground.GetPool(PROTOCOL::UNISWAP_V2, {token1, token2});
    playground.ExecuteSwap(acc1, pool, token1, token2, 10);
    

    std::cout << pool->GetQuantity(pool->pool_token());
    std::unordered_map<Token*, double> output = playground.ExecuteWithdrawal(acc1, pool->pool_token(), 1); 
    
    for (auto op: acc1->ledger()){
        std::cout << *op;
    }
    for (auto data: acc1->wallet()){
        std::cout << data.first->name() << ": " << data.second << "\n";
    }
    return 0;
}
