#pragma once

#include <cstddef>
#include <cstdint>
#include <functional>
#include <list>
#include <map>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <variant>
#include <vector>

namespace vnpy::matching {

using OrderId = std::uint64_t;
using TradeId = std::uint64_t;
using Sequence = std::uint64_t;
using Price = std::int64_t;
using Quantity = std::uint64_t;

enum class Side {
    Buy,
    Sell,
};

enum class OrderType {
    Limit,
    Market,
};

enum class RejectReason {
    InvalidOrderId,
    InvalidQuantity,
    InvalidPrice,
    QuantityOverflow,
    DuplicateOrderId,
};

enum class CancelReason {
    UserRequested,
    UnfilledMarketRemainder,
};

struct NewOrder {
    OrderId order_id{};
    Side side{Side::Buy};
    OrderType type{OrderType::Limit};
    Price price{};
    Quantity quantity{};

    bool operator==(const NewOrder &) const = default;
};

struct OrderAccepted {
    Sequence sequence{};
    OrderId order_id{};
    Side side{Side::Buy};
    OrderType type{OrderType::Limit};
    Price price{};
    Quantity quantity{};

    bool operator==(const OrderAccepted &) const = default;
};

struct Trade {
    Sequence sequence{};
    TradeId trade_id{};
    OrderId maker_order_id{};
    OrderId taker_order_id{};
    Side taker_side{Side::Buy};
    Price price{};
    Quantity quantity{};
    Quantity maker_remaining{};
    Quantity taker_remaining{};

    bool operator==(const Trade &) const = default;
};

struct OrderCanceled {
    Sequence sequence{};
    OrderId order_id{};
    Quantity canceled_quantity{};
    CancelReason reason{CancelReason::UserRequested};

    bool operator==(const OrderCanceled &) const = default;
};

struct OrderRejected {
    Sequence sequence{};
    OrderId order_id{};
    RejectReason reason{RejectReason::InvalidOrderId};

    bool operator==(const OrderRejected &) const = default;
};

struct CancelRejected {
    Sequence sequence{};
    OrderId order_id{};

    bool operator==(const CancelRejected &) const = default;
};

using Event = std::variant<OrderAccepted, Trade, OrderCanceled, OrderRejected, CancelRejected>;

using EventBuffer = std::vector<Event>;

struct OrderView {
    OrderId order_id{};
    Quantity remaining{};
    Sequence arrival_sequence{};

    bool operator==(const OrderView &) const = default;
};

struct PriceLevelView {
    Price price{};
    Quantity total_quantity{};
    std::vector<OrderView> orders;

    bool operator==(const PriceLevelView &) const = default;
};

struct BookSnapshot {
    std::vector<PriceLevelView> bids;
    std::vector<PriceLevelView> asks;

    bool operator==(const BookSnapshot &) const = default;
};

class MatchingEngine {
  public:
    MatchingEngine() = default;

    [[nodiscard]] EventBuffer submit(const NewOrder &request);
    void submit(const NewOrder &request, EventBuffer &events);

    [[nodiscard]] EventBuffer cancel(OrderId order_id);
    void cancel(OrderId order_id, EventBuffer &events);

    [[nodiscard]] bool contains(OrderId order_id) const noexcept;
    [[nodiscard]] std::size_t active_order_count() const noexcept;
    [[nodiscard]] std::optional<Price> best_bid() const noexcept;
    [[nodiscard]] std::optional<Price> best_ask() const noexcept;
    [[nodiscard]] BookSnapshot snapshot(std::size_t depth = 0) const;

    // Intended for tests, diagnostics, and interview discussion. Production
    // systems commonly compile expensive invariant checks out of the hot path.
    [[nodiscard]] bool check_invariants(std::string *error = nullptr) const;

    [[nodiscard]] Sequence last_event_sequence() const noexcept;
    [[nodiscard]] TradeId last_trade_id() const noexcept;

    void clear() noexcept;

  private:
    struct RestingOrder {
        OrderId order_id{};
        Side side{Side::Buy};
        Price price{};
        Quantity remaining{};
        Sequence arrival_sequence{};
    };

    struct PriceLevel {
        Quantity total_quantity{};
        std::list<RestingOrder> orders;
    };

    using BidBook = std::map<Price, PriceLevel, std::greater<Price>>;
    using AskBook = std::map<Price, PriceLevel, std::less<Price>>;
    using OrderIterator = std::list<RestingOrder>::iterator;

    struct OrderHandle {
        Side side{Side::Buy};
        Price price{};
        OrderIterator iterator;
    };

    BidBook bids_;
    AskBook asks_;
    std::unordered_map<OrderId, OrderHandle> active_orders_;
    std::unordered_set<OrderId> seen_order_ids_;

    Sequence event_sequence_{};
    TradeId trade_id_{};

    [[nodiscard]] Sequence next_sequence() noexcept;
    [[nodiscard]] std::optional<RejectReason> validate(const NewOrder &request) const noexcept;

    void match_buy(RestingOrder &taker, OrderType type, EventBuffer &events);
    void match_sell(RestingOrder &taker, OrderType type, EventBuffer &events);
    void match_level(RestingOrder &taker, PriceLevel &level, EventBuffer &events);
    void rest(RestingOrder &&order);
};

[[nodiscard]] Sequence event_sequence(const Event &event) noexcept;
[[nodiscard]] std::string_view to_string(Side value) noexcept;
[[nodiscard]] std::string_view to_string(OrderType value) noexcept;
[[nodiscard]] std::string_view to_string(RejectReason value) noexcept;
[[nodiscard]] std::string_view to_string(CancelReason value) noexcept;

} // namespace vnpy::matching
