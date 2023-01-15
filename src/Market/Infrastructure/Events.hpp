#ifndef EVENTS_H
#define EVENTS_H

#include "../../Utilities/Utilities.hpp"
#include "../../Protocols/Protocols.hpp"

class Event {
public:
    Event(PoolInterface* pool);
    Event(PoolInterface* pool, Token *input_token, Token *output_token);

    Event *next() const;
    PoolInterface *pool() const;
    Token *input_token() const;
    Token *output_token() const;

    double simulate(double input_cash) const;
    void setNext(Event *e);
private:
    Event *next_ = nullptr;

    PoolInterface *pool_;
    Token *input_token_;
    Token *output_token_;
};

class TradeRoute {
public:
    TradeRoute(Event *head, Event *tail);
    TradeRoute();
    ~TradeRoute();

    size_t size() const;
    Event *head() const;
    Event *tail() const;

    double simulate(double input_cash) const;
private:
    Event *tryAddEvent(PoolInterface *pool, Token *input_token = nullptr, Token *output_token = nullptr);
    void addEvent(PoolInterface *pool, Token *input_token = nullptr, Token *output_token = nullptr);

    Event *head_ = nullptr;
    Event *tail_ = nullptr;
    size_t len = 0;
};

#endif // EVENTS_H
