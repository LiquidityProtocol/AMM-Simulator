#ifndef PROVIDER_HPP
#define PROVIDER_HPP

#include "../../Utilities/Utilities.hpp"

class Provider : public Account {
public:
    Provider(const std::string name, double budget);

    void StrategicProvide(PoolInterface *pool);

    QVector<double> calcHoldValue(PoolInterface *pool) const;
    double calcShareValue(PoolInterface *pool) const;

    void endEpoch();
private:

    std::vector<std::unordered_map<PoolInterface *, std::unordered_map<Token *, double> > > provideHistory;
    std::vector<std::unordered_map<PoolInterface *, double> > benefitHistory;
};

#endif // PROVIDER_HPP
