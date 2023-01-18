#ifndef EPOCHDATA_HPP
#define EPOCHDATA_HPP

#include "../../Utilities/Utilities.hpp"

class EpochData {
public:
    EpochData(PoolInterface *pool);

    void loadHistory(int nOps);
    void checkPair(Token *a, Token *b) const;

    double getOpenPrice(Token *a, Token *b) const;
    double getClosePrice(Token *a, Token *b) const;
    double getHighPrice(Token *a, Token *b) const;
    double getLowPrice(Token *a, Token *b) const;
private:
    PoolInterface *pool_;

    std::unordered_map<Token *, std::unordered_map<Token*, double> > open, high, low, close;
};

#endif // EPOCHDATA_HPP
