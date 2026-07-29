#include "matching_engine/matching_engine.hpp"

#include <algorithm>
#include <cassert>
#include <iterator>
#include <limits>
#include <utility>

namespace vnpy::matching {

namespace {

void set_error(std::string *error, std::string message) {
    if (error != nullptr) {
        *error = std::move(message);
    }
}

} // namespace

EventBuffer MatchingEngine::submit(const NewOrder &request) {
    EventBuffer events;
    events.reserve(8);
    submit(request, events);
    return events;
}

void MatchingEngine::submit(const NewOrder &request, EventBuffer &events) {
    events.clear();

    if (const auto reason = validate(request); reason.has_value()) {
        events.emplace_back(OrderRejected{
            .sequence = next_sequence(),
            .order_id = request.order_id,
            .reason = *reason,
        });
        return;
    }

    seen_order_ids_.insert(request.order_id);

    const Sequence arrival_sequence = next_sequence();
    events.emplace_back(OrderAccepted{
        .sequence = arrival_sequence,
        .order_id = request.order_id,
        .side = request.side,
        .type = request.type,
        .price = request.price,
        .quantity = request.quantity,
    });

    RestingOrder taker{
        .order_id = request.order_id,
        .side = request.side,
        .price = request.price,
        .remaining = request.quantity,
        .arrival_sequence = arrival_sequence,
    };

    if (request.side == Side::Buy) {
        match_buy(taker, request.type, events);
    } else {
        match_sell(taker, request.type, events);
    }

    if (taker.remaining == 0) {
        return;
    }

    if (request.type == OrderType::Limit) {
        rest(std::move(taker));
    } else {
        events.emplace_back(OrderCanceled{
            .sequence = next_sequence(),
            .order_id = taker.order_id,
            .canceled_quantity = taker.remaining,
            .reason = CancelReason::UnfilledMarketRemainder,
        });
    }
}

EventBuffer MatchingEngine::cancel(OrderId order_id) {
    EventBuffer events;
    events.reserve(1);
    cancel(order_id, events);
    return events;
}

void MatchingEngine::cancel(OrderId order_id, EventBuffer &events) {
    events.clear();

    const auto handle_it = active_orders_.find(order_id);
    if (handle_it == active_orders_.end()) {
        events.emplace_back(CancelRejected{
            .sequence = next_sequence(),
            .order_id = order_id,
        });
        return;
    }

    const OrderHandle handle = handle_it->second;
    const Quantity canceled_quantity = handle.iterator->remaining;

    if (handle.side == Side::Buy) {
        const auto level_it = bids_.find(handle.price);
        assert(level_it != bids_.end());
        PriceLevel &level = level_it->second;
        assert(level.total_quantity >= canceled_quantity);
        level.total_quantity -= canceled_quantity;
        level.orders.erase(handle.iterator);
        active_orders_.erase(handle_it);
        if (level.orders.empty()) {
            bids_.erase(level_it);
        }
    } else {
        const auto level_it = asks_.find(handle.price);
        assert(level_it != asks_.end());
        PriceLevel &level = level_it->second;
        assert(level.total_quantity >= canceled_quantity);
        level.total_quantity -= canceled_quantity;
        level.orders.erase(handle.iterator);
        active_orders_.erase(handle_it);
        if (level.orders.empty()) {
            asks_.erase(level_it);
        }
    }

    events.emplace_back(OrderCanceled{
        .sequence = next_sequence(),
        .order_id = order_id,
        .canceled_quantity = canceled_quantity,
        .reason = CancelReason::UserRequested,
    });
}

bool MatchingEngine::contains(OrderId order_id) const noexcept {
    return active_orders_.contains(order_id);
}

std::size_t MatchingEngine::active_order_count() const noexcept {
    return active_orders_.size();
}

std::optional<Price> MatchingEngine::best_bid() const noexcept {
    if (bids_.empty()) {
        return std::nullopt;
    }
    return bids_.begin()->first;
}

std::optional<Price> MatchingEngine::best_ask() const noexcept {
    if (asks_.empty()) {
        return std::nullopt;
    }
    return asks_.begin()->first;
}

BookSnapshot MatchingEngine::snapshot(std::size_t depth) const {
    BookSnapshot result;

    const auto append_level = [](const auto &entry, std::vector<PriceLevelView> &output) {
        const auto &[price, level] = entry;
        PriceLevelView view{
            .price = price,
            .total_quantity = level.total_quantity,
            .orders = {},
        };
        view.orders.reserve(level.orders.size());
        for (const RestingOrder &order : level.orders) {
            view.orders.push_back(OrderView{
                .order_id = order.order_id,
                .remaining = order.remaining,
                .arrival_sequence = order.arrival_sequence,
            });
        }
        output.push_back(std::move(view));
    };

    result.bids.reserve(depth == 0 ? bids_.size() : std::min(depth, bids_.size()));
    for (const auto &entry : bids_) {
        if (depth != 0 && result.bids.size() >= depth) {
            break;
        }
        append_level(entry, result.bids);
    }

    result.asks.reserve(depth == 0 ? asks_.size() : std::min(depth, asks_.size()));
    for (const auto &entry : asks_) {
        if (depth != 0 && result.asks.size() >= depth) {
            break;
        }
        append_level(entry, result.asks);
    }

    return result;
}

bool MatchingEngine::check_invariants(std::string *error) const {
    std::size_t order_count = 0;

    const auto check_side = [&](const auto &book, Side expected_side, std::string_view name) {
        for (const auto &[price, level] : book) {
            if (level.orders.empty()) {
                set_error(error, std::string(name) + " contains an empty price level");
                return false;
            }

            Quantity total = 0;
            Sequence previous_sequence = 0;
            for (const RestingOrder &order : level.orders) {
                ++order_count;
                if (order.side != expected_side || order.price != price || order.remaining == 0) {
                    set_error(error, std::string(name) + " contains an invalid resting order");
                    return false;
                }
                if (previous_sequence != 0 && order.arrival_sequence <= previous_sequence) {
                    set_error(error, std::string(name) + " violates FIFO arrival order");
                    return false;
                }
                previous_sequence = order.arrival_sequence;

                if (std::numeric_limits<Quantity>::max() - total < order.remaining) {
                    set_error(error, std::string(name) + " quantity overflow");
                    return false;
                }
                total += order.remaining;

                const auto handle_it = active_orders_.find(order.order_id);
                if (handle_it == active_orders_.end()) {
                    set_error(error, std::string(name) + " order is missing from the ID index");
                    return false;
                }
                const OrderHandle &handle = handle_it->second;
                if (handle.side != expected_side || handle.price != price ||
                    handle.iterator->order_id != order.order_id) {
                    set_error(error, std::string(name) + " has a stale ID index entry");
                    return false;
                }
                if (!seen_order_ids_.contains(order.order_id)) {
                    set_error(error, std::string(name) + " active order is missing from seen IDs");
                    return false;
                }
            }

            if (total != level.total_quantity) {
                set_error(error, std::string(name) + " aggregate quantity is inconsistent");
                return false;
            }
        }
        return true;
    };

    if (!check_side(bids_, Side::Buy, "bid book")) {
        return false;
    }
    if (!check_side(asks_, Side::Sell, "ask book")) {
        return false;
    }
    if (order_count != active_orders_.size()) {
        set_error(error, "ID index size differs from resting order count");
        return false;
    }
    if (!bids_.empty() && !asks_.empty() && bids_.begin()->first >= asks_.begin()->first) {
        set_error(error, "book is crossed after matching");
        return false;
    }

    if (error != nullptr) {
        error->clear();
    }
    return true;
}

Sequence MatchingEngine::last_event_sequence() const noexcept {
    return event_sequence_;
}

TradeId MatchingEngine::last_trade_id() const noexcept {
    return trade_id_;
}

void MatchingEngine::clear() noexcept {
    bids_.clear();
    asks_.clear();
    active_orders_.clear();
    seen_order_ids_.clear();
    event_sequence_ = 0;
    trade_id_ = 0;
}

Sequence MatchingEngine::next_sequence() noexcept {
    return ++event_sequence_;
}

std::optional<RejectReason> MatchingEngine::validate(const NewOrder &request) const noexcept {
    if (request.order_id == 0) {
        return RejectReason::InvalidOrderId;
    }
    // Once an ID has been accepted, duplicate detection takes precedence over
    // all mutable order fields supplied by a retrying client.
    if (seen_order_ids_.contains(request.order_id)) {
        return RejectReason::DuplicateOrderId;
    }
    if (request.quantity == 0) {
        return RejectReason::InvalidQuantity;
    }
    if (request.type == OrderType::Limit && request.price <= 0) {
        return RejectReason::InvalidPrice;
    }
    if (request.type == OrderType::Market && request.price != 0) {
        return RejectReason::InvalidPrice;
    }
    if (request.type == OrderType::Limit) {
        Quantity level_quantity = 0;
        if (request.side == Side::Buy) {
            const auto level_it = bids_.find(request.price);
            if (level_it != bids_.end()) {
                level_quantity = level_it->second.total_quantity;
            }
        } else {
            const auto level_it = asks_.find(request.price);
            if (level_it != asks_.end()) {
                level_quantity = level_it->second.total_quantity;
            }
        }

        if (std::numeric_limits<Quantity>::max() - level_quantity < request.quantity) {
            return RejectReason::QuantityOverflow;
        }
    }
    return std::nullopt;
}

void MatchingEngine::match_buy(RestingOrder &taker, OrderType type, EventBuffer &events) {
    while (taker.remaining > 0 && !asks_.empty()) {
        auto level_it = asks_.begin();
        if (type == OrderType::Limit && taker.price < level_it->first) {
            break;
        }

        match_level(taker, level_it->second, events);
        if (level_it->second.orders.empty()) {
            asks_.erase(level_it);
        }
    }
}

void MatchingEngine::match_sell(RestingOrder &taker, OrderType type, EventBuffer &events) {
    while (taker.remaining > 0 && !bids_.empty()) {
        auto level_it = bids_.begin();
        if (type == OrderType::Limit && taker.price > level_it->first) {
            break;
        }

        match_level(taker, level_it->second, events);
        if (level_it->second.orders.empty()) {
            bids_.erase(level_it);
        }
    }
}

void MatchingEngine::match_level(RestingOrder &taker, PriceLevel &level, EventBuffer &events) {
    while (taker.remaining > 0 && !level.orders.empty()) {
        auto maker_it = level.orders.begin();
        RestingOrder &maker = *maker_it;

        const Quantity matched = std::min(taker.remaining, maker.remaining);
        maker.remaining -= matched;
        taker.remaining -= matched;
        assert(level.total_quantity >= matched);
        level.total_quantity -= matched;

        events.emplace_back(Trade{
            .sequence = next_sequence(),
            .trade_id = ++trade_id_,
            .maker_order_id = maker.order_id,
            .taker_order_id = taker.order_id,
            .taker_side = taker.side,
            .price = maker.price,
            .quantity = matched,
            .maker_remaining = maker.remaining,
            .taker_remaining = taker.remaining,
        });

        if (maker.remaining == 0) {
            active_orders_.erase(maker.order_id);
            level.orders.erase(maker_it);
        }
    }
}

void MatchingEngine::rest(RestingOrder &&order) {
    assert(order.remaining > 0);
    const OrderId order_id = order.order_id;
    const Side side = order.side;
    const Price price = order.price;
    const Quantity quantity = order.remaining;

    if (side == Side::Buy) {
        auto [level_it, inserted] = bids_.try_emplace(price);
        static_cast<void>(inserted);
        PriceLevel &level = level_it->second;
        level.orders.push_back(std::move(order));
        level.total_quantity += quantity;
        active_orders_.emplace(order_id, OrderHandle{
                                             .side = side,
                                             .price = price,
                                             .iterator = std::prev(level.orders.end()),
                                         });
    } else {
        auto [level_it, inserted] = asks_.try_emplace(price);
        static_cast<void>(inserted);
        PriceLevel &level = level_it->second;
        level.orders.push_back(std::move(order));
        level.total_quantity += quantity;
        active_orders_.emplace(order_id, OrderHandle{
                                             .side = side,
                                             .price = price,
                                             .iterator = std::prev(level.orders.end()),
                                         });
    }
}

Sequence event_sequence(const Event &event) noexcept {
    return std::visit([](const auto &value) { return value.sequence; }, event);
}

std::string_view to_string(Side value) noexcept {
    return value == Side::Buy ? "BUY" : "SELL";
}

std::string_view to_string(OrderType value) noexcept {
    return value == OrderType::Limit ? "LIMIT" : "MARKET";
}

std::string_view to_string(RejectReason value) noexcept {
    switch (value) {
    case RejectReason::InvalidOrderId:
        return "INVALID_ORDER_ID";
    case RejectReason::InvalidQuantity:
        return "INVALID_QUANTITY";
    case RejectReason::InvalidPrice:
        return "INVALID_PRICE";
    case RejectReason::QuantityOverflow:
        return "QUANTITY_OVERFLOW";
    case RejectReason::DuplicateOrderId:
        return "DUPLICATE_ORDER_ID";
    }
    return "UNKNOWN_REJECT_REASON";
}

std::string_view to_string(CancelReason value) noexcept {
    return value == CancelReason::UserRequested ? "USER_REQUESTED" : "UNFILLED_MARKET_REMAINDER";
}

} // namespace vnpy::matching
