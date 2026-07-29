#include "matching_engine/matching_engine.hpp"

#include <algorithm>
#include <cctype>
#include <charconv>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <system_error>
#include <type_traits>
#include <utility>

namespace vm = vnpy::matching;

namespace {

std::string upper(std::string value) {
    std::transform(value.begin(), value.end(), value.begin(),
                   [](unsigned char c) { return static_cast<char>(std::toupper(c)); });
    return value;
}

std::optional<vm::Side> parse_side(std::string value) {
    value = upper(std::move(value));
    if (value == "BUY" || value == "B") {
        return vm::Side::Buy;
    }
    if (value == "SELL" || value == "S") {
        return vm::Side::Sell;
    }
    return std::nullopt;
}

template <typename T> std::optional<T> parse_integer(const std::string &text) {
    T value{};
    const char *begin = text.data();
    const char *end = text.data() + text.size();
    const auto [position, error] = std::from_chars(begin, end, value);
    if (error != std::errc{} || position != end) {
        return std::nullopt;
    }
    return value;
}

bool has_extra_token(std::istringstream &input) {
    std::string extra;
    return static_cast<bool>(input >> extra);
}

void print_event(const vm::Event &event) {
    std::visit(
        [](const auto &value) {
            using T = std::decay_t<decltype(value)>;
            std::cout << "  [seq=" << value.sequence << "] ";

            if constexpr (std::is_same_v<T, vm::OrderAccepted>) {
                std::cout << "ACCEPT order=" << value.order_id
                          << " side=" << vm::to_string(value.side)
                          << " type=" << vm::to_string(value.type) << " price=" << value.price
                          << " qty=" << value.quantity;
            } else if constexpr (std::is_same_v<T, vm::Trade>) {
                std::cout << "TRADE id=" << value.trade_id << " maker=" << value.maker_order_id
                          << " taker=" << value.taker_order_id
                          << " taker_side=" << vm::to_string(value.taker_side)
                          << " price=" << value.price << " qty=" << value.quantity
                          << " maker_rem=" << value.maker_remaining
                          << " taker_rem=" << value.taker_remaining;
            } else if constexpr (std::is_same_v<T, vm::OrderCanceled>) {
                std::cout << "CANCEL order=" << value.order_id << " qty=" << value.canceled_quantity
                          << " reason=" << vm::to_string(value.reason);
            } else if constexpr (std::is_same_v<T, vm::OrderRejected>) {
                std::cout << "REJECT order=" << value.order_id
                          << " reason=" << vm::to_string(value.reason);
            } else if constexpr (std::is_same_v<T, vm::CancelRejected>) {
                std::cout << "CANCEL_REJECT order=" << value.order_id
                          << " reason=UNKNOWN_OR_TERMINAL_ORDER";
            }
            std::cout << '\n';
        },
        event);
}

void print_events(const vm::EventBuffer &events) {
    for (const vm::Event &event : events) {
        print_event(event);
    }
}

void print_level(const vm::PriceLevelView &level) {
    std::cout << "  price=" << std::setw(6) << level.price << " total=" << std::setw(4)
              << level.total_quantity << " fifo=[";
    for (std::size_t i = 0; i < level.orders.size(); ++i) {
        const vm::OrderView &order = level.orders[i];
        if (i != 0) {
            std::cout << ", ";
        }
        std::cout << order.order_id << ':' << order.remaining;
    }
    std::cout << "]\n";
}

void print_book(const vm::MatchingEngine &engine, std::size_t depth = 0) {
    const vm::BookSnapshot book = engine.snapshot(depth);
    std::cout << "ASKS (best first)\n";
    for (const vm::PriceLevelView &level : book.asks) {
        print_level(level);
    }
    std::cout << "------------------------------\n";
    std::cout << "BIDS (best first)\n";
    for (const vm::PriceLevelView &level : book.bids) {
        print_level(level);
    }
    std::cout << "active_orders=" << engine.active_order_count() << "\n";
}

void print_help() {
    std::cout << "Commands (all prices are integer ticks):\n"
              << "  LIMIT  <id> <BUY|SELL> <price> <qty>\n"
              << "  MARKET <id> <BUY|SELL> <qty>\n"
              << "  CANCEL <id>\n"
              << "  BOOK [depth]       0 or omitted means all levels\n"
              << "  CHECK              validate internal invariants\n"
              << "  HELP\n"
              << "  QUIT\n";
}

bool process_line(vm::MatchingEngine &engine, std::string line) {
    const std::size_t comment = line.find('#');
    if (comment != std::string::npos) {
        line.erase(comment);
    }

    std::istringstream input(line);
    std::string command;
    if (!(input >> command)) {
        return true;
    }
    command = upper(std::move(command));

    if (command == "LIMIT") {
        std::string id_text;
        std::string side_text;
        std::string price_text;
        std::string quantity_text;
        if (!(input >> id_text >> side_text >> price_text >> quantity_text) ||
            has_extra_token(input)) {
            std::cout << "error: expected LIMIT <id> <BUY|SELL> <price> <qty>\n";
            return true;
        }
        const auto id = parse_integer<vm::OrderId>(id_text);
        const auto side = parse_side(side_text);
        const auto price = parse_integer<vm::Price>(price_text);
        const auto quantity = parse_integer<vm::Quantity>(quantity_text);
        if (!id.has_value() || !side.has_value() || !price.has_value() || !quantity.has_value()) {
            std::cout << "error: invalid LIMIT field\n";
            return true;
        }
        print_events(engine.submit(vm::NewOrder{
            .order_id = *id,
            .side = *side,
            .type = vm::OrderType::Limit,
            .price = *price,
            .quantity = *quantity,
        }));
    } else if (command == "MARKET") {
        std::string id_text;
        std::string side_text;
        std::string quantity_text;
        if (!(input >> id_text >> side_text >> quantity_text) || has_extra_token(input)) {
            std::cout << "error: expected MARKET <id> <BUY|SELL> <qty>\n";
            return true;
        }
        const auto id = parse_integer<vm::OrderId>(id_text);
        const auto side = parse_side(side_text);
        const auto quantity = parse_integer<vm::Quantity>(quantity_text);
        if (!id.has_value() || !side.has_value() || !quantity.has_value()) {
            std::cout << "error: invalid MARKET field\n";
            return true;
        }
        print_events(engine.submit(vm::NewOrder{
            .order_id = *id,
            .side = *side,
            .type = vm::OrderType::Market,
            .price = 0,
            .quantity = *quantity,
        }));
    } else if (command == "CANCEL") {
        std::string id_text;
        if (!(input >> id_text) || has_extra_token(input)) {
            std::cout << "error: expected CANCEL <id>\n";
            return true;
        }
        const auto id = parse_integer<vm::OrderId>(id_text);
        if (!id.has_value()) {
            std::cout << "error: invalid order ID\n";
            return true;
        }
        print_events(engine.cancel(*id));
    } else if (command == "BOOK") {
        std::size_t depth = 0;
        std::string depth_text;
        if (input >> depth_text) {
            const auto parsed_depth = parse_integer<std::size_t>(depth_text);
            if (!parsed_depth.has_value() || has_extra_token(input)) {
                std::cout << "error: depth must be a non-negative integer\n";
                return true;
            }
            depth = *parsed_depth;
        }
        print_book(engine, depth);
    } else if (command == "CHECK") {
        std::string error;
        if (engine.check_invariants(&error)) {
            std::cout << "invariants: OK\n";
        } else {
            std::cout << "invariants: FAILED: " << error << '\n';
        }
    } else if (command == "HELP") {
        print_help();
    } else if (command == "QUIT" || command == "EXIT") {
        return false;
    } else {
        std::cout << "error: unknown command '" << command << "'\n";
    }

    return true;
}

void run_stream(vm::MatchingEngine &engine, std::istream &input, bool prompt) {
    std::string line;
    while (true) {
        if (prompt) {
            std::cout << "> " << std::flush;
        }
        if (!std::getline(input, line)) {
            break;
        }
        if (!process_line(engine, line)) {
            break;
        }
    }
}

void submit_and_show(vm::MatchingEngine &engine, const vm::NewOrder &order) {
    std::cout << "\n>>> " << vm::to_string(order.type) << ' ' << order.order_id << ' '
              << vm::to_string(order.side);
    if (order.type == vm::OrderType::Limit) {
        std::cout << " price=" << order.price;
    }
    std::cout << " qty=" << order.quantity << '\n';
    print_events(engine.submit(order));
}

void run_builtin_demo() {
    vm::MatchingEngine engine;
    std::cout << "Price-time-priority matching demo\n"
              << "Prices are represented as integer ticks.\n";

    submit_and_show(engine, {100, vm::Side::Sell, vm::OrderType::Limit, 10'100, 5});
    submit_and_show(engine, {101, vm::Side::Sell, vm::OrderType::Limit, 10'100, 7});
    submit_and_show(engine, {102, vm::Side::Sell, vm::OrderType::Limit, 10'200, 4});

    std::cout << "\nTwo orders share price 10100; order 100 is first in FIFO.\n";
    print_book(engine);

    submit_and_show(engine, {200, vm::Side::Buy, vm::OrderType::Limit, 10'100, 8});
    std::cout << "\nOrder 200 fills order 100 first, then partially fills order 101.\n";
    print_book(engine);

    submit_and_show(engine, {201, vm::Side::Buy, vm::OrderType::Market, 0, 10});
    std::cout << "\nThe market order sweeps all asks; its unmatched remainder is canceled.\n";
    print_book(engine);

    submit_and_show(engine, {300, vm::Side::Buy, vm::OrderType::Limit, 9'900, 3});
    std::cout << "\n>>> CANCEL 300\n";
    print_events(engine.cancel(300));

    std::string error;
    std::cout << "\nInvariant check: " << (engine.check_invariants(&error) ? "OK" : error) << '\n';
}

} // namespace

int main(int argc, char **argv) {
    if (argc == 1) {
        run_builtin_demo();
        return 0;
    }

    const std::string option = argv[1];
    vm::MatchingEngine engine;

    if (option == "--interactive" || option == "-i") {
        print_help();
        run_stream(engine, std::cin, true);
        return 0;
    }

    if (option == "--file" && argc == 3) {
        std::ifstream file(argv[2]);
        if (!file) {
            std::cerr << "failed to open command file: " << argv[2] << '\n';
            return 1;
        }
        run_stream(engine, file, false);
        return 0;
    }

    std::cout << "Usage:\n"
              << "  matching_engine_demo             run built-in scenario\n"
              << "  matching_engine_demo -i          interactive mode\n"
              << "  matching_engine_demo --file PATH replay command file\n";
    return option == "--help" || option == "-h" ? 0 : 1;
}
