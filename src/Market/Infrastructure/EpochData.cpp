#include "EpochData.hpp"

EpochData::EpochData(PoolInterface *pool) : pool_(pool) {}

void EpochData::loadHistory(int nOps) {
    std::vector<Operation *> opsList = pool_->GetLatestOps(nOps);

    for (Token *a : pool_->tokens())
    for (Token *b : pool_->tokens())
        if (a->name() != b->name()) {
            if (opsList.empty()) {
                open[a][b] = high[a][b] = low[a][b] = close[a][b] = pool_->GetSpotPrice(a, b);
            } else {
                std::vector<double> price;

                for (auto ops : opsList)
                    price.push_back(ops->GetSpotPrice(a, b));

                open[a][b] = price[0];
                close[a][b] = price.back();

                high[a][b] = *max_element(price.begin(), price.end());
                low[a][b] = *min_element(price.begin(), price.end());
            }
        }
}

void EpochData::checkPair(Token *a, Token *b) const {
    if (!open.count(a) || !(open.find(a)->second).count(b))
        throw std::invalid_argument("Pool doesn't support this pair");
}

double EpochData::getOpenPrice(Token *a, Token *b) const {
    checkPair(a, b);
    return (open.find(a)->second).find(b)->second;
}

double EpochData::getClosePrice(Token *a, Token *b) const {
    checkPair(a, b);
    return (close.find(a)->second).find(b)->second;
}

double EpochData::getHighPrice(Token *a, Token *b) const {
    checkPair(a, b);
    return (high.find(a)->second).find(b)->second;
}

double EpochData::getLowPrice(Token *a, Token *b) const {
    checkPair(a, b);
    return (low.find(a)->second).find(b)->second;
}
