#define TOKEN_PATH  ../Token.hpp

#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;

class Protocol_Formulas {
protected:
    string name;
    int nTokens;
public:
    Protocol_Formulas() : name("UniswapV2"), nTokens(2) {}
    ~Protocol_Formulas() {}

    string get_Identity()   {   return  name;       }
    int get_nTokens()       {   return  nTokens;    }

    virtual double compute_invariant(const vector<double>&);
    virtual double compute_spot_exchange_rate(const vector<double>&, int, int);
    virtual double compute_swapped_quantity(const vector<double>&, int , int, double);
    virtual double compute_slippage(const vector<double>&, int, int, double);
    virtual double compute_divergence_loss(const vector<double>&r, double);
};
