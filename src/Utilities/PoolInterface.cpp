#include "Utilities.hpp"

PoolInterface::PoolInterface(std::unordered_set<Token *> tokens, double pool_fee)
    : tokens_container_(TokensContainer(tokens))
    , pool_fee_(pool_fee) {
    if (tokens.size() < 2) {
        throw std::invalid_argument("not enough tokens");
    }
    if (pool_fee < 0 || pool_fee > 1) {
        throw std::invalid_argument("invalid pool fee");
    }

    for (auto token : tokens) {
        quantities_[token] = 0;
    }
    quantities_[pool_token_ = new Token(this)] = 0;
}

bool PoolInterface::InPool(Token *token) const {
    /*
     * This method checks if a token is in the pool.
     *
     * @param token: a pointer to the token to check
     *
     * @return: true if the token is in the pool, false otherwise
     */
    return quantities_.count(token);
}

double PoolInterface::GetQuantity(Token *token) const {
    /*
     * This method returns the quantity of a token in the pool,
     * or an error if the token is not in the pool.
     *
     * @param token: a pointer to the token to check
     *
     * @return: the quantity of the token in the pool
     */
    return InPool(token) ? quantities_.find(token)->second : 0;
}

double PoolInterface::pool_fee() const {
    /*
     * This method returns the pool fee.
     *
     * @param none
     *
     * @return: the pool fee
     */
    return pool_fee_;
}

Token * PoolInterface::pool_token() const {
    /*
     * This method returns the pool token.
     *
     * @param none
     *
     * @return: the pool token
     */
    return pool_token_;
}

double PoolInterface::total_pool_token_quantity() const {
    /*
     * This method returns the total quantity of pool tokens in the pool.
     *
     * @param none
     *
     * @return: the total quantity of pool tokens in the pool
     */
    return GetQuantity(pool_token_);
}

std::unordered_set<Token *> PoolInterface::tokens() const {
    /*
     * This method returns the set of tokens in the pool.
     *
     * @param none
     *
     * @return: the set of tokens in the pool
     */
    std::unordered_set<Token *> tokens;
    for (auto token : tokens_container_.tokens()) {
        tokens.emplace(token);
    }
    return tokens;
}
std::unordered_map<Token *, double> PoolInterface::quantities() const {
    std::unordered_map<Token *, double> quantities;

    for (auto token : tokens()) {
        quantities[token] = GetQuantity(token);
    }
    return quantities;
}

double PoolInterface::SimulateSwap(Token *input_token, Token *output_token, double input_quantity) const {
    /*
     * This method simulates a swap of tokens in the pool.
     *
     * @param input_token: a pointer to the input token to swap
     * @param output_token: a pointer to the output token
     * @param input_quantity: the quantity of the input token to swap
     *
     * @return: the quantity of the output token that would be received if the swap were to occur
     */
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
    /*
     * This method swaps tokens in the pool.
     *
     * @param trader: a pointer to the account that is trading
     * @param input_token: a pointer to the input token to swap
     * @param output_token: a pointer to the output token
     * @param input_quantity: the quantity of the input token to swap
     *
     * @return: a pointer to the operation that was created
     */
    if (!CheckWallet(trader, {{input_token, input_quantity}})) {
        throw std::invalid_argument("not enough quantities in wallet");
    }
    double output_quantity = SimulateSwap(input_token, output_token, input_quantity);
    ExecuteSwap(trader, input_token, output_token, input_quantity, output_quantity);
    ledger_.emplace_back(new Operation("TRADE", trader->name(), this, {{input_token, input_quantity}}, {{output_token, output_quantity}}));
    return ledger_.back();
}

double PoolInterface::SimulateProvision(std::unordered_map<Token *, double> input_quantities) const {
    /*
     * This method simulates the provision of liquidity to the pool.
     *
     * @param input_quantities: a map of token pointers to quantities of each token to provide
     *
     * @return: the quantity of pool tokens that would be received if the provision were to occur
     */
    if (!total_pool_token_quantity()) {
        return INITIAL_POOL_TOKEN_SUPPLY;
    }
    if (!ValidProvision(input_quantities)) {
        throw std::invalid_argument("invalid provision");
    }
    Token* reference_token = *tokens().begin();
    double generated_pool_token_quantity = total_pool_token_quantity() / (GetQuantity(reference_token) / input_quantities[reference_token]);
    return generated_pool_token_quantity;
}

Operation * PoolInterface::Provide(Account *provider, std::unordered_map<Token *, double> input_quantities) {
    /*
     * This method provides liquidity to the pool.
     *
     * @param provider: a pointer to the account that is providing liquidity
     * @param input_quantities: a map of token pointers to quantities of each token to provide
     *
     * @return: a pointer to the operation that was created
     */
    if (!CheckWallet(provider, input_quantities)) {
        throw std::invalid_argument("not enough quantities in wallet");
    }
    double generated_pool_token_quantity = SimulateProvision(input_quantities);
    ExecuteProvision(provider, input_quantities, generated_pool_token_quantity);
    ledger_.emplace_back(new Operation("PROVIDE", provider->name(), this, input_quantities, {{pool_token(), generated_pool_token_quantity}}));
    return ledger_.back();
}

std::unordered_map<Token *, double> PoolInterface::SimulateWithdrawal(double surrendered_pool_token_quantity) const {
    /*
     * This method simulates the withdrawal of liquidity from the pool.
     *
     * @param surrendered_pool_token_quantity: the quantity of pool tokens to withdraw
     *
     * @return: a map of token pointers to quantities of each token that would be received if the withdrawal were to occur
     */
    if (surrendered_pool_token_quantity > GetQuantity(pool_token_)) {
        throw std::invalid_argument("too many pool tokens");
    } else if (surrendered_pool_token_quantity <= 0) {
        throw std::invalid_argument("invalid quantity");
    }
    std::unordered_map<Token *, double> output_quantities;
    double ratio = surrendered_pool_token_quantity / total_pool_token_quantity();
    for (auto token : tokens()) {
        output_quantities[token] = GetQuantity(token) * ratio;
    }
    return output_quantities;
}

Operation * PoolInterface::Withdraw(Account *provider, double surrendered_pool_token_quantity) {
    /*
     * This method withdraws liquidity from the pool.
     *
     * @param provider: a pointer to the account that is withdrawing liquidity
     * @param surrendered_pool_token_quantity: the quantity of pool tokens to withdraw
     *
     * @return: a pointer to the operation that was created
     */
    if (!CheckWallet(provider, {{pool_token_, surrendered_pool_token_quantity}})) {
        throw std::invalid_argument("not enough quantities in wallet");
    }
    std::unordered_map<Token *, double> output_quantities = SimulateWithdrawal(surrendered_pool_token_quantity);
    ExecuteWithdrawal(provider, surrendered_pool_token_quantity, output_quantities);
    ledger_.emplace_back(new Operation("WITHDRAW", provider->name(), this, {{pool_token(), surrendered_pool_token_quantity}}, output_quantities));
    return ledger_.back();
}

double PoolInterface::GetSlippage(Token *input_token, Token *output_token, double input_quantity) const {
    /*
     * This method computes the slippage of a swap.
     *
     * @param input_token: a pointer to the input token to swap
     * @param output_token: a pointer to the output token
     * @param input_quantity: the quantity of the input token to swap
     *
     * @return: the slippage of the swap
     */
    if (!InPool(input_token) || !InPool(output_token)) {
        throw std::invalid_argument("invalid token");
    } else if (input_quantity <= 0) {
        throw std::invalid_argument("invalid quantity");
    } else {
        return ComputeSlippage(input_token, output_token, input_quantity);
    }
}

double PoolInterface::GetSpotPrice(Token *input_token, Token *output_token) const {
    if (!InPool(input_token) || !InPool(output_token)) {
        throw std::invalid_argument("invalid token");
    } else {
        return ComputeSpotExchangeRate(input_token, output_token);
    }
}

std::vector<Operation *> PoolInterface::ledger() const {
    /*
     * This method returns the ledger of the pool.
     *
     * @return: the ledger of the pool
     */
    return ledger_;
}

double PoolInterface::ComputeSpotExchangeRate(Token *input_token, Token *output_token) const {
    /*
     * This method computes the spot exchange rate of a swap.
     *
     * @param input_token: a pointer to the input token to swap
     * @param output_token: a pointer to the output token
     *
     * @return: the spot exchange rate of the swap
     */
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
    /*
     * This method computes the slippage of a swap.
     *
     * @param input_token: a pointer to the input token to swap
     * @param output_token: a pointer to the output token
     * @param input_quantity: the quantity of the input token to swap
     *
     * @return: the slippage of the swap
     */
    double output_quantity = ComputeSwappedQuantity(input_token, output_token, input_quantity);
    double exchange_rate = ComputeSpotExchangeRate(input_token, output_token);

    return input_quantity / output_quantity / exchange_rate - 1;
}

bool PoolInterface::CheckWallet(Account *account, const std::unordered_map<Token *, double> &quantities) const {
    /*
     * This method checks if an account has enough quantities of tokens in its wallet.
     *
     * @param account: a pointer to the account
     * @param quantities: a map of token pointers to quantities of each token
     *
     * @return: true if the account has enough quantities of tokens in its wallet, false otherwise
     */
    for (auto [token, quantity] : quantities) {
        if (account->GetQuantity(token) < quantity) {
            return false;
        }
    }
    return true;
}

void PoolInterface::UpdateWallet(Account *account, Token *token, double quantity) const {
    account->wallet_[token] += quantity;
    account->total_value_ += quantity * token->real_value();
}

void PoolInterface::ExecuteSwap(Account *trader, Token *input_token, Token *output_token, double input_quantity, double output_quantity) {
    /*
     * This method executes a swap.
     *
     * @param trader: a pointer to the account that is trading
     * @param input_token: a pointer to the input token to swap
     * @param output_token: a pointer to the output token
     * @param input_quantity: the quantity of the input token to swap
     * @param output_quantity: the quantity of the output token to receive
     *
     * @return: none
     */
    if (GetQuantity(output_token) <= output_quantity) {
        throw std::invalid_argument("not enough liquidity");
    }
    
    quantities_[input_token] += input_quantity;
    UpdateWallet(trader, input_token, -input_quantity);
    quantities_[output_token] -= output_quantity;
    UpdateWallet(trader, output_token, output_quantity);
}

bool PoolInterface::ValidProvision(std::unordered_map<Token *, double> quantities) const {
    /*
     * This method checks if a provision is valid.
     *
     * @param quantities: a map of token pointers to quantities of each token
     *
     * @return: true if the provision is valid, false otherwise
     */
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
    /*
     * This method executes a provision. This method is called by the Provision method;
     * it is not meant to be called by the user.
     * To provide liquidity to a pool, use the Provision method (see above).
     *
     * @param provider: a pointer to the account that is providing
     * @param input_quantities: a map of token pointers to quantities of each token
     * @param generated_pool_token_quantity: the quantity of pool tokens to generate
     *
     * @return: none
     */
    for (auto [token, quantity] : input_quantities) {
        quantities_[token] += quantity;
        UpdateWallet(provider, token, -quantity);
    }
    quantities_[pool_token_] += generated_pool_token_quantity;
    UpdateWallet(provider, pool_token_, generated_pool_token_quantity);
}

void PoolInterface::ExecuteWithdrawal(Account *provider, double surrendered_pool_token_quantity, std::unordered_map<Token *, double> output_quantities) {
    /*
     * This method executes a withdrawal. This method is called by the Withdraw method;
     * it is not meant to be called by the user.
     * To withdraw liquidity from a pool, use the Withdraw method (see above)
     *
     * @param provider: a pointer to the account that is withdrawing
     * @param surrendered_pool_token_quantity: the quantity of pool tokens to surrender
     * @param output_quantities: a map of token pointers to quantities of each token
     *
     * @return: none
     */
    for (auto [token, quantity] : output_quantities) {
        quantities_[token] -= quantity;
        UpdateWallet(provider, token, quantity);
    }
    quantities_[pool_token_] -= surrendered_pool_token_quantity;
    UpdateWallet(provider, pool_token_, -surrendered_pool_token_quantity);
}
