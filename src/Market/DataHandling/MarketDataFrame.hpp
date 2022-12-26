//
//  MarketDataFrame.cpp
//  Backtest Environment
//
//  Created by Evan Kirkiles on 5/27/18.
//  Copyright © 2018 Evan Kirkiles. All rights reserved.
//

#ifndef MarketDataFrame_hpp
#define MarketDataFrame_hpp

#include <string>
#include <stdio.h>
#include <vector>
#include <map>

class MarketDataFrame {
public:
    std::map<long, std::map<std::string, double>> transactions;
    std::map<long, std::map<std::string, double>> token_volume;
    std::vector<long> timestamps;

    MarketDataFrame(char txt_file[FILENAME_MAX], char csv[FILENAME_MAX]);
    MarketDataFrame() = default;
};

long get_epoch_time(std::string date);
std::string get_std_time(long epochtime);

#endif /* MarketDataFrame_hpp */