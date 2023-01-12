//First code in the project

#include <iostream>
#include "Utilities/DivergenceLossNoFees.hpp"
#include <random>
using namespace std;

int main() {
    vector<double> p;
    p = Divergence_loss_UNISWAP_visualisation();
    for (int i = 0; i < 7; ++i) {
        cout << p[i] << " ";
    }
    return 0;
}
