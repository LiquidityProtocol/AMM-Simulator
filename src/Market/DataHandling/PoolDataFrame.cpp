#include <fstream>
#include <iostream>
#include <sstream>

#include <algorithm>
#include <stdio.h>
#include <cstdlib>
#include <cassert>
#include "PoolDataFrame.hpp"

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

std::ostream & operator << (std::ostream &os, const Transaction &a) {
    os << std::fixed << std::setprecision(5);
    os << "Date: " << get_std_time(a.GetTimeStamp()) << "\n";
    os << a.GetType() << "\n";

    os << ">> " << a.symbol_[0] << ": " << "Amount = " << a.amount_[0] << ", Volume = " << a.volume_[0] << "\n";
    os << ">> " << a.symbol_[1] << ": " << "Amount = " << a.amount_[1] << ", Volume = " << a.volume_[1] << "\n";

    return os;
}

Transaction::Transaction(long timestamp, std::string *symbols, double *amount, double *volume) : timestamp_(timestamp) {
    symbol_ = symbols;
    amount_ = amount;
    volume_ = volume;

    if (amount[0] > 0 && amount[1] > 0) {
        type_ = "MINT";
    } else if (amount[0] < 0 && amount[1] < 0) {
        type_ = "BURN";
    } else {
        type_ = "SWAP";
    }
}
std::vector<std::string> Transaction::GetSymbol() const {
    return {symbol_[0], symbol_[1]};
}
std::vector<double> Transaction::GetAmount() const {
    return {amount_[0], amount_[1]};
}
std::vector<double> Transaction::GetVolume() const {
    return {volume_[0], volume_[1]};
}
std::string Transaction::GetType() const {
    return type_;
}
long Transaction::GetTimeStamp() const {
    return timestamp_;
}

// Takes .csv data in type-amount0-amount1-date format and makes it into a map of maps
PoolDataFrame::PoolDataFrame(std::string pool_id) {
    std::string txt_file = "data/" + pool_id + "/poolconfig.txt";
    std::string csv_file = "data/" + pool_id + "/transactions.csv";

    if (FILE *file = fopen(csv_file.c_str(), "r")) {
        fclose(file);
    } else {
        system(("python3 ./UniSwapQuery.py " + pool_id).c_str());
    }

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

Transaction PoolDataFrame::operator[](int i) {
    long timestamp = timestamps[i];

    std::string *Symbols = new std::string[2];
    double *Amount = new double[2];
    double *Volume = new double[2];

    int cnt = 0;

    for (auto [symbol, amount] : transactions[timestamp]) {
        Symbols[cnt] = symbol;
        Amount[cnt] = amount;
        Volume[cnt] = token_volume[timestamp][symbol];

        cnt++;
    }
    return Transaction(timestamp, Symbols, Amount, Volume);
}
size_t PoolDataFrame::size() const {
    return timestamps.size();
}

// int main() {
//     PoolDataFrame dt("0x6c6bc977e13df9b0de53b251522280bb72383700");

//     std::cerr << dt.size() << "\n";
//     std::cerr << dt[5];
// }