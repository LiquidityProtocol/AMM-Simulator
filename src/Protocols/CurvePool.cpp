#include "CurvePool.hpp"

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