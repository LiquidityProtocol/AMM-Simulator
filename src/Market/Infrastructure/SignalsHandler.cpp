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

        PoolInterface *pool = msg.pool();
        Token *input_token = msg.input_token();
        Token *output_token = msg.output_token();

        double quantity = msg.quantity();

        SignalQueue.pop();

        while (sender->GetQuantity(input_token) < quantity)
            quantity *= 0.95;

        sender->Trade(pool, input_token, output_token, quantity);
    }
}
