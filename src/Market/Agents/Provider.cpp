#include "Provider.hpp"

Provider::Provider(const std::string name, double budget) : Account(name, budget) {}

void Provider::StrategicProvide(PoolInterface *pool) {
    Token *token1 = *(pool->tokens()).begin();
    Token *token2 = *(++(pool->tokens()).begin());

    double PoolRatio = pool->GetSpotPrice(token1, token2);
    double MarketRatio = token2->real_value() / token1->real_value();

    double LP_discourage = abs(log(PoolRatio) - log(MarketRatio));
    double LP_volume = (1 - LP_discourage) * total_value() * 0.2;
    double LP_amount = LP_volume / pool->pool_token_value();

    if (LP_amount < 0) {
        LP_amount = std::min(-LP_amount, GetQuantity(pool->pool_token()));
        if (LP_amount > 0)
            Withdraw(pool, LP_amount);
    } else {
        std::unordered_map<Token *, double> providingQuantities;
        std::unordered_set<Token *> tokenSet = pool->tokens();

        for (auto [token, quantity] : wallet())
            if (!token->pool())
                tokenSet.emplace(token);

        double neededBudget = 0;

        for (auto token : tokenSet) {
            double neededQuantity = pool->GetQuantity(token) / pool->total_pool_token_quantity() * LP_amount;
            double activeQuantity = GetQuantity(token);

            if (activeQuantity > neededQuantity) {
                sell(token, (activeQuantity - neededQuantity) * 0.6);
            } else {
                neededBudget += (neededQuantity - activeQuantity) * token->real_value();
            }
        }
        if (budget() < neededBudget) {
            LP_amount /= neededBudget;
            LP_amount *= budget() * 0.9;
        }

        for (auto token : tokenSet) {
            double neededQuantity = pool->GetQuantity(token) / pool->total_pool_token_quantity() * LP_amount;
            double activeQuantity = GetQuantity(token);

            if (activeQuantity < neededQuantity) {
                buy(token, neededQuantity - activeQuantity);
            }
            providingQuantities[token] = neededQuantity;
        }
        Provide(pool, providingQuantities);
    }
}

void Provider::calcHoldValue(PoolInterface *pool, std::vector<double> &vals) const {
    vals.clear();

    double hold = 0;
    double share = 0;

    for (size_t i = 0 ; i < provideHistory.size() ; ++i)
    for (auto [token, quantity] : provideHistory[i].find(pool)->second)
        hold += quantity * token->real_value();

    vals.push_back(hold);

    for (size_t i = 0 ; i < provideHistory.size() ; ++i) {
        for (auto [token, quantity] : provideHistory[i].find(pool)->second)
            hold -= quantity * token->real_value();

        share += benefitHistory[i].find(pool)->second;
        vals.push_back(hold + share * pool->pool_token_value());
    }
}

void Provider::calcShareValue(PoolInterface *pool, double &val) const {
    val = pool->pool_token_value() * GetQuantity(pool->pool_token());
}
