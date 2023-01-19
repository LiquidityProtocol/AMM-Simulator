#ifndef STRAT_LINEAR_REGRESSION
#define STRAT_LINEAR_REGRESSION

#include "../Infrastructure/Signals.hpp"
#include <cmath>

namespace LinearRegression {
    class LRchannel {
    public:
        LRchannel(double m, double b, double d) :
            slope_(m),
            intercept_(b),
            deviation_(d) {}

        double fit(double x) const {
            return slope_ * x + intercept_;
        }
        double deviation() const {
            return deviation_;
        }

    private:
        double slope_;
        double intercept_;
        double deviation_;
    };
    LRchannel calculateLR(std::vector<double> bars) {
        double Xmean = (double)(bars.size() + 1) / 2;
        double Ymean = accumulate(bars.begin(), bars.end(), (double)0) / (double)bars.size();

        double variance_X = 0;
        double variance_Y = 0;

        double covariance_XY = 0;

        for (size_t i = 0 ; i < bars.size() ; ++i) {
            variance_X += std::pow(i + 1 - Xmean, 2);
            variance_Y += std::pow(bars[i] - Ymean, 2);

            covariance_XY += (i + 1 - Xmean) * (bars[i] - Ymean);
        }
        variance_X /= (double)bars.size();
        variance_Y /= (double)bars.size();
        covariance_XY /= (double)bars.size();

        double slope = covariance_XY / variance_X;
        double intercept = Ymean - slope * Xmean;

        return LRchannel(slope, intercept, sqrt(variance_Y));
    }

    void calculateSignal(std::vector<Signal> &signal, PoolInterface *pool) {
        std::vector<Operation *> opsList = pool->GetLatestOps(50);

        if (opsList.empty())
            return;

        for (Token *a : pool->tokens())
        for (Token *b : pool->tokens()) {
            if (a->name() == b->name())
                continue;

            std::vector<double> bars;

            for (auto ops : opsList)
                bars.push_back(ops->GetSpotPrice(a, b));

            LRchannel fitChannel = calculateLR(bars);

            double fit = fitChannel.fit(bars.size());
            double dev = fitChannel.deviation();

            if (bars.back() < fit && (fit - bars.back()) / dev > 0.5)
                signal.push_back(Signal(pool, a, b));
        }
    }
}

#endif
