#ifndef CURVE_POOL_HPP
#define CURVE_POOL_HPP

#include <cmath>
#include "../Utilities/Utilities.hpp"

class Curve : public PoolInterface {
public:
    Curve(std::unordered_map<Token *, double> quantities,
                  double pool_fee, 
                  double leverage=0) : PoolInterface(quantities, pool_fee) {

    int n = quantities.size()

    if(leverage<0){
            throw std::invalid_argument("leverage can go from zero to infinity only");
    }
    else{
        leverage_ = leverage;
    }
}

private:
    
    double leverage_;
    int n;
    double SumInvariant(std::unordered_map<Token *, double> quantities){
        double sum = 0;
        double product = 1;
        int n = quantities.size();
        for (auto [token, quantity] : quantities) {
            sum += quantity;
            product *= quantity;
        }
        if (leverage_ < 1e-10){
            return std::pow(product, 1/n) * n;
        } 
        if (leverage_ == 1){
            return std::pow(product * sum, 1 / (n + 1)) * std::pow(n, n/(n+1));
        }

        if (n == 2){
            return;

        }
        // raise Exception("cannot handle unequal asset pool with n>2")

    }




    double ComputeSpotExchangeRate(Token *input_token, Token *output_token) const {
        return ;
    }

    double ComputeSwappedQuantity(Token *input_token, Token *output_token, double input_quantity) const {
        double C = SumInvariant(std::unordered_map<Token *, double> quantities);
        double X = std::pow((C / n),n);
        double r1 = GetQuantity(input_token);
        double r2 = GetQuantity(output_token);
        double updated_reserves_in = (r1 + input_quantity);
        double product = 1;
        double sum = 0;
        for (auto [token, quantity] : quantities){
            sum += quantity;
            product *= quantity;
        }
        double product_prime_excluding_output_token = r1_prime * product/(r1*r2);
        double sum_prime_excluding_output_token = sum + input_quantity - r2;
        double A = std::max(leverage_, std::pow(10, -5));
        double B = (1 - 1/A)*C - sum_prime_excluding_output_token;
        double updated_reserves_out = (B + sqrt((B*B + 4 * C * X / A / prod_exo))) / 2;
        return r2 - updated_reserves_out;
    }

    double ComputeSlippage(Token *input_token, Token *output_token, double input_quantity) const {
        double SwappedQuantity = ComputeSwappedQuantity(input_token, output_token, input_quantity);
        //double r2 = SwappedQuantity + GetQuantity(output_token);
        double r1 = input_quantity;
        double p = ComputeSpotExchangeRate(GetQuantity(input_quantity), GetQuantity(output_token));
        return (r1/SwappedQuantity)/p - 1;
    }


};

#endif