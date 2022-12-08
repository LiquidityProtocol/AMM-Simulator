#include "Utilities.hpp"

Operation::Operation(const std::string &operation_type,
                     const std::string &account_name,
                     PoolInterface *pool,
                     std::unordered_map<Token *, double> input,
                     std::unordered_map<Token *, double> output) {
    /*
        * Constructor for the Operation class.
        *
        * @param operation_type: Type of the operation.
        * @param account_name: Name of the account.
        * @param pool: Pointer to the pool.
        * @param input: Input of the operation.
        * @param output: Output of the operation.
        * 
        * @return: None.
    */
    operation_type_ = operation_type;
    account_name_ = account_name;
    pool_ = pool;
    input_ = input;
    output_ = output;
};

std::string Operation::operation_type() const {
    /*
        * Getter for the operation type.
        *
        * @param: None.
        * 
        * @return: Operation type.
    */
    return operation_type_;
}

std::string Operation::account_name() const {
    /*
        * Getter for the account name.
        *
        * @param: None.
        * 
        * @return: Account name.
    */
    return account_name_;
}

std::unordered_map<Token *, double> Operation::input() const {
    /*
        * Getter for the input.
        *
        * @param: None.
        *  
        * @return: Input.
    */
    return input_;
}

std::unordered_map<Token *, double> Operation::output() const {
    /*
        * Getter for the output.
        *
        * @param: None.
        * 
        * @return: Output.
    */
    return output_;
}

std::ostream & operator<<(std::ostream &os, const Operation &op)  {
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
    return  os;
}