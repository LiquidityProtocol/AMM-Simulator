#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP

#include <unordered_map>
#include <unordered_set>

#include <stdexcept>
#include "../Token.hpp"

using namespace std;

template<typename T>
class Protocol  {
protected:
    string name_;
    T invariant;
    
    Protocol<T>(const string &name) : name_(name)   {}
    Protocol<T>() : name_("Combi") {}

    #define r(x)    r.find(x)-> second
public:
    string name()           {   return  name_;  }
    void setInvariant(T C)  {   invariant = C;  }

    // disallow copying
	Protocol & operator=(const Protocol &) = delete;
	Protocol(const Protocol &) = delete;

    virtual double computeSpotExchangeRate(const unordered_map<Token*, double>&, Token*, Token*) = 0;
    virtual double computeSwapQuantity(const unordered_map<Token*, double>&, Token*, Token*, double) = 0;
    virtual double computeDivergenceLoss(const unordered_map<Token*, double>&, double) = 0;
    virtual double computeSlippage(const unordered_map<Token *, double>& r, Token *i, Token *o, double quantity_in) {
        double quantity_out  = computeSwapQuantity(r, i, o, quantity_in);
        double exchange_rate = computeSpotExchangeRate(r, i, o);

        return  quantity_in / quantity_out / exchange_rate - 1;
    }
    // the slippage function is optional to be defined again for inherit class
};
#endif