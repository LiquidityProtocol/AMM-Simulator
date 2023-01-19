#include "SignalsHandler.hpp"

SignalsHandler::SignalsHandler() = default;
SignalsHandler::~SignalsHandler() {
    respondSignals();
}

void SignalsHandler::requestSignal(Account *sender, Signal msg) {
    SignalQueue.push(std::make_pair(sender, msg));
}

void SignalsHandler::respondSignals() {
    while (SignalQueue.size()) {
        Account *sender = SignalQueue.front().first;
        Signal msg = SignalQueue.front().second;
        double quantity = msg.quantity();

        SignalQueue.pop();

        while (true) {
            try {
                sender->Trade(msg.pool(),
                            msg.input_token(),
                            msg.output_token(),
                            quantity);
                break;
            } catch (...) {
                quantity *= 0.9;
            }
        }
    }
}
