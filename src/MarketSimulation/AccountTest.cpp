#include "Account.hpp"
#include "../Token.hpp"
#include <iostream>
#include "../UniswapV2Pool.hpp"
#include "../ConstantSum.hpp"
using namespace std;

int main(){
  Token* token1_ptr = Token::GetToken("ABC");
  token1_ptr->setPrice(1000);

  Token* token2_ptr = Token::GetToken("DEF");
  token2_ptr->setPrice(2300);

  Account acc1 = Account("alice");
  // Account acc2 = Account("alice");
  acc1.mintToken(token1_ptr, 50);
  acc1.mintToken(token2_ptr, 100);
  
  // cout << acc1.getTotalValue() << endl; 
  // cout << acc1.getTokenValue(token1_ptr) << endl;
  // cout << acc1.getTokenValue(token2_ptr) << endl;

  // UniswapV2Pool pool1({{token1_ptr, 10}, {token2_ptr, 20}});
  ConstantSum pool2({{token1_ptr, 10}, {token2_ptr, 20}});
  acc1.swap(&pool2, token1_ptr, token2_ptr, 10);
  // cout << acc1.getTokenQuantity(token2_ptr);
  assert(acc1.getTokenQuantity(token1_ptr) == 40);
  assert(acc1.getTokenQuantity(token2_ptr) - 100 == 20 - pool2.GetQuantity(token2_ptr));
  return 0;
}