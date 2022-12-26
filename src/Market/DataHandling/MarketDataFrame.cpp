#include <fstream>
#include <iostream>
#include <sstream>

#include <algorithm>
#include <stdio.h>
#include <cassert>
#include "MarketDataFrame.hpp"

// Find epoch time from normal YYYY-MM-DD
long get_epoch_time(std::string date) {
    std::string delimiter = "-";
    std::string token;
    struct tm t = {0};
    size_t pos = 0;

    while ((pos = date.find(delimiter)) != std::string::npos) {
        token = date.substr(0, pos);
        date.erase(0, pos + delimiter.length());

        if (pos == 4) {
            t.tm_year = stoi(token);
        } else {
            assert(pos == 2);
            t.tm_mon = stoi(token);
        }
    }

    if (date == "Date") {
        t.tm_mday = 0;
    } else {
        t.tm_mday = stoi(date);
    }
        
    // Get time since 1900 epoch
    t.tm_year -= 1900;
    t.tm_mon--;
    t.tm_hour = 0;
    t.tm_min = 0;
    t.tm_sec = 0;
    time_t timeSinceEpoch = mktime(&t);
    
    return long(timeSinceEpoch);
}

// Find normal time YYYY-MM-DD from epoch time
std::string get_std_time(long epochtime) {
    time_t t = epochtime;
    char string[80];
    strftime(string, 80, "%Y-%m-%d", gmtime(&t));
    return string;
}
    
// Takes .csv data in type-amount0-amount1-date format and makes it into a map of maps
MarketDataFrame::MarketDataFrame(char txt_file[FILENAME_MAX], char csv_file[FILENAME_MAX]) {
    std::ifstream txt(txt_file);
    std::ifstream csv(csv_file);
    std::string line;

    std::vector<std::string> symbols;
    std::vector<double> volume;

    // Iterate through the csv file
    while (getline(txt, line)) {
        std::string token_symbol;
        double token_volume;

        std::stringstream ss(line);

        ss >> token_symbol >> token_volume;

        symbols.push_back(token_symbol);
        volume.push_back(token_volume);
    }
    
    // Iterate through the csv file
    while(getline(csv, line)) {
        replace(line.begin(), line.end(), ',', ' ');
        std::stringstream ss(line);
        std::string type;

        double amount0;
        double amount1;
        long timestamp;

        ss >> type;
        ss >> amount0;
        ss >> amount1;
        ss >> timestamp;

        if (type == "BURN") {
            amount0 *= -1;
            amount1 *= -1;
        }
        
        // Add the date to the indices
        transactions[timestamp][symbols[0]] = amount0;
        transactions[timestamp][symbols[1]] = amount1;

        timestamps.push_back(timestamp);
    }
    for (auto itr = transactions.end() ; itr != transactions.begin() ;) {
        itr--;

        long timestamp = (itr->first);

        volume[0] -= (itr->second).find(symbols[0])->second;
        volume[1] -= (itr->second).find(symbols[1])->second;

        token_volume[timestamp][symbols[0]] = volume[0];
        token_volume[timestamp][symbols[1]] = volume[1];
    }
};

// int main() {
//     MarketDataFrame a("data/sample_poolconfig.txt", "data/sample_transactions.csv");

//     for (int i = 0 ; i < 10 ; ++i) {
//         long timestamp = a.timestamps[a.timestamps.size() - i - 1];
        
//         std::cerr << "Date: " << get_std_time(timestamp) << "\n";

//         for (auto [symbol, amount] : a.transactions[timestamp])
//             std::cerr << ">> " << symbol << ": " << amount << "\n";
        
//         std::cerr << "  Volume:\n";

//         for (auto [symbol, volume] : a.token_volume[timestamp])
//             std::cerr << ">> " << symbol << ": " << volume << "\n";
//     }
// }