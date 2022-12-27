#ifndef CURVE_POOL_HPP
#define CURVE_POOL_HPP

#include "../Utilities/Utilities.hpp"
#include <cmath>

double solve(int n, double a, double b); // solve equation x^n + ax + b = 0

class CurvePool : public PoolInterface {
public:
    friend class Playground;
    friend class Market;
private:
    CurvePool(std::unordered_set<Token *> tokens,
                  double pool_fee, 
                  double leverage = 0) : PoolInterface(tokens, pool_fee) {
                    
        if (leverage < 0) {
            throw std::invalid_argument("invalid leverage");
        } else {
            leverage_ = leverage;
        }
    }
    CurvePool(std::unordered_map<Token *, double> quantities,
                  double pool_fee, 
                  double leverage = 0) : PoolInterface(quantities, pool_fee) {
                    
        if (leverage < 0) {
            throw std::invalid_argument("invalid leverage");
        } else {
            leverage_ = leverage;
        }
    }
    double leverage_;

    double Sum() const {
        double ans = 0;
        for (auto token : tokens())
            ans += GetQuantity(token);
        return ans;
    }
    double Product() const {
        double ans = 1;
        for (auto token : tokens())
            ans *= GetQuantity(token);
        return ans;
    }

    double ComputeInvariant(const std::unordered_map<Token *, double> &quantities) const {
        // the params of this function is not related
        // I only take into account the invariant of the pool
        static double constant_ = 0;

        if (quantities == this->quantities()) {
            if (constant_) {
                return constant_ * GetQuantity(pool_token());
            } else {
                const double scale = 10000;
                double S = 0;
                double P = 1;

                int n = quantities.size();
                
                for (auto [token, quantity] : quantities) {
                    S += quantity / scale;
                    P *= quantity / scale;
                }
                // A * (S / C - 1) = (C / n) ** n / P - 1
                return constant_ = solve(n + 1, std::pow(n, n) * P * (leverage_ - 1), -std::pow(n, n) * P * leverage_ * S) * scale;
            }
        } else {
            throw std::invalid_argument("Not passing snapshot of this pool");
        }
    }
    double ComputeSpotExchangeRate(Token *input_token, Token *output_token) const {
        double r1 = GetQuantity(input_token);
        double r2 = GetQuantity(output_token);

        double P = Product();
        double C = ComputeInvariant({});

        int n = quantities().size();

        double spot_price = r1 / r2;

        spot_price *= (leverage_ * r2 * P + C * std::pow(C / n, n));
        spot_price /= (leverage_ * r1 * P + C * std::pow(C / n, n));

        return spot_price;
    }

    double ComputeSwappedQuantity(Token *input_token, Token *output_token, double input_quantity) const {
        int n = quantities().size();

        double C = ComputeInvariant(quantities());
        double X = std::pow((C / n),n);

        double prod_exo = 1;    // new pool product excluding output asset
        double sum_exo = 0;     // new pool sum excluding output asset

        for (auto token : tokens()) {
            double _x;
            if (token == input_token) {
                _x = GetQuantity(token) + input_quantity;
            } else if (token != output_token) {
                _x = GetQuantity(token);
            } else {
                continue;
            }
            prod_exo *= _x;
            sum_exo += _x;
        }
        double A = std::max(leverage_, std::pow(10, -5));
        double B = (1 - 1 / A) * C - sum_exo;

        double r2_prime = (B + sqrt((B * B + 4 * C * X / A / prod_exo))) / 2;

        return GetQuantity(output_token) - r2_prime;
    }
};

#endif