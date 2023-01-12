#include <cassert>
#include "../Playground.hpp"

int main() {
  Playground playground;

  Token *token1 = playground.GetToken("token1", 10).first;
  Token *token2 = playground.GetToken("token2", 20).first;
  Token *token3 = playground.GetToken("Token3", 10).first;

  Account *alice = playground.GetAccount("Alice").first;
  alice->Deposit(token1, 1000);
  alice->Deposit(token2, 1000);

  playground.ExecuteInitialProvision(alice, PROTOCOL::BALANCER, {{token1, 100}, {token2, 100}}, 0, {{token1, 10}, {token2, 20}});
  PoolInterface *pool = playground.GetPool(PROTOCOL::BALANCER, {token1, token2});
  assert(pool->total_pool_token_quantity() == 1);

  // check for correct quantities of tokens (Token 1 and 2 in pool, Token 3 not in pool)
  assert(alice->GetQuantity(token1) == 100);
  assert(alice->GetQuantity(token2) == 100);
  assert(!playground.Existing(PROTOCOL::BALANCER, {token3}));

   //checking that we get an exception when getting the quantity of Token 3)
  try {
    alice->GetQuantity(token3);
    assert(false);
  } catch (std::invalid_argument &e) {
    // expected exception
  }

  // checking that we get an exception when executing a swap with an invalid token
  try {
    playground.ExecuteSwap(alice, pool, token1, token3, 20);
    assert(false);
  } catch (std::invalid_argument &e) {
    // expected exception
  }

  // executing swaps between token 1 and token 2
  assert(playground.ExecuteSwap(alice, pool, token1, token2, 20) == 20);
  assert(pool->GetQuantity(token1) == 120);
  assert(pool->GetQuantity(token2) == 80);

  assert(playground.ExecuteSwap(alice, pool, token2, token1, 110) == 110);
  assert(pool->GetQuantity(token1) == 10);
  assert(pool->GetQuantity(token2) == 190);

  try {
      playground.ExecuteSwap(alice, pool, token2, token1, 20);
      assert(false);
  } catch (std::invalid_argument &e) {
      assert(std::string(e.what()) == "not enough liquidity");
  }

  std::cout << "Success!\n";

  return 0;
}
