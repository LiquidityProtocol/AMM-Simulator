#include <cassert>
#include <unordered_set>
#include <stdexcept>
#include "../Protocols/UniswapV2Pool.hpp"

int main() {
    Token *token1 = Token::GetToken("token1");
    Token *token2 = Token::GetToken("token2");
    Token *token3 = Token::GetToken("token3");

    UniswapV2Pool pool({{token1, 10}, {token2, 20}});

    assert(pool.InPool(token1));
    assert(!pool.InPool(token3));

    try {
        pool.GetQuantity(token3);
        assert(false);
    } catch (std::invalid_argument &e) {
        assert(std::string(e.what()) == "invalid token");
    }
    assert(pool.GetQuantity(token1) == 10);

    assert(pool.tokens() == std::unordered_set<Token *>({token1, token2}));

    try {
        pool.SimulateProvision({{token1, 1}, {token2, 1}});
        assert(false);
    } catch (std::invalid_argument &e) {
        assert(std::string(e.what()) == "invalid provision");
    }

    double generated_pool_token_quantity = pool.SimulateProvision({{token1, 1}, {token2, 2}});
    assert(generated_pool_token_quantity / (pool.total_pool_token_quantity() + generated_pool_token_quantity) == 1.0 / 11);
    
    Account *account = Account::GetAccount("Alice");
    account->Deposit(token1, 100);
    account->Deposit(token2, 100);

    try {
        account->Provide(&pool, {{token1, 101}, {token2, 202}});
        assert(false);
    } catch (std::invalid_argument &e) {
        assert(std::string(e.what()) == "not enough quantities in wallet");
    }

    generated_pool_token_quantity = account->Provide(&pool, {{token1, 50}, {token2, 100}});
    assert(generated_pool_token_quantity / pool.total_pool_token_quantity() == 50.0 / pool.GetQuantity(token1));
    assert(pool.GetQuantity(token1) == 60 && pool.GetQuantity(token2) == 120);
    assert(account->GetQuantity(pool.pool_token()) == generated_pool_token_quantity && account->GetQuantity(token1) == 50 && account->GetQuantity(token2) == 0);

    try {
        pool.SimulateWithdrawal(pool.total_pool_token_quantity() + 1);
        assert(false);
    } catch (std::invalid_argument &e) {
        assert(std::string(e.what()) == "too many pool tokens");
    }
    try {
        pool.SimulateWithdrawal(0);
        assert(false);
    } catch (std::invalid_argument &e) {
        assert(std::string(e.what()) == "invalid quantity");
    }

    auto output_quantities = pool.SimulateWithdrawal(pool.total_pool_token_quantity() / 6);
    assert(output_quantities[token1] == pool.GetQuantity(token1) / 6 && output_quantities[token2] == pool.GetQuantity(token2) / 6);

    try {
        account->Withdraw(&pool, account->GetQuantity(pool.pool_token()) + 0.1);
        assert(false);
    } catch (std::invalid_argument &e) {
        assert(std::string(e.what()) == "not enough quantities in wallet");
    }

    output_quantities = account->Withdraw(&pool, pool.total_pool_token_quantity() / 3);
    assert(output_quantities[token1] == 20 && output_quantities[token2] == 40);
    assert(pool.GetQuantity(token1) == 40 && pool.GetQuantity(token2) == 80);
    assert(account->GetQuantity(pool.pool_token()) == 3 && account->GetQuantity(token1) == 70 && account->GetQuantity(token2) == 40);

    try {
        pool.SimulateSwap(token1, token3, 10);
        assert(false);
    } catch (std::invalid_argument &e) {
        assert(std::string(e.what()) == "invalid token");
    }
    try {
        pool.SimulateSwap(token3, token1, 10);
        assert(false);
    } catch (std::invalid_argument &e) {
        assert(std::string(e.what()) == "invalid token");
    }
    assert(pool.SimulateSwap(token1, token2, 120) == 60);

    double output_quantity = account->Trade(&pool, token1, token2, 40);
    assert(output_quantity == 40);
    assert(pool.GetQuantity(token1) == 80 && pool.GetQuantity(token2) == 40);
    assert(account->GetQuantity(pool.pool_token()) == 3 && account->GetQuantity(token1) == 30 && account->GetQuantity(token2) == 80);

    for (auto op : pool.ledger()) {
        std::cout << *op;
    }

    return 0;
}