#ifndef STRAT_BOLLINGER_BANDS
#define STRAT_BOLLINGER_BANDS

#include "../Infrastructure/Signals.hpp"
#include <cmath>


//In this example, the Bollinger Bands indicator is used to identify potential entry or exit points
//for traders by comparing the current price to the upper and lower bands of a moving average and 
//standard deviation. When the current price is above the upper band, a sell signal is generated,
//and when the current price is below the lower band, a buy signal is generated.

namespace BollingerBands {
    //This function calculates the Simple Moving Average (SMA) of the prices over a given period. 
    // It uses a for loop to iterate over the prices array and add them up, then returns the average by dividing the sum by the period
    double calculateSMA(std::vector<double> prices, int period) {
        double sum = 0;
        for (int i = 0; i < period; i++) {
            sum += prices[i];
        }
        return sum / period;
    }
    //This function calculates the standard deviation of the prices over a given period. 
    double calculateStandardDeviation(std::vector<double> prices, int period, double SMA) {
        double sum = 0;
        for (int i = 0; i < period; i++) {
            sum += pow(prices[i] - SMA, 2);
        }
        return sqrt(sum / period);
    }
    //This function generates signals to buy or sell based on the Bollinger Bands indicator
    //calculates the upper and lower bands using the standard deviation multiple.
    //compares the current price to the upper and lower bands and generates a buy signal if the price is below the lower band or a sell signal if the price is above the upper band
    void calculateSignal(std::vector<Signal> &signals, std::vector<double> prices, int period, double standard_deviation_multiple) {
        double SMA = calculateSMA(prices, period);
        double standard_deviation = calculateStandardDeviation(prices, period, SMA);
        double upper_band = SMA + standard_deviation * standard_deviation_multiple;
        double lower_band = SMA - standard_deviation * standard_deviation_multiple;

        if (prices.back() > upper_band) {
            signals.push_back(Signal(SignalType::SELL));
        } else if (prices.back() < lower_band) {
            signals.push_back(Signal(SignalType::BUY));
        }
    }
}
#endif
