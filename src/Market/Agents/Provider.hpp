#ifndef PROVIDER_HPP
#define PROVIDER_HPP

#include "../../Utilities/Utilities.hpp"

class Provider : public Account {
public:
    Provider(const std::string name, double budget);

    void StrategicProvide(PoolInterface *pool);

    void calcHoldValue(PoolInterface *pool, std::vector<double> &vals) const;
    void calcShareValue(PoolInterface *pool, double &val) const;

    void endEpoch();
private:

    std::vector<std::unordered_map<PoolInterface *, std::unordered_map<Token *, double> > > provideHistory;
    std::vector<std::unordered_map<PoolInterface *, double> > benefitHistory;
};

#endif // PROVIDER_HPP
