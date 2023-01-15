#include "StrategyHeader.hpp"

void Arbitrager::sell(Token *token, double quantity) {
    if (GetQuantity(token) < quantity) {
        throw std::invalid_argument("Not enough token to sell");
    } else {
        Deposit(token, -quantity);
    }
}

void Arbitrager::buy(Token *token, double quantity) {
    if (total_value() < token->real_value() * quantity) {
        throw std::invalid_argument("Not enough cash to buy token");
    } else {
        Deposit(token, quantity);
    }
}

double Arbitrager::ExecuteSignal(Event *event, double input_quantity) {
    return Trade(event->pool(), event->input_token(), event->output_token(), input_quantity);
}
double Arbitrager::ExecuteTradeRoute(TradeRoute *route, double input_quantity) {
    for (Event *node = route->head() ; node ; node = node->next())
        input_quantity = ExecuteSignal(node, input_quantity);

    return input_quantity;
}

void Arbitrager::ExecuteStrategy() {

}
