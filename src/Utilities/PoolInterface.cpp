#include "Utilities.hpp"

PoolInterface::PoolInterface(std::unordered_map<Token *, double> quantities, double pool_fee) : quantities_(quantities) {
    if (quantities.size() < 2) {
        throw std::invalid_argument("not enough tokens");
    }
    if (pool_fee < 0 || pool_fee > 1) {
        throw std::invalid_argument("invalid pool fee");
    } else {
        pool_fee_ = pool_fee;
    }
    pool_token_ = Token::GetToken("PoolToken" + std::to_string(reinterpret_cast<uint64_t>(this)));
    quantities_[pool_token_] = 1;
}

bool PoolInterface::InPool(Token *token) const {
    return quantities_.count(token);
}

double PoolInterface::GetQuantity(Token *token) const {
    if (!InPool(token)) {
        throw std::invalid_argument("invalid token");
    }
    return quantities_.find(token)->second;
}

double PoolInterface::pool_fee() const {
    return pool_fee_;
}

Token * PoolInterface::pool_token() const {
    return pool_token_;
}

double PoolInterface::total_pool_token_quantity() const {
    return GetQuantity(pool_token_);
}

std::unordered_set<Token *> PoolInterface::tokens() const {
    std::unordered_set<Token *> tokens;
    tokens.reserve(quantities_.size());
    for (auto [token, quantity] : quantities_) {
        if (token != pool_token_) {
            tokens.emplace(token);
        }
    }
    return tokens;
}

double PoolInterface::SimulateSwap(Token *input_token, Token *output_token, double input_quantity) const {
    if (!InPool(input_token) || !InPool(output_token)) {
        throw std::invalid_argument("invalid token");
    } else if (input_quantity <= 0) {
        throw std::invalid_argument("invalid quantity");
    } else {
        double fee_quantity = input_quantity * pool_fee();
        double output_quantity = ComputeSwappedQuantity(input_token, output_token, input_quantity - fee_quantity);
        return output_quantity;
    }
}

Operation * PoolInterface::Swap(Account *trader, Token *input_token, Token *output_token, double input_quantity) {
    if (!CheckWallet(trader, {{input_token, input_quantity}})) {
        throw std::invalid_argument("not enough quantities in wallet");
    }
    double output_quantity = SimulateSwap(input_token, output_token, input_quantity);
    ExecuteSwap(trader, input_token, output_token, input_quantity, output_quantity);
    ledger_.emplace_back(new Operation("TRADE", trader->name(), this, {{input_token, input_quantity}}, {{output_token, output_quantity}}));
    return ledger_.back();
}

double PoolInterface::SimulateProvision(std::unordered_map<Token *, double> input_quantities) const {
    if (!ValidProvision(input_quantities)) {
        throw std::invalid_argument("invalid provision");
    }
    Token* reference_token = *tokens().begin();
    double generated_pool_token_quantity = total_pool_token_quantity() / (GetQuantity(reference_token) / input_quantities[reference_token]);
    return generated_pool_token_quantity;
}

Operation * PoolInterface::Provide(Account *provider, std::unordered_map<Token *, double> input_quantities) {
    if (!CheckWallet(provider, input_quantities)) {
        throw std::invalid_argument("not enough quantities in wallet");
    }
    double generated_pool_token_quantity = SimulateProvision(input_quantities);
    ExecuteProvision(provider, input_quantities, generated_pool_token_quantity);
    ledger_.emplace_back(new Operation("PROVIDE", provider->name(), this, input_quantities, {{pool_token(), generated_pool_token_quantity}}));
    return ledger_.back();
}

std::unordered_map<Token *, double> PoolInterface::SimulateWithdrawal(double surrendered_pool_token_quantity) const {
    if (surrendered_pool_token_quantity > GetQuantity(pool_token_)) {
        throw std::invalid_argument("too many pool tokens");
    } else if (surrendered_pool_token_quantity <= 0) {
        throw std::invalid_argument("invalid quantity");
    }
    std::unordered_map<Token *, double> output_quantities;
    double ratio = surrendered_pool_token_quantity / GetQuantity(pool_token_);
    for (auto token : tokens()) {
        output_quantities[token] = GetQuantity(token) * ratio;
    }
    return output_quantities;
}

Operation * PoolInterface::Withdraw(Account *provider, double surrendered_pool_token_quantity) {
    if (!CheckWallet(provider, {{pool_token_, surrendered_pool_token_quantity}})) {
        throw std::invalid_argument("not enough quantities in wallet");
    }
    std::unordered_map<Token *, double> output_quantities = SimulateWithdrawal(surrendered_pool_token_quantity);
    ExecuteWithdrawal(provider, surrendered_pool_token_quantity, output_quantities);
    ledger_.emplace_back(new Operation("WITHDRAW", provider->name(), this, {{pool_token(), surrendered_pool_token_quantity}}, output_quantities));
    return ledger_.back();
}

double PoolInterface::GetSlippage(Token *input_token, Token *output_token, double input_quantity) const {
    if (!InPool(input_token) || !InPool(output_token)) {
        throw std::invalid_argument("invalid token");
    } else if (input_quantity <= 0) {
        throw std::invalid_argument("invalid quantity");
    } else {
        return ComputeSlippage(input_token, output_token, input_quantity);
    }
}

std::vector<Operation *> PoolInterface::ledger() const {
    return ledger_;
}

double PoolInterface::ComputeSpotExchangeRate(Token *input_token, Token *output_token) const {
    std::unordered_map<Token *, double> clone_quantities;
    for (auto token : tokens()) {
        clone_quantities[token] = GetQuantity(token);
    }
    
    auto df = [&](Token *token) {
        static const double eps = 1e-6;
        clone_quantities[token] -= eps;         double val1 = ComputeInvariant(clone_quantities);
        clone_quantities[token] += 2 * eps;     double val2 = ComputeInvariant(clone_quantities);

        return (val2 - val1) / (2 * eps);
    };
    return df(input_token) / df(output_token);
}

double PoolInterface::ComputeSlippage(Token *input_token, Token *output_token, double input_quantity) const {
    double output_quantity = ComputeSwappedQuantity(input_token, output_token, input_quantity);
    double exchange_rate = ComputeSpotExchangeRate(input_token, output_token);

    return input_quantity / output_quantity / exchange_rate - 1;
}

bool PoolInterface::CheckWallet(Account *account, const std::unordered_map<Token *, double> &quantities) const {
    for (auto [token, quantity] : quantities) {
        if (account->GetQuantity(token) < quantity) {
            return false;
        }
    }
    return true;
}

void PoolInterface::ExecuteSwap(Account *trader, Token *input_token, Token *output_token, double input_quantity, double output_quantity) {
    if (GetQuantity(output_token) <= output_quantity) {
        throw std::invalid_argument("not enough liquidity");
    }
    
    quantities_[input_token] += input_quantity;
    trader->Deposit(input_token, -input_quantity);
    quantities_[output_token] -= output_quantity;
    trader->Deposit(output_token, output_quantity);
}

bool PoolInterface::ValidProvision(std::unordered_map<Token *, double> quantities) const {
    double reference_ratio = -1;
    for (auto token : tokens()) {
        if (quantities[token] <= 0) {
            return false;
        }
        if (reference_ratio == -1) {
            reference_ratio = GetQuantity(token) / quantities[token];
        } else {
            if (GetQuantity(token) / quantities[token] != reference_ratio) {
                return false;
            }
        }
    }
    return true;
}

void PoolInterface::ExecuteProvision(Account *provider, std::unordered_map<Token *, double> input_quantities, double generated_pool_token_quantity) {
    for (auto [token, quantity] : input_quantities) {
        quantities_[token] += quantity;
        provider->Deposit(token, -quantity);
    }
    quantities_[pool_token_] += generated_pool_token_quantity;
    provider->Deposit(pool_token_, generated_pool_token_quantity);
}

void PoolInterface::ExecuteWithdrawal(Account *provider, double surrendered_pool_token_quantity, std::unordered_map<Token *, double> output_quantities) {
    for (auto [token, quantity] : output_quantities) {
        quantities_[token] -= quantity;
        provider->Deposit(token, quantity);
    }
    quantities_[pool_token_] -= surrendered_pool_token_quantity;
    provider->Deposit(pool_token_, -surrendered_pool_token_quantity);
}