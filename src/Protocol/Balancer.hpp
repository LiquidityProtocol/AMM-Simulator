#ifndef BALANCER_HPP
#define BALANCER_HPP

#include <unordered_map>
#include <unordered_set>

#include <stdexcept>
#include <math.h>

#include "Protocol.hpp"

using namespace std;

class Balancer_protocol : public Protocol<double>   {
private:
    Balancer_protocol() {   name_ = "Balancer"; }
    unordered_map<Token*, double> weights;

    #define w(i)    weights.find(o)->second

    static Balancer_protocol *pProtocol;
public:
    static Balancer_protocol *getProtocol() {
        if (!pProtocol)
            pProtocol = new Balancer_protocol();
        return  pProtocol;
    }
    void setWeight(const unordered_map<Token*, double>& w)  {
        weights = w;
    }
    double computeSpotExchangeRate(const unordered_map<Token *, double>& r, Token *i, Token *o) {
        if (i == o) return  1;
        else        return  r(i) * w(o) / r(o) / w(i);
    }
    double computeSwapQuantity(const unordered_map<Token *, double>& r, Token *i, Token *o, double quantity_in) {
        if (i == o) return  quantity_in;

        double new_ri = r(i) + quantity_in;
        double new_ro = r(o) * pow(r(i) / new_ri, w(i) / w(o));

        return  r(o) - new_ro;
    }
    double computeDivergenceLoss(const unordered_map<Token *, double>& r, double p) {
        // need to implement this later
        return  0;
    }
};
Balancer_protocol *Balancer_protocol::pProtocol = nullptr;
#endif