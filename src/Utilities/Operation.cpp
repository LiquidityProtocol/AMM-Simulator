#include "Utilities.hpp"

Operation::Operation(
    const std::string &operation_type,
    const std::string &account_name,
    PoolInterface *pool,
    const std::unordered_map<Token *, double> &input,
    const std::unordered_map<Token *, double> &output
) : operation_type_(operation_type)
  , account_name_(account_name)
  , pool_(pool)
  , input_(input)
  , output_(output) {
    quantities_ = pool->quantities();

    for (Token *a : pool->tokens())
        market_price_[a] = a->real_value();

    for (Token *a : pool->tokens())
    for (Token *b : pool->tokens())
        spotPriceMatrix[a][b] = pool->GetSpotPrice(a, b);
}

std::string Operation::operation_type() const {
    return operation_type_;
}

std::string Operation::account_name() const {
    return account_name_;
}

PoolInterface *Operation::pool() const {
    return pool_;
}

std::unordered_map<Token *, double> Operation::input() const {
    return input_;
}

std::unordered_map<Token *, double> Operation::output() const {
    return output_;
}

double Operation::GetMarketPrice(Token *a) const {
    return (market_price_.find(a)->second);
}

double Operation::GetSpotPrice(Token *a, Token *b) const {
    if (!pool_->InPool(a) || !pool_->InPool(b))
        throw std::invalid_argument("Pool does not support this pair");
    return (spotPriceMatrix.find(a)->second).find(b)->second;
}

double Operation::GetQuanitty(Token *a) const {
    return quantities_.find(a)->second;
}

double Operation::GetVolume(Token *a) const {
    return GetMarketPrice(a) * GetQuanitty(a);
}

std::ostream & operator<<(std::ostream &os, const Operation &op) {
    /*
        * Overload of the << operator for the Operation class.
        *
        * @param os: Output stream.
        * @param op: Operation.
        * 
        * @return: Output stream.
    */

    os << "OPERATION " << std::to_string(reinterpret_cast<uint64_t>(&op)) << ":\n";
    os << ">>> TYPE: " << op.operation_type_ << "\n";
    os << ">>> ACCOUNT: " << op.account_name_ << "\n";
    os << ">>> POOL: " << op.pool_ << "\n";
    os << ">>> INPUT: ";

    for(auto [token, quantity] : op.input_)
        os << token->name() << ": " << quantity << "; ";
    
    os << "\n";
    os << ">>> OUTPUT: ";
    for (auto [token, quantity]: op.output_)
        os << token->name() << ": " << quantity << "; ";
    
    os << "\n\n";
    return os;
}
