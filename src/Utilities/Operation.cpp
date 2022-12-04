#include "Utilities.hpp"
#include <iostream>

using namespace std;

Operation::Operation(const std::string &type, std::string account, PoolInterface * pool, std::unordered_map<Token *, double> input, std::unordered_map<Token *, double> output) {
        operation_type_ = type;
        account_ = account;
        pool_ = pool;
        input_ = input;
        output_ = output;
    };

void Operation::Print() {
        cout << "OPERATION " << to_string(reinterpret_cast<uint64_t>(this)) << ":\n";
        cout << ">>> TYPE: " << operation_type_ << "\n";
        cout << ">>> ACCOUNT: " << account_ << "\n";
        cout << ">>> POOL: " << pool_ << "\n";
        cout << ">>> INPUT: ";
        for (auto [token, quantity]: input_){
            cout << token->name() << ": " << std::to_string(quantity) << "; ";
        }
        cout << "\n";
        cout << ">>> OUTPUT: ";
        for (auto [token, quantity]: output_){
            cout << token->name() << ": " << std::to_string(quantity) << "; ";
        }
        cout << "\n";
    };