#include "Simulation.hpp"
#include <iostream>


std::normal_distribution<double> Simulation::distribution = std::normal_distribution<double>(0.0, 1.0);
std::default_random_engine Simulation::generator = std::default_random_engine();

ActionInfo::ActionInfo(Action type, PoolInterface *pool, double x) : type_(type) {
    double poolValue = 0;
    for (auto token : pool->tokens()) {
        poolValue += pool->GetQuantity(token) * token->real_value();
    }
    poolShareValue_ = poolValue / pool->GetQuantity(pool->pool_token());

    for (auto token1 : pool->tokens())
    for (auto token2 : pool->tokens())
        spotPriceMat[token1][token2] = pool->GetSpotPrice(token1, token2);
    
    if (type == TRADE) {
        slippage_ = x;
    } else {
        receivedPoolTokens_ = x;
    }
}
Action ActionInfo::getType() const {
    return type_;
}
double ActionInfo::getSlippage() const {
    return type_ == TRADE ? slippage_ : -1;
}
double ActionInfo::cntPoolToken() const {
    return type_ == PROVIDE ? receivedPoolTokens_ : -1;
}

double ActionInfo::getPoolShareValue() const {
    return poolShareValue_;
}
double ActionInfo::getSpotPrice(Token *a, Token *b) const {
    return (spotPriceMat.find(a)->second).find(b)->second;
}

size_t ActionHistory::size() {
    return history_.size();
}
void ActionHistory::addEvent(ActionInfo event) {
    history_.push_back(event);
}
ActionInfo ActionHistory::operator[](int i) const {
    return history_[i];
}

Simulation::Simulation(Playground *playground, std::pair< PROTOCOL, std::unordered_set<Token*> > pool_info, int nArbs, int nEpochs) {
    nEpochs_ = nEpochs;
    nArbs_ = nArbs;
    epoch = 0;
    playground_ = playground;
    pool_info_ = pool_info;
    pool_ = playground_->GetPool(pool_info.first, pool_info.second);

    simulationTrader = playground_->GetAccount("Simulation Trader").first;
    simulationProvider = playground_->GetAccount("Simulation Provider").first;

    for (auto token : pool_->tokens()) {
        simulationTrader->Deposit(token, 100000);
        simulationProvider->Deposit(token, 100000);
    }
    
    poolType_ = getPoolType(pool_);
}
void Simulation::runEpoch() {
    if (converged_) {
        throw std::invalid_argument("Price converged");
    }
    ++epoch;
    Token *input_token;
    Token *output_token;
    double input_quantity;

    double best_profit = -1;

    for (auto token1 : pool_->tokens())
    for (auto token2 : pool_->tokens()) {
        double quantity = calcOptimalAmount(token1, token2);    // try swap token1 to get token2
        if (quantity > 0) {
            // std::cerr << "Combi found a profit pair!!!\n";
            // std::cerr << token1->name() << "\n";
            // std::cerr << token2->name() << "\n";
            double output_quantity = playground_->SimulateSwap(pool_, token1, token2, quantity);
            double current_profit = output_quantity * token2->real_value() - quantity * token1->real_value();

            // std::cerr << current_profit <<"\n";

            if (best_profit < current_profit) {
                best_profit = current_profit;

                input_token = token1;
                output_token = token2;

                input_quantity = quantity;
                // std::cerr << "Hey best traded pair updated\n";
            }
        }
    }
    if (best_profit > 0) {
        std::cerr << "Epoch " << epoch << ": Combi is tradinggg!!!\n";
        double sample = distribution(generator) * nArbs_ * 0.01;
        double slippage = pool_->GetSlippage(input_token, output_token, input_quantity * (1 + sample));

        playground_->ExecuteSwap(simulationTrader, pool_, input_token, output_token, input_quantity * (1 + sample));
        history_.addEvent(ActionInfo(TRADE, pool_, slippage));
    } else {
        converged_ = true;
        std::cerr << "Epoch " << epoch << ": Price Converged\n";
    }
}
void Simulation::Provide(double expectedPoolTokenQuantity) {
    std::unordered_map<Token *, double> quantities;

    for (auto token : pool_->tokens()) {
        double quantity = pool_->GetQuantity(token);
        
        quantity /= pool_->GetQuantity(pool_->pool_token());
        quantity *= expectedPoolTokenQuantity;

        quantities[token] = quantity;
    }
    playground_->ExecuteProvision(simulationProvider, pool_info_.first, quantities);
    history_.addEvent(ActionInfo(PROVIDE, pool_, expectedPoolTokenQuantity));
}
ActionHistory Simulation::getHistory() {
    return history_;
}

double Simulation::calcOptimalAmount(Token *input_token, Token *output_token) {
    assert(pool_->tokens().find(input_token) != pool_->tokens().end());
    assert(pool_->tokens().find(output_token) != pool_->tokens().end());

    double spotPoolPrice = pool_->GetSpotPrice(input_token, output_token);
    double spotMarketPrice = output_token->real_value() / input_token->real_value();

    if (spotPoolPrice > spotMarketPrice) {
        return 0;
    } else {
        // this formula is exact for UniSwapV2 Pool
        double val1 = input_token->real_value() * pool_->GetQuantity(input_token);
        double val2 = output_token->real_value() * pool_->GetQuantity(output_token);

        double balanceQuantity1 = sqrt(val1 * val2) / input_token->real_value();
        return balanceQuantity1 - pool_->GetQuantity(input_token);
    }
}