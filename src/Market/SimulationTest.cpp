#include "Simulation.hpp"
#include "../Playground.hpp"

int main(){
  Playground *playground = new Playground;
  Token *token1 = playground->GetToken("token1", 10).first;
  Token *token2 = playground->GetToken("token2", 20).first;
  assert(playground->existing_tokens() == std::unordered_set<Token *>({token1, token2}));

  Account *alice = playground->GetAccount("Alice").first;
  alice->Deposit(token1, 100);
  alice->Deposit(token2, 100);

  playground->ExecuteInitialProvision(alice, PROTOCOL::UNISWAP_V2, {{token1, 20}, {token2, 40}}, 0.01);
  PoolInterface *pool = playground->GetPool(PROTOCOL::UNISWAP_V2, {token1, token2});
  assert(pool->total_pool_token_quantity() == 1);
  std::pair<PROTOCOL, std::unordered_set<Token*> > pool_info = {PROTOCOL::UNISWAP_V2, {token1, token2}};
  Simulation simulation( playground, pool_info);
  simulation.runEpoch();
}