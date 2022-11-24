#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP
#include "../Token.hpp"
#include <unordered_map>
#include <stdexcept>
#include <set>
#include "../PoolInterface.hpp"
using namespace std;

class Account{
  public:
  Account(const string &name){
    if (!existing_acc.count(name)){
      existing_acc.insert(name);
      name_ = name;
      wallet = unordered_map<Token*, double>();
    }else{
      throw invalid_argument("Account exist");
    }
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
    if(!wallet.count(input_token)){
      throw invalid_argument("token not in wallet!");
    }else if (input_quantity > wallet[input_token]){
      throw invalid_argument("not enough token!");
    }else{
      double output_quantity = pool->Swap(input_token, output_token, input_quantity);
      wallet[input_token] -= input_quantity;
      mintToken(output_token, output_quantity); //use mintToken since the output_token may not be in wallet
      usd_value -= input_quantity*input_token->getPrice();
      usd_value += output_quantity*output_token->getPrice();
    }
  }

  private:
  Account(const std::string &name) : name_(name) {}
	static std::unordered_map<std::string, Account *> existing_acc_;
	std::string name_;
public:
	// disallow copying
	Token & operator=(const Token &) = delete;
	Token(const Token &) = delete;
  unordered_map<Token*, double> wallet;
  double usd_value;
  static set<string> existing_acc;
  string name_;
  
};

static unordered_map<string, Account *> existing_acc_ = unordered_map<string, Account *> ();

#endif