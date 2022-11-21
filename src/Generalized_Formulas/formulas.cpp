#include <iostream>
#include <vector>
#include <math.h>
#include "message.hpp"
#include "formulas.hpp"

using namespace std;

double Protocol_Formulas::compute_invariant(const vector<double>& r)    {
    return  r[0] * r[1];
}
double Protocol_Formulas::compute_spot_exchange_rate(const vector<double>& r, int i, int o)  {
    return  r[i] / r[o];
}
double Protocol_Formulas::compute_swapped_quantity(const vector<double>& r, int i, int o, double quantity_in)   {
    alert(i != o, "", "The exchanged tokens need to be different.");

    double new_ri = r[i] + quantity_in;
    double new_ro = r[0] * r[1] / new_ri;

    return  r[o] - new_ro;
}
double Protocol_Formulas::compute_slippage(const vector<double>& r, int i, int o, double quantity_in) {
    double quantity_out  = compute_swapped_quantity(r, i, o, quantity_in);
    double exchange_rate = compute_spot_exchange_rate(r, i, o);

    return  quantity_in / quantity_out / exchange_rate - 1;
}
double Protocol_Formulas::compute_divergence_loss(const vector<double>& r, double p)    {
    return  sqrt(1 + p) / (1 + p/2) - 1;
}

#define TEST_FORMULAS   1

int main()  {
    #if TEST_FORMULAS == 1
    Protocol_Formulas *F = new Protocol_Formulas();
    vector<double> r = {10, 1000};  // ETH, DAI

    alert(F -> compute_invariant(r) == 10000,
        "Invariant Correct",
        "Invariant Wrong");
    
    alert(F -> compute_spot_exchange_rate(r, 1, 0) == 100,
        "Exchange Rate Correct",
        "Exchange Rate Wrong");
    
    alert(abs(F -> compute_divergence_loss(r, 1) + 0.05719) < 0.001,
        "Calculate the Divergence Loss Correct",
        "Calculate the Divergence Loss Wrong");
    #endif
}
