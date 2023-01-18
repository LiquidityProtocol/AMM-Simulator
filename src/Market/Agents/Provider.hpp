#ifndef PROVIDER_HPP
#define PROVIDER_HPP

#include "../../Utilities/Utilities.hpp"

class Provider : public Account {
public:
    Provider(const std::string name, double budget);
private:
    double budget_;
};

#endif // PROVIDER_HPP
