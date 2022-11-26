#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP

#include <unordered_map>
#include <unordered_set>

#include <stdexcept>
#include "Token.hpp"

using namespace std;

template<typename T>
class Protocol  {
protected:
    string name;
    T invariant;
    static std::unordered_map<string, Protocol<T>*> existing_protocols;
    
    Protocol() : name("UniSwapV2")  {}
public:
    // disallow copying
	Protocol & operator=(const Protocol &) = delete;
	Protocol(const Protocol &) = delete;

    static Protocol* GetProtocol(const std::string &name)   {
		if (!existing_protocols.count(name))    {
            if (name == "UniSwapV2")
                existing_protocols[name] = new Protocol();
            else
                throw invalid_argument("invalid protocol");
        }
        
		return existing_protocols[name];
	}

    string getIdentity()    {   return  name;   }
    void setInvariant(T C)  {   invariant = C;  }

    #define r(x)    r.find(x)->second

    virtual double computeSpotExchangeRate(const unordered_map<Token *, double>& r, Token *i, Token *o) {
        if (i == o) return  1;
        else        return  r(i) / r(o);
    }
    virtual double computeSwapQuantity(const unordered_map<Token *, double>& r, Token *i, Token *o, double quantity_in) {
        if (i == o) return  quantity_in;

        double new_ri = r(i) + quantity_in;
        double new_ro = r(i) * r(o) / new_ri;

        return  r(o) - new_ro;
    }
    virtual double computeDivergenceLoss(const unordered_map<Token *, double>& r, double p) {
        return  sqrt(1 + p) / (1 + p/2) - 1;
    }
    
    double computeSlippage(const unordered_map<Token *, double>& r, Token *i, Token *o, double quantity_in) {
        double quantity_out  = computeSwapQuantity(r, i, o, quantity_in);
        double exchange_rate = computeSpotExchangeRate(r, i, o);

        return  quantity_in / quantity_out / exchange_rate - 1;
    }
};
template<typename T>
unordered_map<string, Protocol<T>*> Protocol<T>::existing_protocols = unordered_map<string, Protocol<T>*>();
#endif