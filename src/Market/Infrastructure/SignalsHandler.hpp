#ifndef SIGNALSHANDLER_HPP
#define SIGNALSHANDLER_HPP

#include "Signals.hpp"
#include <queue>

class SignalsHandler {
public:
    SignalsHandler();
    ~SignalsHandler();

    void requestSignal(Account *sender, Signal msg);
    void respondSignals();
private:
    std::queue<std::pair<Account*, Signal> > SignalQueue;
};

#endif // SIGNALSHANDLER_HPP
