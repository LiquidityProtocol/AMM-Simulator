//
//  MarketDataFrame.cpp
//  Backtest Environment
//
//  Created by Evan Kirkiles on 5/27/18.
//  Copyright © 2018 Evan Kirkiles. All rights reserved.
//

#ifndef MarketDataFrame_hpp
#define MarketDataFrame_hpp

#include <iostream>
#include <iomanip>
#include <string>
#include <stdio.h>
#include <vector>
#include <map>

class Transaction {
public:
    friend class PoolDataFrame;
    friend std::ostream & operator << (std::ostream &os, const Transaction &a);

    std::vector<std::string> GetSymbol() const;
    std::vector<double> GetAmount() const;
    std::vector<double> GetVolume() const;
    std::string GetType() const;
    long GetTimeStamp() const;
private:
    Transaction(long timestamp, std::string *symbols, double *amount, double *volume);
    Transaction() = default;

    long timestamp_;
    std::string type_;
    std::string *symbol_;
    double *amount_;
    double *volume_;
};

class PoolDataFrame {
public:
    PoolDataFrame(std::string pool_id);
    PoolDataFrame() = default;

    Transaction operator [](int i);
    size_t size() const;
private:
    std::map<long, std::map<std::string, double>> transactions;
    std::map<long, std::map<std::string, double>> token_volume;
    std::vector<long> timestamps;
};

long get_epoch_time(std::string date);
std::string get_std_time(long epochtime);

#endif /* MarketDataFrame_hpp */