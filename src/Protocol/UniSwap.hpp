#ifndef UNISWAP_HPP
#define UNISWAP_HPP

#include <stdexcept>
#include <math.h>

#include "Protocol.hpp"

using namespace std;

#define ld      double
#define p(x)    pair<x, x>

class UniSwapV2_protocol : public Protocol<ld>    {
private:
    UniSwapV2_protocol()    {   name_ = "UniSwapV2";    }
    static UniSwapV2_protocol *pProtocol;
public:
    static UniSwapV2_protocol *getProtocol()    {
        if (!pProtocol)
            pProtocol = new UniSwapV2_protocol();
        return  pProtocol;
    }
    double computeSpotExchangeRate(const unordered_map<Token *, double>& r, Token *i, Token *o) {
        if (i == o) return  1;
        else        return  r(i) / r(o);
    }
    double computeSwapQuantity(const unordered_map<Token *, double>& r, Token *i, Token *o, double quantity_in) {
        if (i == o) return  quantity_in;

        double new_ri = r(i) + quantity_in;
        double new_ro = r(i) * r(o) / new_ri;

        return  r(o) - new_ro;
    }
    double computeDivergenceLoss(const unordered_map<Token *, double>& r, double p) {
        return  sqrt(1 + p) / (1 + p/2) - 1;
    }
    double computeSlippage(const unordered_map<Token *, double>& r, Token *i, double quantity_in)   {
        return  quantity_in / r(i);
    }
};
class UniSwapV3_protocol : public Protocol<p(ld)> {
private:
    #define A   slippage_controller
    #define B   sqrt(A) - 1
    
    double slippage_controller = 2;
    static UniSwapV3_protocol *pProtocol;

    #define C1  invariant.first
    #define C2  invariant.second

    UniSwapV3_protocol()    {   name_ = "UniSwapV3";    }
public:
    static UniSwapV3_protocol *getProtocol()    {
        if (!pProtocol)
            pProtocol = new UniSwapV3_protocol();
        return  pProtocol;
    }
    void setSlippageController(double _A)   {   A = _A; }
    double computeSpotExchangeRate(const unordered_map<Token *, double>& r, Token *i, Token *o) {
        assert(r.size() == 2);

        if (i == o) return  1;
        if (r.find(i) == r.begin()) return  (B * r(i) + C1) / (B * r(o) + C2);
        if (r.find(o) == r.begin()) return  (B * r(i) + C2) / (B * r(o) + C1);

        assert(0);
    }
    double computeSwapQuantity(const unordered_map<Token *, double>& r, Token *i, Token *o, double quantity_in) {
        if (i == o) return  quantity_in;

        double new_ri = r(i) + quantity_in;
        double new_ro = 0;

        if (r.find(i) == r.begin()) new_ro = (A * C1 * C2 / (B * new_ri + C1) - C2) / B;
        if (r.find(o) == r.begin()) new_ro = (A * C1 * C2 / (B * new_ri + C2) - C1) / B;

        if (new_ro == 0)    throw invalid_argument("invalid exchanged tokens");

        return  r(o) - new_ro;
    }
    double computeDivergenceLoss(const unordered_map<Token *, double>& r, double p) {
        if (p <= -1)    throw invalid_argument("invalid change in price");
        if (p <= 1/A - 1)   return  ((p + 1) * sqrt(A) - 1) / (2 + p);
        if (p <= A - 1)     return  (sqrt(p + 1) / (1 + p/2) - 1) / (1 - 1/sqrt(A));
        else                return  (sqrt(A) - 1 - p) / (2 + p);
    }
    double computeSlippage(const unordered_map<Token *, double>& r, Token *i, double quantity_in)   {
        return  quantity_in / (r(i) + (r.find(i) == r.begin() ? C1 : C2) / B);
    }
};

UniSwapV2_protocol *UniSwapV2_protocol::pProtocol = nullptr;
UniSwapV3_protocol *UniSwapV3_protocol::pProtocol = nullptr;
#endif