#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP
#include "../Token.hpp"
#include <unordered_map>
#include <stdexcept>
#include <set>
#include "../PoolInterface.hpp"
using namespace std;

class Account{
  private:
    Account(const std::string &name){
      usd_value = 0;
      name_ = name;
    }
    static std::unordered_map<std::string, Account *> existing_acc_;

  public:
  // disallow copying
	Account & operator=(const Account &) = delete;
	Account(const Account &) = delete;

  unordered_map<Token*, double> wallet;
  double usd_value;
  static set<string> existing_acc;
  string name_;

  static Account * GetAccount(const string &name) {
		if (!existing_acc_.count(name)) {
			existing_acc_[name] = new Account(name);
		}
		return existing_acc_[name];
	}

  void mintToken(Token* token_ptr, double quantity){
    wallet[token_ptr] += quantity;
    usd_value += quantity*token_ptr->getPrice();
  }

  double getTokenQuantity(Token* token_ptr){
    if(!wallet.count(token_ptr)){
      return 0;
    }
    return wallet[token_ptr];
  }

  double getTokenValue(Token* token_ptr){
    return getTokenQuantity(token_ptr)*token_ptr->getPrice();
  }

  double getTotalValue(){
    return usd_value;
  }

  void swap(PoolInterface *pool, Token* input_token, Token* output_token, double input_quantity){
    if (input_quantity > wallet[input_token]){
      throw invalid_argument("not enough token!");
    }else{
      double output_quantity = pool->Swap(input_token, output_token, input_quantity);
      wallet[input_token] -= input_quantity;
      mintToken(output_token, output_quantity); //use mintToken since the output_token may not be in wallet
      usd_value -= input_quantity*input_token->getPrice();
      usd_value += output_quantity*output_token->getPrice();
    }
  }
  
};

unordered_map<string, Account *> Account::existing_acc_ = unordered_map<string, Account *> ();

#endif