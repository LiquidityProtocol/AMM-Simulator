#ifndef CURVE_POOL_HPP
#define CURVE_POOL_HPP

#include "../Utilities/Utilities.hpp"
#include <cmath>

double solve(int n, double a, double b) { // solve equation x^n + ax + b = 0
    if (abs(a) < 1e-6) return std::pow(-b, 1.0 / n);
    
    auto calc_f = [&](double x) {
        return std::pow(x, n) + a * x + b;
    };
    auto solve_interval = [&](double l, double r, bool increasing) {
        for (int _ = 0 ; _ < 64 ; ++_) {
            double m = (l + r) / 2;
            double f = calc_f(m);

            if (increasing) {
                f > 1e-6 ? r = m : l = m;
            } else {
                f < -1e-6 ? r = m : l = m;
            }
        }
        return (l + r) / 2;
    };

    if (n % 2 == 0) {
        double extrema;
        if (a > 0)  extrema = -std::pow(a / n, 1.0 / (n - 1));
        else        extrema = std::pow(-a / n, 1.0 / (n - 1));

        if (calc_f(extrema) > 0)
            throw std::invalid_argument("unable to find constant");
        
        double C = solve_interval(extrema, 1e9, true);
        assert(abs(calc_f(C)) < 1e-6);

        return C;
    } else {
        if (a > 0) { // the function is increasing
            return solve_interval(-1e9, 1e9, true);
        } else {
            double extrema1 = -std::pow(-a / n, 1.0 / (n - 1));
            double extrema2 = std::pow(-a / n, 1.0 / (n - 1));

            if (calc_f(extrema2) < 1e-6) {
                return solve_interval(extrema2, 1e9, true);
            } else if (calc_f(extrema1) < 1e-6) {
                return solve_interval(extrema1, extrema2, false);
            } else {
                return solve_interval(-1e9, extrema1, true);
            }
        }
    }
}

class CurvePool : public PoolInterface {
public:
    CurvePool(std::unordered_map<Token *, double> quantities,
                  double pool_fee, 
                  double leverage = 0) : PoolInterface(quantities, pool_fee) {
                    
        if (leverage < 0) {
            throw std::invalid_argument("invalid leverage");
        } else {
            leverage_ = leverage;
        }
        double S = 0;
        double P = 1;
        int n = quantities.size();

        for (auto [token, quantity] : quantities) {
            S += quantity / scale_;
            P *= quantity / scale_;
        }
        // A * (S / C - 1) = (C / n) ** n / P - 1
        constant_ = solve(n + 1, std::pow(n, n) * P * (leverage - 1), -std::pow(n, n) * P * leverage * S);
    }
private:
    const double scale_ = 1000;
    double leverage_;
    double constant_;

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
        return constant_ * scale_ * GetQuantity(pool_token());
    }
    double ComputeSpotExchangeRate(Token *input_token, Token *output_token) const {
        double r1 = GetQuantity(input_token);
        double r2 = GetQuantity(output_token);

        double P = Product();
        double C = ComputeInvariant({});

        int n = quantities_.size() - 1;

        double spot_price = r1 / r2;

        spot_price *= (leverage_ * r2 * P + C * std::pow(C / n, n));
        spot_price /= (leverage_ * r1 * P + C * std::pow(C / n, n));

        return spot_price;
    }

    double ComputeSwappedQuantity(Token *input_token, Token *output_token, double input_quantity) const {
        int n = quantities_.size() - 1;

        double C = ComputeInvariant(quantities_);
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