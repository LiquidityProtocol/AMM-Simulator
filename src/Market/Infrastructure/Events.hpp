#ifndef EVENTS_H
#define EVENTS_H

#include "../../Utilities/Utilities.hpp"
#include "../../Protocols/Protocols.hpp"

class Signal {
public:
    Signal(PoolInterface* pool);
    Signal(PoolInterface* pool, Token *input_token, Token *output_token);

    Signal *next() const;
    PoolInterface *pool() const;
    Token *input_token() const;
    Token *output_token() const;

    double simulate(double input_cash) const;
    void setNext(Signal *e);
private:
    Signal *next_ = nullptr;

    PoolInterface *pool_;
    Token *input_token_;
    Token *output_token_;
};

class TradeRoute {
public:
    TradeRoute(Signal *head, Signal *tail);
    TradeRoute();
    ~TradeRoute();

    size_t size() const;
    Signal *head() const;
    Signal *tail() const;

    double simulate(double input_cash) const;
private:
    Signal *tryAddSignal(PoolInterface *pool, Token *input_token = nullptr, Token *output_token = nullptr);
    void addSignal(PoolInterface *pool, Token *input_token = nullptr, Token *output_token = nullptr);

    Signal *head_ = nullptr;
    Signal *tail_ = nullptr;
    size_t len = 0;
};

#endif // EVENTS_H
