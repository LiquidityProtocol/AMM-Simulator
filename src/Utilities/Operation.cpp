#include "Utilities.hpp"
#include <iostream>

using namespace std;

Operation::Operation(const std::string &type,
                     const std::string &account,
                     PoolInterface * pool,
                     std::unordered_map<Token *, double> input,
                     std::unordered_map<Token *, double> output) {
    operation_type_ = type;
    account_ = account;
    pool_ = pool;
    input_ = input;
    output_ = output;
};

std::ostream& operator << (std::ostream& os, const Operation& ops)  {
    os << "OPERATION " << to_string(reinterpret_cast<uint64_t>(&ops)) << ":\n";
    os << ">>> TYPE: " << ops.operation_type_ << "\n";
    os << ">>> ACCOUNT: " << ops.account_ << "\n";
    os << ">>> POOL: " << ops.pool_ << "\n";
    os << ">>> INPUT: ";

    for(auto [token, quantity] : ops.input_)
        os << token->name() << ": " << quantity << "; ";
    
    os << "\n";
    os << ">>> OUTPUT: ";
    for (auto [token, quantity]: ops.output_)
        os << token->name() << ": " << quantity << "; ";
    
    os << "\n\n";
    return  os;
}