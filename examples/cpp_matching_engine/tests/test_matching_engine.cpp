#include "matching_engine/matching_engine.hpp"

#include <algorithm>
#include <functional>
#include <iostream>
#include <limits>
#include <random>
#include <stdexcept>
#include <string>
#include <utility>
#include <variant>
#include <vector>

namespace vm = vnpy::matching;

namespace {

void require(bool condition, const char *expression, int line) {
    if (!condition) {
        throw std::runtime_error("line " + std::to_string(line) +
                                 ": requirement failed: " + expression);
    }
}

#define REQUIRE(expression) require(static_cast<bool>(expression), #expression, __LINE__)

std::vector<vm::Trade> trades(const vm::EventBuffer &events) {
    std::vector<vm::Trade> result;
    for (const vm::Event &event : events) {
        if (const auto *trade = std::get_if<vm::Trade>(&event)) {
            result.push_back(*trade);
        }
    }
    return result;
}

template <typename T> const T *find_event(const vm::EventBuffer &events) {
    for (const vm::Event &event : events) {
        if (const auto *value = std::get_if<T>(&event)) {
            return value;
        }
    }
    return nullptr;
}

void require_valid(const vm::MatchingEngine &engine) {
    std::string error;
    REQUIRE(engine.check_invariants(&error));
    REQUIRE(error.empty());
}

void submit_ignored(vm::MatchingEngine &engine, const vm::NewOrder &order) {
    vm::EventBuffer events;
    engine.submit(order, events);
}

void cancel_ignored(vm::MatchingEngine &engine, vm::OrderId order_id) {
    vm::EventBuffer events;
    engine.cancel(order_id, events);
}

void limit_order_rests() {
    vm::MatchingEngine engine;
    const auto events = engine.submit({1, vm::Side::Buy, vm::OrderType::Limit, 100, 7});

    REQUIRE(events.size() == 1);
    REQUIRE(std::holds_alternative<vm::OrderAccepted>(events[0]));
    REQUIRE(engine.contains(1));
    REQUIRE(engine.best_bid() == 100);
    REQUIRE(!engine.best_ask().has_value());

    const auto book = engine.snapshot();
    REQUIRE(book.bids.size() == 1);
    REQUIRE(book.bids[0].total_quantity == 7);
    REQUIRE(book.bids[0].orders[0].order_id == 1);
    require_valid(engine);
}

void execution_uses_maker_price() {
    vm::MatchingEngine engine;
    submit_ignored(engine, {1, vm::Side::Sell, vm::OrderType::Limit, 100, 3});
    const auto events = engine.submit({2, vm::Side::Buy, vm::OrderType::Limit, 105, 3});
    const auto result = trades(events);

    REQUIRE(result.size() == 1);
    REQUIRE(result[0].price == 100);
    REQUIRE(result[0].maker_order_id == 1);
    REQUIRE(result[0].taker_order_id == 2);
    REQUIRE(result[0].taker_side == vm::Side::Buy);
    REQUIRE(engine.active_order_count() == 0);
    require_valid(engine);
}

void better_price_matches_first() {
    vm::MatchingEngine engine;
    submit_ignored(engine, {1, vm::Side::Sell, vm::OrderType::Limit, 102, 2});
    submit_ignored(engine, {2, vm::Side::Sell, vm::OrderType::Limit, 101, 2});
    const auto result = trades(engine.submit({3, vm::Side::Buy, vm::OrderType::Market, 0, 3}));

    REQUIRE(result.size() == 2);
    REQUIRE(result[0].maker_order_id == 2);
    REQUIRE(result[0].price == 101);
    REQUIRE(result[0].quantity == 2);
    REQUIRE(result[1].maker_order_id == 1);
    REQUIRE(result[1].price == 102);
    REQUIRE(result[1].quantity == 1);
    require_valid(engine);
}

void fifo_within_price_level() {
    vm::MatchingEngine engine;
    submit_ignored(engine, {1, vm::Side::Sell, vm::OrderType::Limit, 100, 5});
    submit_ignored(engine, {2, vm::Side::Sell, vm::OrderType::Limit, 100, 5});
    const auto result = trades(engine.submit({3, vm::Side::Buy, vm::OrderType::Market, 0, 7}));

    REQUIRE(result.size() == 2);
    REQUIRE(result[0].maker_order_id == 1);
    REQUIRE(result[0].quantity == 5);
    REQUIRE(result[1].maker_order_id == 2);
    REQUIRE(result[1].quantity == 2);

    const auto book = engine.snapshot();
    REQUIRE(book.asks[0].orders.size() == 1);
    REQUIRE(book.asks[0].orders[0].order_id == 2);
    REQUIRE(book.asks[0].orders[0].remaining == 3);
    require_valid(engine);
}

void partial_fill_updates_aggregates() {
    vm::MatchingEngine engine;
    submit_ignored(engine, {10, vm::Side::Buy, vm::OrderType::Limit, 100, 10});
    const auto result = trades(engine.submit({11, vm::Side::Sell, vm::OrderType::Limit, 99, 4}));

    REQUIRE(result.size() == 1);
    REQUIRE(result[0].maker_order_id == 10);
    REQUIRE(result[0].maker_remaining == 6);
    REQUIRE(result[0].taker_remaining == 0);

    const auto book = engine.snapshot();
    REQUIRE(book.bids[0].total_quantity == 6);
    REQUIRE(book.bids[0].orders[0].remaining == 6);
    require_valid(engine);
}

void market_remainder_is_canceled() {
    vm::MatchingEngine engine;
    submit_ignored(engine, {1, vm::Side::Sell, vm::OrderType::Limit, 100, 2});
    const auto events = engine.submit({2, vm::Side::Buy, vm::OrderType::Market, 0, 5});

    const auto *canceled = find_event<vm::OrderCanceled>(events);
    REQUIRE(canceled != nullptr);
    REQUIRE(canceled->order_id == 2);
    REQUIRE(canceled->canceled_quantity == 3);
    REQUIRE(canceled->reason == vm::CancelReason::UnfilledMarketRemainder);
    REQUIRE(!engine.contains(2));
    require_valid(engine);
}

void aggressive_limit_remainder_rests() {
    vm::MatchingEngine engine;
    submit_ignored(engine, {1, vm::Side::Sell, vm::OrderType::Limit, 100, 2});
    const auto events = engine.submit({2, vm::Side::Buy, vm::OrderType::Limit, 105, 5});

    const auto result = trades(events);
    REQUIRE(result.size() == 1);
    REQUIRE(result[0].quantity == 2);
    REQUIRE(result[0].taker_remaining == 3);
    REQUIRE(engine.contains(2));
    REQUIRE(engine.best_bid() == 105);
    REQUIRE(!engine.best_ask().has_value());
    REQUIRE(engine.snapshot().bids[0].total_quantity == 3);
    require_valid(engine);
}

void limit_price_is_a_hard_boundary() {
    vm::MatchingEngine engine;
    submit_ignored(engine, {1, vm::Side::Sell, vm::OrderType::Limit, 100, 1});
    submit_ignored(engine, {2, vm::Side::Sell, vm::OrderType::Limit, 101, 1});
    const auto events = engine.submit({3, vm::Side::Buy, vm::OrderType::Limit, 100, 2});

    const auto result = trades(events);
    REQUIRE(result.size() == 1);
    REQUIRE(result[0].maker_order_id == 1);
    REQUIRE(result[0].price == 100);
    REQUIRE(engine.contains(2));
    REQUIRE(engine.contains(3));
    REQUIRE(engine.best_bid() == 100);
    REQUIRE(engine.best_ask() == 101);
    require_valid(engine);
}

void cancel_removes_order_and_level() {
    vm::MatchingEngine engine;
    submit_ignored(engine, {1, vm::Side::Buy, vm::OrderType::Limit, 100, 4});
    const auto events = engine.cancel(1);

    const auto *canceled = find_event<vm::OrderCanceled>(events);
    REQUIRE(canceled != nullptr);
    REQUIRE(canceled->canceled_quantity == 4);
    REQUIRE(!engine.contains(1));
    REQUIRE(!engine.best_bid().has_value());

    const auto second_cancel = engine.cancel(1);
    REQUIRE(find_event<vm::CancelRejected>(second_cancel) != nullptr);
    require_valid(engine);
}

void cancel_middle_order_preserves_fifo() {
    vm::MatchingEngine engine;
    submit_ignored(engine, {1, vm::Side::Sell, vm::OrderType::Limit, 100, 1});
    submit_ignored(engine, {2, vm::Side::Sell, vm::OrderType::Limit, 100, 1});
    submit_ignored(engine, {3, vm::Side::Sell, vm::OrderType::Limit, 100, 1});
    cancel_ignored(engine, 2);

    const auto result = trades(engine.submit({4, vm::Side::Buy, vm::OrderType::Market, 0, 2}));
    REQUIRE(result.size() == 2);
    REQUIRE(result[0].maker_order_id == 1);
    REQUIRE(result[1].maker_order_id == 3);
    require_valid(engine);
}

void cancel_head_and_tail_preserves_remaining_order() {
    vm::MatchingEngine engine;
    submit_ignored(engine, {1, vm::Side::Sell, vm::OrderType::Limit, 100, 1});
    submit_ignored(engine, {2, vm::Side::Sell, vm::OrderType::Limit, 100, 2});
    submit_ignored(engine, {3, vm::Side::Sell, vm::OrderType::Limit, 100, 3});

    cancel_ignored(engine, 1);
    cancel_ignored(engine, 3);

    const auto book = engine.snapshot();
    REQUIRE(book.asks.size() == 1);
    REQUIRE(book.asks[0].total_quantity == 2);
    REQUIRE(book.asks[0].orders.size() == 1);
    REQUIRE(book.asks[0].orders[0].order_id == 2);

    const auto result = trades(engine.submit({4, vm::Side::Buy, vm::OrderType::Market, 0, 2}));
    REQUIRE(result.size() == 1);
    REQUIRE(result[0].maker_order_id == 2);
    REQUIRE(!engine.best_ask().has_value());
    require_valid(engine);
}

void partial_fill_then_cancel_uses_leaves_quantity() {
    vm::MatchingEngine engine;
    submit_ignored(engine, {1, vm::Side::Buy, vm::OrderType::Limit, 100, 10});
    submit_ignored(engine, {2, vm::Side::Sell, vm::OrderType::Market, 0, 4});

    const auto events = engine.cancel(1);
    const auto *canceled = find_event<vm::OrderCanceled>(events);
    REQUIRE(canceled != nullptr);
    REQUIRE(canceled->canceled_quantity == 6);
    REQUIRE(!engine.contains(1));
    require_valid(engine);
}

void duplicate_id_is_rejected_after_terminal_state() {
    vm::MatchingEngine engine;
    submit_ignored(engine, {1, vm::Side::Buy, vm::OrderType::Limit, 100, 1});
    cancel_ignored(engine, 1);
    const auto events = engine.submit({1, vm::Side::Sell, vm::OrderType::Limit, 101, 1});

    const auto *rejected = find_event<vm::OrderRejected>(events);
    REQUIRE(rejected != nullptr);
    REQUIRE(rejected->reason == vm::RejectReason::DuplicateOrderId);
    require_valid(engine);
}

void filled_maker_and_taker_ids_cannot_be_reused() {
    vm::MatchingEngine engine;
    submit_ignored(engine, {1, vm::Side::Sell, vm::OrderType::Limit, 100, 1});
    submit_ignored(engine, {2, vm::Side::Buy, vm::OrderType::Market, 0, 1});

    auto events = engine.submit({1, vm::Side::Buy, vm::OrderType::Limit, 99, 1});
    REQUIRE(find_event<vm::OrderRejected>(events)->reason == vm::RejectReason::DuplicateOrderId);
    events = engine.submit({2, vm::Side::Buy, vm::OrderType::Limit, 99, 1});
    REQUIRE(find_event<vm::OrderRejected>(events)->reason == vm::RejectReason::DuplicateOrderId);
    require_valid(engine);
}

void invalid_orders_are_rejected() {
    vm::MatchingEngine engine;

    auto events = engine.submit({0, vm::Side::Buy, vm::OrderType::Limit, 100, 1});
    REQUIRE(find_event<vm::OrderRejected>(events)->reason == vm::RejectReason::InvalidOrderId);

    events = engine.submit({1, vm::Side::Buy, vm::OrderType::Limit, 100, 0});
    REQUIRE(find_event<vm::OrderRejected>(events)->reason == vm::RejectReason::InvalidQuantity);

    events = engine.submit({2, vm::Side::Buy, vm::OrderType::Limit, 0, 1});
    REQUIRE(find_event<vm::OrderRejected>(events)->reason == vm::RejectReason::InvalidPrice);

    // Rejected submissions do not consume their ID; a corrected order can reuse it.
    events = engine.submit({1, vm::Side::Buy, vm::OrderType::Limit, 100, 1});
    REQUIRE(find_event<vm::OrderAccepted>(events) != nullptr);

    events = engine.submit({3, vm::Side::Buy, vm::OrderType::Market, 99, 1});
    REQUIRE(find_event<vm::OrderRejected>(events)->reason == vm::RejectReason::InvalidPrice);

    // A corrected request can reuse an ID that was never accepted.
    events = engine.submit({3, vm::Side::Buy, vm::OrderType::Market, 0, 1});
    REQUIRE(find_event<vm::OrderAccepted>(events) != nullptr);
    REQUIRE(find_event<vm::OrderCanceled>(events) != nullptr);

    // For an accepted ID, duplicate detection takes precedence on retries.
    events = engine.submit({3, vm::Side::Buy, vm::OrderType::Limit, 0, 0});
    REQUIRE(find_event<vm::OrderRejected>(events)->reason == vm::RejectReason::DuplicateOrderId);
    require_valid(engine);
}

void price_level_quantity_overflow_is_rejected() {
    vm::MatchingEngine engine;
    submit_ignored(engine, {
                               1,
                               vm::Side::Buy,
                               vm::OrderType::Limit,
                               100,
                               std::numeric_limits<vm::Quantity>::max(),
                           });

    const auto events = engine.submit({2, vm::Side::Buy, vm::OrderType::Limit, 100, 1});
    const auto *rejected = find_event<vm::OrderRejected>(events);
    REQUIRE(rejected != nullptr);
    REQUIRE(rejected->reason == vm::RejectReason::QuantityOverflow);
    REQUIRE(!engine.contains(2));
    require_valid(engine);
}

void event_sequences_are_monotonic() {
    vm::MatchingEngine engine;
    vm::EventBuffer all;

    const auto append = [&](vm::EventBuffer events) {
        all.insert(all.end(), events.begin(), events.end());
    };

    append(engine.submit({1, vm::Side::Sell, vm::OrderType::Limit, 100, 2}));
    append(engine.submit({2, vm::Side::Buy, vm::OrderType::Market, 0, 3}));
    append(engine.cancel(999));

    REQUIRE(!all.empty());
    for (std::size_t i = 1; i < all.size(); ++i) {
        REQUIRE(vm::event_sequence(all[i]) == vm::event_sequence(all[i - 1]) + 1);
    }
    REQUIRE(engine.last_event_sequence() == vm::event_sequence(all.back()));
    REQUIRE(engine.last_trade_id() == 1);
}

void market_event_order_is_accepted_trades_canceled() {
    vm::MatchingEngine engine;
    submit_ignored(engine, {1, vm::Side::Sell, vm::OrderType::Limit, 100, 2});
    const auto events = engine.submit({2, vm::Side::Buy, vm::OrderType::Market, 0, 5});

    REQUIRE(events.size() == 3);
    REQUIRE(std::holds_alternative<vm::OrderAccepted>(events[0]));
    REQUIRE(std::holds_alternative<vm::Trade>(events[1]));
    REQUIRE(std::holds_alternative<vm::OrderCanceled>(events[2]));
    REQUIRE(vm::event_sequence(events[1]) == vm::event_sequence(events[0]) + 1);
    REQUIRE(vm::event_sequence(events[2]) == vm::event_sequence(events[1]) + 1);
}

void caller_owned_event_buffer_is_reused_safely() {
    vm::MatchingEngine engine;
    vm::EventBuffer events{
        vm::CancelRejected{.sequence = 999, .order_id = 999},
    };

    engine.submit({1, vm::Side::Buy, vm::OrderType::Limit, 100, 1}, events);
    REQUIRE(events.size() == 1);
    REQUIRE(std::holds_alternative<vm::OrderAccepted>(events[0]));
    REQUIRE(vm::event_sequence(events[0]) == 1);

    engine.cancel(1, events);
    REQUIRE(events.size() == 1);
    REQUIRE(std::holds_alternative<vm::OrderCanceled>(events[0]));
    REQUIRE(vm::event_sequence(events[0]) == 2);
}

void snapshot_depth_and_clear_work() {
    vm::MatchingEngine engine;
    submit_ignored(engine, {1, vm::Side::Buy, vm::OrderType::Limit, 99, 1});
    submit_ignored(engine, {2, vm::Side::Buy, vm::OrderType::Limit, 98, 1});
    submit_ignored(engine, {3, vm::Side::Sell, vm::OrderType::Limit, 101, 1});
    submit_ignored(engine, {4, vm::Side::Sell, vm::OrderType::Limit, 102, 1});

    const auto top = engine.snapshot(1);
    REQUIRE(top.bids.size() == 1);
    REQUIRE(top.asks.size() == 1);
    REQUIRE(top.bids[0].price == 99);
    REQUIRE(top.asks[0].price == 101);

    engine.clear();
    REQUIRE(engine.active_order_count() == 0);
    REQUIRE(!engine.best_bid().has_value());
    REQUIRE(!engine.best_ask().has_value());
    REQUIRE(engine.last_event_sequence() == 0);
    REQUIRE(engine.last_trade_id() == 0);

    // clear() starts a new engine lifecycle, so IDs can be used again.
    const auto events = engine.submit({1, vm::Side::Buy, vm::OrderType::Limit, 99, 1});
    REQUIRE(find_event<vm::OrderAccepted>(events) != nullptr);
    require_valid(engine);
}

void replay_is_deterministic() {
    const std::vector<vm::NewOrder> commands{
        {1, vm::Side::Sell, vm::OrderType::Limit, 100, 2},
        {2, vm::Side::Sell, vm::OrderType::Limit, 101, 3},
        {3, vm::Side::Buy, vm::OrderType::Limit, 101, 4},
        {4, vm::Side::Buy, vm::OrderType::Market, 0, 2},
    };

    vm::MatchingEngine first;
    vm::MatchingEngine second;
    for (const vm::NewOrder &command : commands) {
        REQUIRE(first.submit(command) == second.submit(command));
    }
    REQUIRE(first.cancel(3) == second.cancel(3));
    REQUIRE(first.snapshot() == second.snapshot());
    REQUIRE(first.last_event_sequence() == second.last_event_sequence());
    REQUIRE(first.last_trade_id() == second.last_trade_id());
    require_valid(first);
    require_valid(second);
}

void symmetric_sell_aggression() {
    vm::MatchingEngine engine;
    submit_ignored(engine, {1, vm::Side::Buy, vm::OrderType::Limit, 100, 2});
    submit_ignored(engine, {2, vm::Side::Buy, vm::OrderType::Limit, 101, 2});
    const auto result = trades(engine.submit({3, vm::Side::Sell, vm::OrderType::Market, 0, 3}));

    REQUIRE(result.size() == 2);
    REQUIRE(result[0].maker_order_id == 2);
    REQUIRE(result[0].price == 101);
    REQUIRE(result[1].maker_order_id == 1);
    REQUIRE(result[1].price == 100);
    require_valid(engine);
}

void randomized_operations_preserve_invariants() {
    vm::MatchingEngine engine;
    std::mt19937_64 rng(42);
    vm::OrderId next_id = 1;

    for (std::size_t i = 0; i < 5'000; ++i) {
        const std::uint64_t choice = rng() % 10;
        if (choice < 7) {
            const vm::Side side = (rng() & 1U) == 0 ? vm::Side::Buy : vm::Side::Sell;
            const vm::Price price = side == vm::Side::Buy
                                        ? 9'900 - static_cast<vm::Price>(rng() % 50)
                                        : 10'100 + static_cast<vm::Price>(rng() % 50);
            submit_ignored(engine, {next_id++, side, vm::OrderType::Limit, price, 1 + rng() % 20});
        } else if (choice < 9) {
            const vm::Side side = (rng() & 1U) == 0 ? vm::Side::Buy : vm::Side::Sell;
            submit_ignored(engine, {next_id++, side, vm::OrderType::Market, 0, 1 + rng() % 20});
        } else {
            const vm::OrderId candidate = next_id > 1 ? 1 + rng() % (next_id - 1) : 1;
            cancel_ignored(engine, candidate);
        }

        if (i % 100 == 0) {
            require_valid(engine);
        }
    }
    require_valid(engine);
}

} // namespace

int main() {
    const std::vector<std::pair<std::string, std::function<void()>>> tests{
        {"limit order rests", limit_order_rests},
        {"execution uses maker price", execution_uses_maker_price},
        {"better price matches first", better_price_matches_first},
        {"FIFO within price level", fifo_within_price_level},
        {"partial fill updates aggregates", partial_fill_updates_aggregates},
        {"market remainder is canceled", market_remainder_is_canceled},
        {"aggressive limit remainder rests", aggressive_limit_remainder_rests},
        {"limit price is a hard boundary", limit_price_is_a_hard_boundary},
        {"cancel removes order and level", cancel_removes_order_and_level},
        {"cancel middle order preserves FIFO", cancel_middle_order_preserves_fifo},
        {"cancel head and tail preserves remaining order",
         cancel_head_and_tail_preserves_remaining_order},
        {"partial fill then cancel uses leaves quantity",
         partial_fill_then_cancel_uses_leaves_quantity},
        {"duplicate ID rejected after terminal state",
         duplicate_id_is_rejected_after_terminal_state},
        {"filled maker and taker IDs cannot be reused",
         filled_maker_and_taker_ids_cannot_be_reused},
        {"invalid orders are rejected", invalid_orders_are_rejected},
        {"price-level quantity overflow is rejected", price_level_quantity_overflow_is_rejected},
        {"event sequences are monotonic", event_sequences_are_monotonic},
        {"market event order is accepted-trades-canceled",
         market_event_order_is_accepted_trades_canceled},
        {"caller-owned event buffer is reused safely", caller_owned_event_buffer_is_reused_safely},
        {"snapshot depth and clear work", snapshot_depth_and_clear_work},
        {"replay is deterministic", replay_is_deterministic},
        {"symmetric sell aggression", symmetric_sell_aggression},
        {"randomized operations preserve invariants", randomized_operations_preserve_invariants},
    };

    std::size_t passed = 0;
    for (const auto &[name, test] : tests) {
        try {
            test();
            ++passed;
            std::cout << "[PASS] " << name << '\n';
        } catch (const std::exception &exception) {
            std::cerr << "[FAIL] " << name << ": " << exception.what() << '\n';
        }
    }

    std::cout << passed << '/' << tests.size() << " tests passed\n";
    return passed == tests.size() ? 0 : 1;
}
