#include "Events.hpp"

Event::Event(PoolInterface *pool) {
    pool_ = pool;

    std::unordered_set<Token *> tokens = pool->tokens();

    if (tokens.size() > 2) {
        std::string protocolName = PROTOCOL_NAME.find(GetPoolType(pool)) -> second;
        throw std::invalid_argument("Specify input token and output token for " + protocolName);
    } else {
        Token *a = *tokens.begin();
        Token *b = *(++tokens.begin());

        if (pool->GetSpotPrice(a, b) > b->real_value() / a->real_value()) {
            std::swap(a, b);
        }
        // now b is under valued
        input_token_ = a;
        output_token_ = b;
    }
}

Event::Event(PoolInterface *pool, Token *input_token, Token *output_token) {
    if (pool->GetSpotPrice(input_token, output_token) > output_token->real_value() / input_token->real_value()) {
        throw std::invalid_argument("Creating ineffective signal");
    } else {
        pool_ = pool;
        input_token_ = input_token;
        output_token_ = output_token;
    }
}

Event *Event::next() const {
    return next_;
}
PoolInterface *Event::pool() const {
    return pool_;
}

Token *Event::input_token() const {
    return input_token_;
}
Token *Event::output_token() const {
    return output_token_;
}

double Event::simulate(double input_cash) const {
    double input_quantity = input_cash / input_token_->real_value();
    double output_quantity = pool_->SimulateSwap(input_token_, output_token_, input_quantity);

    return output_quantity * output_token_->real_value() - input_cash;
}

void Event::setNext(Event *e) {
    next_ = e;
}

TradeRoute::TradeRoute() = default;
TradeRoute::TradeRoute(Event *head, Event *tail) {
    if (head == nullptr) throw std::invalid_argument("Invalid input event");
    if (tail == nullptr) throw std::invalid_argument("Invalid output event");

    bool check = false;
    Event *node = head;

    for(len = 1 ; len <= 10 ; ++len) {
        if (node == tail) {
            check = true;
            break;
        } else if (node == nullptr) {
            throw std::invalid_argument("Invalid Trade Route");
        }
    }
    if (!check) {
        throw std::invalid_argument("Trade Route is too long");
    } else {
        head_ = head;
        tail_ = tail;
    }

}

TradeRoute::~TradeRoute() {
    while (head_) {
        Event *node = head_;
        head_ = node->next();

        delete node;
    }
}

size_t TradeRoute::size() const {
    return len;
}

Event *TradeRoute::head() const {
    return head_;
}
Event *TradeRoute::tail() const {
    return tail_;
}

double TradeRoute::simulate(double input_cash) const {
    double cashToForward = input_cash;

    for (Event *node = head_ ; node ; node = node->next()) {
        double profit = node->simulate(cashToForward);
        cashToForward += profit;
    }
    return cashToForward - input_cash;
}

Event *TradeRoute::tryAddEvent(PoolInterface *pool, Token *input_token, Token *output_token) {
    Event *e;
    if (input_token) {
        e = new Event(pool, input_token, output_token);
    } else {
        e = new Event(pool);
    }
    if (head_ && e->input_token() != tail_->output_token()) {
        throw std::invalid_argument("Pair does not match the trade route");
    }
    return e;
}

void TradeRoute::addEvent(PoolInterface *pool, Token *input_token, Token *output_token) {
    Event *e = tryAddEvent(pool, input_token, output_token);
    len++;

    if (head_) {
        tail_->setNext(e);
        tail_ = e;
    } else {
        head_ = tail_ = e;
    }
}
